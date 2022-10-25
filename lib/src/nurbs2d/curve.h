/**
 * The Curve class represents a non-uniform polynomial B-spline curve, while the
 * RationalCurve class represents a non-uniform rational B-spline (NURBS) curve.
 */

#pragma once

#include <vector>
#include "Point2d.h"

namespace nurbs2d
{

// Forward declaration
template <typename T> struct RationalCurve;

/**
Struct for holding a polynomial B-spline curve
@tparam T Data type of control points and knots (float or double)
*/
template <typename T> struct Curve
{
    unsigned int degree;
    std::vector<T> knots;
    std::vector<rf::Point2d<T>> control_points;

    Curve() = default;
    Curve(const RationalCurve<T> &crv) : Curve(crv.degree, crv.knots, crv.control_points) {}
    Curve(unsigned int degree, const std::vector<T> &knots,
          const std::vector<rf::Point2d<T>> &control_points)
        : degree(degree), knots(knots), control_points(control_points)
    {
    }
};

/**
Struct for holding a rational B-spline curve
@tparam T Data type of control points and knots (float or double)
*/
template <typename T> struct RationalCurve
{
    unsigned int degree;
    std::vector<T> knots;
    std::vector<rf::Point2d<T>> control_points;
    std::vector<T> weights;

    RationalCurve() = default;
    RationalCurve(const Curve<T> &crv)
        : RationalCurve(crv, std::vector<T>(crv.control_points.size(), 1.0))
    {
    }
    RationalCurve(const Curve<T> &crv, const std::vector<T> &weights)
        : RationalCurve(crv.degree, crv.knots, crv.control_points, weights)
    {
    }
    RationalCurve(unsigned int degree, const std::vector<T> &knots,
                  const std::vector<rf::Point2d<T>> &control_points, const std::vector<T> weights)
        : degree(degree), knots(knots), control_points(control_points), weights(weights)
    {
    }
};

} // namespace nurbs2d


