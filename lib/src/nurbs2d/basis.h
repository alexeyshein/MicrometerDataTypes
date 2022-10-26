/**
 * Low-level functions for evaluating B-spline basis functions and their derivatives
 */

#pragma once

#include <vector>
#include <cassert>

namespace nurbs2d
{

 /**
 * Check if two numbers are close enough within eps
 * @param[in] a First number
 * @param[in] b Second number
 * @param[in] eps Tolerance for checking closeness
 * @return Whether the numbers are close w.r.t. the tolerance
 */
    template <typename T> inline bool close(T a, T b, double eps = std::numeric_limits<T>::epsilon())
    {
        return (std::abs(a - b) < eps) ? true : false;
    }




/**
 * Find the span of the given parameter in the knot vector.
 * @param[in] degree Degree of the curve.
 * @param[in] knots Knot vector of the curve.
 * @param[in] u Parameter value.
 * @return Span index into the knot vector such that (span - 1) < u <= span
*/
template <typename T> int findSpan(unsigned int degree, const std::vector<T> &knots, T u)
{
    // index of last control point
    int n = static_cast<int>(knots.size()) - degree - 2;
    assert(n >= 0);
    /*
        // For u that is equal to last knot value
        if (util::close(u, knots[n + 1])) {
            return n;
        }
    */
    // For values of u that lies outside the domain
    if (u > (knots[n + 1] - std::numeric_limits<T>::epsilon()))
    {
        return n;
    }
    if (u < (knots[degree] + std::numeric_limits<T>::epsilon()))
    {
        return degree;
    }

    // Binary search
    // TODO: Replace this with std::lower_bound
    int low = degree;
    int high = n + 1;
    int mid = (int)std::floor((low + high) / 2.0);
    while (u < knots[mid] || u >= knots[mid + 1])
    {
        if (u < knots[mid])
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
        mid = (int)std::floor((low + high) / 2.0);
    }
    return mid;
}

/**
 * Compute a single B-spline basis function
 * @param[in] i The ith basis function to compute.
 * @param[in] deg Degree of the basis function.
 * @param[in] knots Knot vector corresponding to the basis functions.
 * @param[in] u Parameter to evaluate the basis functions at.
 * @return The value of the ith basis function at u.
 */
template <typename T> T bsplineOneBasis(int i, unsigned int deg, const std::vector<T> &U, T u)
{
    int m = static_cast<int>(U.size()) - 1;
    // Special case
    if ((i == 0 && close(u, U[0])) || (i == m - deg - 1 && close(u, U[m])))
    {
        return 1.0;
    }
    // Local property ensures that basis function is zero outside span
    if (u < U[i] || u >= U[i + deg + 1])
    {
        return 0.0;
    }
    // Initialize zeroth-degree functions
    std::vector<double> N;
    N.resize(deg + 1);
    for (int j = 0; j <= static_cast<int>(deg); j++)
    {
        N[j] = (u >= U[i + j] && u < U[i + j + 1]) ? 1.0 : 0.0;
    }
    // Compute triangular table
    for (int k = 1; k <= static_cast<int>(deg); k++)
    {
        T saved = (close(N[0], 0.0)) ? 0.0 : ((u - U[i]) * N[0]) / (U[i + k] - U[i]);
        for (int j = 0; j < static_cast<int>(deg) - k + 1; j++)
        {
            T Uleft = U[i + j + 1];
            T Uright = U[i + j + k + 1];
            if (close(N[j + 1], 0.0))
            {
                N[j] = saved;
                saved = 0.0;
            }
            else
            {
                T temp = N[j + 1] / (Uright - Uleft);
                N[j] = saved + (Uright - u) * temp;
                saved = (u - Uleft) * temp;
            }
        }
    }
    return N[0];
}

/**
 * Compute all non-zero B-spline basis functions
 * @param[in] deg Degree of the basis function.
 * @param[in] span Index obtained from findSpan() corresponding the u and knots.
 * @param[in] knots Knot vector corresponding to the basis functions.
 * @param[in] u Parameter to evaluate the basis functions at.
 * @return N Values of (deg+1) non-zero basis functions.
 */
template <typename T>
std::vector<T> bsplineBasis(unsigned int deg, int span, const std::vector<T> &knots, T u)
{
    std::vector<T> N;
    N.resize(deg + 1, T(0));
    std::vector<T> left, right;
    left.resize(deg + 1, static_cast<T>(0.0));
    right.resize(deg + 1, static_cast<T>(0.0));
    T saved = 0.0, temp = 0.0;

    N[0] = 1.0;

    for (int j = 1; j <= static_cast<int>(deg); j++)
    {
        left[j] = (u - knots[span + 1 - j]);
        right[j] = knots[span + j] - u;
        saved = 0.0;
        for (int r = 0; r < j; r++)
        {
            temp = N[r] / (right[r + 1] + left[j - r]);
            N[r] = saved + right[r + 1] * temp;
            saved = left[j - r] * temp;
        }
        N[j] = saved;
    }
    return N;
}


} // namespace nurbs2d


