/**
 * Core functionality for evaluating points, derivatives and related
 * quantities on NURBS curves and surfaces.
 */

#pragma once

#include "basis.h"
#include "curve.h"
#include <tuple>
#include <vector>

namespace nurbs2d
{

/////////////////////////////////////////////////////////////////////

namespace internal
{

/**
 * Evaluate point on a nonrational NURBS curve
 * @param[in] degree Degree of the given curve.
 * @param[in] knots Knot vector of the curve.
 * @param[in] control_points Control points of the curve.
 * @param[in] u Parameter to evaluate the curve at.
 * @return point Resulting point on the curve at parameter u.
 */
template <typename T>
rf::Point2d<T> curvePoint(unsigned int degree, const std::vector<T> &knots,
                            const std::vector<rf::Point2d<double>> &control_points, T u)
{
    // Initialize result to 0s
    rf::Point2d<T> point(T(0),T(0));

    // Find span and corresponding non-zero basis functions
    int span = findSpan(degree, knots, u);
    std::vector<T> N = bsplineBasis(degree, span, knots, u);

    // Compute point
    for (unsigned int j = 0; j <= degree; j++)
    {
        //point += static_cast<T>(N[j]) * control_points[span - degree + j];
        point.x+=static_cast<T>(N[j]) *control_points[span - degree + j].x;
        point.y+=static_cast<T>(N[j]) *control_points[span - degree + j].y;
    }
    return point;
}

/**
 * Evaluate derivatives of a non-rational NURBS curve
 * @param[in] degree Degree of the curve
 * @param[in] knots Knot vector of the curve.
 * @param[in] control_points Control points of the curve.
 * @param[in] num_ders Number of times to derivate.
 * @param[in] u Parameter to evaluate the derivatives at.
 * @return curve_ders Derivatives of the curve at u.
 * E.g. curve_ders[n] is the nth derivative at u, where 0 <= n <= num_ders.
 */
template <typename T>
std::vector<rf::Point2d<T>> curveDerivatives(unsigned int degree, const std::vector<T> &knots,
                                               const std::vector<rf::Point2d<T>> &control_points,
                                               int num_ders, T u)
{

    typedef Point2d<T> tvecn;
    using std::vector;

    std::vector<Point2d<T>> curve_ders;
    curve_ders.resize(num_ders + 1);

    // Assign higher order derivatives to zero
    for (int k = degree + 1; k <= num_ders; k++)
    {
        curve_ders[k] = tvecn(0.0);
    }

    // Find the span and corresponding non-zero basis functions & derivatives
    int span = findSpan(degree, knots, u);
    array2<T> ders = bsplineDerBasis<T>(degree, span, knots, u, num_ders);

    // Compute first num_ders derivatives
    int du = num_ders < static_cast<int>(degree) ? num_ders : static_cast<int>(degree);
    for (int k = 0; k <= du; k++)
    {
        curve_ders[k] = tvecn(0.0);
        for (int j = 0; j <= static_cast<int>(degree); j++)
        {
            curve_ders[k] += static_cast<T>(ders(k, j)) * control_points[span - degree + j];
        }
    }
    return curve_ders;
}

} // namespace internal

/////////////////////////////////////////////////////////////////////

/**
Evaluate point on a nonrational NURBS curve
@param[in] crv Curve object
@param[in] u Parameter to evaluate the curve at.
@return point Resulting point on the curve at parameter u.
*/
template <typename T> rf::Point2d<T> curvePoint(const Curve<T> &crv, T u)
{
    return internal::curvePoint(crv.degree, crv.knots, crv.control_points, u);
}

/**
 * Evaluate point on a rational NURBS curve
 * @param[in] crv RationalCurve object
 * @param[in] u Parameter to evaluate the curve at.
 * @return point Resulting point on the curve.
 */
template <typename T> rf::Point2d<T> curvePoint(const RationalCurve<T> &crv, T u)
{

    typedef rf::Point2d<T> tvecnp1;

    // Compute homogenous coordinates of control points
    std::vector<tvecnp1> Cw;
    Cw.reserve(crv.control_points.size());
    for (size_t i = 0; i < crv.control_points.size(); i++)
    {
        Cw.push_back(tvecnp1(util::cartesianToHomogenous(crv.control_points[i], crv.weights[i])));
    }

    // Compute point using homogenous coordinates
    tvecnp1 pointw = internal::curvePoint(crv.degree, crv.knots, Cw, u);

    // Convert back to cartesian coordinates
    return util::homogenousToCartesian(pointw);
}

/**
 * Evaluate derivatives of a non-rational NURBS curve
 * @param[in] crv Curve object
 * @param[in] num_ders Number of times to derivate.
 * @param[in] u Parameter to evaluate the derivatives at.
 * @return curve_ders Derivatives of the curve at u.
 * E.g. curve_ders[n] is the nth derivative at u, where 0 <= n <= num_ders.
 */
template <typename T>
std::vector<rf::Point2d<T>> curveDerivatives(const Curve<T> &crv, int num_ders, T u)
{
    return internal::curveDerivatives(crv.degree, crv.knots, crv.control_points, num_ders, u);
}

/**
 * Evaluate derivatives of a rational NURBS curve
 * @param[in] u Parameter to evaluate the derivatives at.
 * @param[in] knots Knot vector of the curve.
 * @param[in] control_points Control points of the curve.
 * @param[in] weights Weights corresponding to each control point.
 * @param[in] num_ders Number of times to differentiate.
 * @param[inout] curve_ders Derivatives of the curve at u.
 * E.g. curve_ders[n] is the nth derivative at u, where n is between 0 and
 * num_ders-1.
 */
template <typename T>
std::vector<rf::Point2d<T>> curveDerivatives(const RationalCurve<T> &crv, int num_ders, T u)
{

    typedef glm::vec<3, T> tvecn;
    typedef glm::vec<4, T> tvecnp1;

    std::vector<tvecn> curve_ders;
    curve_ders.reserve(num_ders + 1);

    // Compute homogenous coordinates of control points
    std::vector<tvecnp1> Cw;
    Cw.reserve(crv.control_points.size());
    for (size_t i = 0; i < crv.control_points.size(); i++)
    {
        Cw.push_back(util::cartesianToHomogenous(crv.control_points[i], crv.weights[i]));
    }

    // Derivatives of Cw
    std::vector<tvecnp1> Cwders =
        internal::curveDerivatives(crv.degree, crv.knots, Cw, num_ders, u);

    // Split Cwders into coordinates and weights
    std::vector<tvecn> Aders;
    std::vector<T> wders;
    for (const auto &val : Cwders)
    {
        Aders.push_back(util::truncateHomogenous(val));
        wders.push_back(val.w);
    }

    // Compute rational derivatives
    for (int k = 0; k <= num_ders; k++)
    {
        tvecn v = Aders[k];
        for (int i = 1; i <= k; i++)
        {
            v -= static_cast<T>(util::binomial(k, i)) * wders[i] * curve_ders[k - i];
        }
        curve_ders.push_back(v / wders[0]);
    }
    return curve_ders;
}

/**
 * Evaluate the tangent of a B-spline curve
 * @param[in] crv Curve object
 * @return Unit tangent of the curve at u.
 */
template <typename T> rf::Point2d<T> curveTangent(const Curve<T> &crv, T u)
{
    std::vector<glm::vec<3, T>> ders = curveDerivatives(crv, 1, u);
    glm::vec<3, T> du = ders[1];
    T du_len = glm::length(du);
    if (!util::close(du_len, T(0)))
    {
        du /= du_len;
    }
    return du;
}

/**
 * Evaluate the tangent of a rational B-spline curve
 * @param[in] crv RationalCurve object
 * @return Unit tangent of the curve at u.
 */
template <typename T> rf::Point2d<T> curveTangent(const RationalCurve<T> &crv, T u)
{
    std::vector<glm::vec<3, T>> ders = curveDerivatives(crv, 1, u);
    glm::vec<3, T> du = ders[1];
    T du_len = glm::length(du);
    if (!util::close(du_len, T(0)))
    {
        du /= du_len;
    }
    return du;
}



} // namespace nurbs2d
