/**
 * Functionality for checking validity and properties of NURBS curves and
 * surfaces
 */

#pragma once


#include <algorithm>
#include <limits>
#include <vector>
#include "curve.h"

namespace nurbs2d
{

/////////////////////////////////////////////////////////////////////

namespace internal
{

/**
 * Checks if the relation between degree, number of knots, and
 * number of control points is valid
 * @param[in] degree Degree
 * @param[in] num_knots Number of knot values
 * @param[in] num_ctrl_pts Number of control points
 * @return Whether the relationship is valid
 */
inline bool isValidRelation(unsigned int degree, size_t num_knots, size_t num_ctrl_pts)
{
    return (num_knots - degree - 1) == num_ctrl_pts;
}

/**
 * isKnotVectorMonotonic returns whether the knots are in ascending order
 * @tparam Type of knot values
 * @param[in] knots Knot vector
 * @return Whether monotonic
 */
template <typename T> bool isKnotVectorMonotonic(const std::vector<T> &knots)
{
    return std::is_sorted(knots.begin(), knots.end());
}

/**
 * Returns whether the curve is valid
 * @tparam T Type of control point coordinates, knot values
 * @param[in] degree Degree of curve
 * @param[in] knots Knot vector of curve
 * @param[in] control_points Control points of curve
 * @return Whether valid
 */
template <typename T>
bool curveIsValid(unsigned int degree, const std::vector<T> &knots,
                  const std::vector<rf::Point2d<double>> &control_points)
{
    if (degree < 1 || degree > 9)
    {
        return false;
    }
    if (!isValidRelation(degree, knots.size(), control_points.size()))
    {
        return false;
    }
    if (!isKnotVectorMonotonic(knots))
    {
        return false;
    }
    return true;
}

/**
 * Returns whether the curve is valid
 * @tparam T Type of control point coordinates, knot values and weights
 * @param[in] degree Degree of curve
 * @param[in] knots Knot vector of curve
 * @param[in] control_points Control points of curve
 * @return Whether valid
 */
template <typename T>
bool curveIsValid(unsigned int degree, const std::vector<T> &knots,
                  const std::vector<rf::Point2d<double>> &control_points, const std::vector<T> &weights)
{
    if (!isValidRelation(degree, knots.size(), control_points.size()))
    {
        return false;
    }
    if (weights.size() != control_points.size())
    {
        return false;
    }
    return true;
}


// /**
//  * Returns whether the given knot vector is closed by checking the
//  * periodicity of knot vectors near the start and end
//  * @param[in] degree Degree of curve/surface
//  * @param[in] knots Knot vector of curve/surface
//  * @return Whether knot vector is closed
//  */
// template <typename T> bool isKnotVectorClosed(unsigned int degree, const std::vector<T> &knots)
// {
//     for (int i = 0; i < degree - 1; ++i)
//     {
//         int j = knots.size() - degree + i;
//         if (std::abs((knots[i + 1] - knots[i]) - (knots[j + 1] - knots[j])) >
//             std::numeric_limits<T>::epsilon())
//         {
//             return false;
//         }
//     }
//     return true;
// }

// /**
//  * Returns whether the given knot vector is closed by checking the
//  * periodicity of knot vectors near the start and end
//  * @param[in] degree Degree of curve/surface
//  * @param[in] vec Array of any control points/weights
//  * @return Whether knot vector is closed
//  */
// template <typename T> bool isArray1Closed(unsigned int degree, const std::vector<T> &vec)
// {
//     for (int i = 0; i < degree; ++i)
//     {
//         int j = vec.size() - degree + i;
//         if (glm::length(vec[i] - vec[j]) > 1e-5)
//         {
//             return false;
//         }
//     }
//     return true;
// }



} // namespace internal

/////////////////////////////////////////////////////////////////////

// /**
//  * Returns the multiplicity of the knot at index
//  * @tparam Type of knot values
//  * @param[in] knots Knot vector
//  * @param[in] knot_val Knot of interest
//  * @return Multiplicity (>= 0)
//  */
// template <typename T> unsigned int knotMultiplicity(const std::vector<T> &knots, T knot_val)
// {
//     T eps = std::numeric_limits<T>::epsilon();
//     unsigned int mult = 0;
//     for (const T knot : knots)
//     {
//         if (std::abs(knot_val - knot) < eps)
//         {
//             ++mult;
//         }
//     }
//     return mult;
// }

// /**
//  * Returns the mulitplicity of the knot at index
//  * @tparam Type of knot values
//  * @param[in] knots Knot vector
//  * @param[in] index Index of knot of interest
//  * @return Multiplicity (>= 1)
//  */
// template <typename T>
// [[deprecated("Use knotMultiplicity(knots, param).")]]
// unsigned int knotMultiplicity(const std::vector<T> &knots, unsigned int index)
// {
//     T curr_knot_val = knots[index];
//     T eps = std::numeric_limits<T>::epsilon();
//     unsigned int mult = 0;
//     for (const T knot : knots)
//     {
//         if (std::abs(curr_knot_val - knot) < eps)
//         {
//             ++mult;
//         }
//     }
//     return mult;
// }

/**
 * Returns whether the curve is valid
 * @tparam T Type of control point coordinates, knot values
 * @param[in] crv Curve object
 * @return Whether valid
 */
template <typename T> bool curveIsValid(const Curve<T> &crv)
{
    return internal::curveIsValid(crv.degree, crv.knots, crv.control_points);
}

/**
 * Returns whether the curve is valid
 * @tparam T Type of control point coordinates, knot values
 * @param[in] crv RationalCurve object
 * @return Whether valid
 */
template <typename T> bool curveIsValid(const RationalCurve<T> &crv)
{
    return internal::curveIsValid(crv.degree, crv.knots, crv.control_points, crv.weights);
}


/**
 * Checks whether the curve is closed
 * @param[in] crv Curve object
 * @return  Whether closed
 */
// template <typename T> bool curveIsClosed(const Curve<T> &crv)
// {
//     return internal::isArray1Closed(crv.degree, crv.control_points) &&
//            internal::isKnotVectorClosed(crv.degree, crv.knots);
// }

// /**
//  * Checks whether the rational curve is closed
//  * @param[in] crv RationalCurve object
//  * @return  Whether closed
//  */
// template <typename T> bool curveIsClosed(const RationalCurve<T> &crv)
// {
//     return internal::isArray1Closed(crv.degree, crv.control_points) &&
//            internal::isArray1Closed(crv.degree, crv.weights) &&
//            internal::isKnotVectorClosed(crv.degree, crv.knots);
// }

} // namespace nurbs2d

