// Copyright 2019 Sho Hirose
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <array>    // std::array
#include <cmath>    // std::sqrt, std::pow
#include <complex>  // std::complex

namespace shirose {

/// @brief Computes roots of a quadratic equation.
/// @param[in] a Array of coefficients of a quadratic equation
/// @returns Array of roots of a quadratic equation
///
/// The quadratic equation takes the form of:
/// \f[
///   x^2 + a[0] x + a[1] = 0.
/// \f]
template <typename T>
inline std::array<std::complex<T>, 2> roots(
    const std::array<T, 2>& a) noexcept {
  // Discriminant of the quadratic equation
  const auto disc = a[0] * a[0] - 4 * a[1];

  using std::complex;
  using std::sqrt;

  const auto s = sqrt(complex<T>(disc, 0));
  const auto x1 = (-a[0] + s) / 2.0;
  const auto x2 = (-a[0] - s) / 2.0;

  return {x1, x2};
}

/// @brief Computes roots of a cubic equation by using Cardano's formula.
/// @param[in] a Array of coefficients of a cubic equation
/// @returns Array of roots of a cubic equation
///
/// The cubic equation takes the form of:
/// \f[
///   x^3 + a[0] x^2 + a[1] x + a[2] = 0.
/// \f]
template <typename T>
std::array<std::complex<T>, 3> roots(const std::array<T, 3>& a) noexcept {
  // Depressed cubic equation:
  // x^3 + 3px + 2q = 0
  const auto p = (3 * a[1] - a[0] * a[0]) / 9;
  const auto q = (27 * a[2] + a[0] * (2 * a[0] * a[0] - 9 * a[1])) / 54;
  // Discriminant of the cubic equation
  const auto disc = p * p * p + q * q;

  using std::complex;
  using std::pow;
  using std::sqrt;

  const auto s = sqrt(complex<T>(disc, 0));
  const auto u1 = pow(-q + s, 1.0 / 3.0);
  const auto u2 = pow(-q - s, 1.0 / 3.0);

  constexpr double sqrt3 = 1.7320508075688772935;
  // The primitive cube root of unity
  const auto w1 = complex<T>(-0.5, sqrt3 / 2);
  const auto w2 = complex<T>(-0.5, -sqrt3 / 2);

  // Roots based on Cardano's formula
  const auto x1 = u1 + u2 - a[0] / 3;
  const auto x2 = w1 * u1 + w2 * u2 - a[0] / 3;
  const auto x3 = w2 * u1 + w1 * u2 - a[0] / 3;

  return {x1, x2, x3};
}

/// @brief Computes the discriminant of a quadratic equation.
/// @param[in] a Array of coefficients of a quadratic equation
/// @returns Discriminant of a quadratic equation
///
/// The quadratic equation takes the form of:
/// \f[
///   x^2 + a[0] x + a[1] = 0.
/// \f]
template <typename T>
inline T discriminant(const std::array<T, 2>& a) noexcept {
  return a[0] * a[0] - 4 * a[1];
}

/// @brief Computes the discriminant of a cubic equation.
/// @param[in] a Array of coefficients of a cubic equation
/// @returns Discriminant of a cubic equation
///
/// The cubic equation takes the form of:
/// \f[
///   x^3 + a[0] x^2 + a[1] x + a[2] = 0.
/// \f]
template <typename T>
inline T discriminant(const std::array<T, 3>& a) noexcept {
  // Depressed cubic equation:
  // x^3 + 3px + 2q = 0
  const auto p = (3 * a[1] - a[0] * a[0]) / 9;
  const auto q = (27 * a[2] + a[0] * (2 * a[0] * a[0] - 9 * a[1])) / 54;
  return p * p * p + q * q;
}

}  // namespace shirose