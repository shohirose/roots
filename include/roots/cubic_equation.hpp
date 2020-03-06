// Copyright 2020 Sho Hirose
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

#ifndef ROOTS_CUBIC_EQUATION_HPP
#define ROOTS_CUBIC_EQUATION_HPP

#include <array>    // std::array
#include <cmath>    // std::sqrt, std::pow, std::fabs
#include <complex>  // std::complex

namespace roots {

/// @brief Cubic equation with real coefficients.
/// @tparam T Value type for coefficients. It must be a scalar type.
template <typename T>
class cubic_equation {
 public:
  using value_t = T;
  using coeffs_t = std::array<value_t, 3>;
  using complex_t = std::complex<value_t>;
  using roots_t = std::array<complex_t, 3>;

  cubic_equation() = default;

  /// @brief Computes roots.
  /// @param[in] a Coefficients of the equation.
  explicit cubic_equation(const coeffs_t& a) noexcept
      : result_{calc_roots(a)} {}

  /// @brief Computes roots.
  /// @param[in] a Coefficients of the equation.
  void compute(const coeffs_t& a) noexcept { result_ = calc_roots(a); }

  /// @brief Returns discriminant
  value_t discriminant() const noexcept { return result_.discriminant; }

  /// @brief Returns roots.
  const roots_t& roots() const noexcept { return result_.roots; }

  /// @brief Returns the number of distinct real roots.
  int num_of_real_roots() const noexcept {
    using std::fabs;
    constexpr double tolerance = 1e-10;
    const auto d = this->discriminant();
    if (d < 0) {
      return 1;
    } else if (d < tolerance) {
      return (fabs(this->p()) < tolerance) ? 1 : 2;
    } else {
      return 3;
    }
  }

 private:
  value_t p() const noexcept { return result_.p; }
  value_t q() const noexcept { return result_.q; }

  /// @brief Result of the root calculation.
  ///
  /// A cubic equation
  /// \f[ x^3 + a_0 x^2 + a_1 x + a_2 = 0 \f]
  /// can be converted into the depressed cubic equation:
  /// \f[ y^3 + py + q = 0 \f]
  /// where \f$ y \f$, \f$ p \f$, and \f$ q \f$ are defined by
  /// \f[
  ///     y = x + \frac{a_0}{3}
  ///     p = \frac{3 a_1 - a_0^2}{9}
  ///     q = \frac{27 a_2 + 2 a_0^3 - 9 a_0 a_1}{54}
  /// \f]
  /// Then, the discriminant (\f$ \Delta \f$) of the original cubic equation can
  /// be calculated by
  /// \f[ \Delta = - p^3 - q^2 \f]
  struct result {
    value_t p;
    value_t q;
    value_t discriminant;
    roots_t roots;
  };

  using result_t = result;

  static result_t calc_roots(const coeffs_t& a) noexcept {
    const auto p = (3 * a[1] - a[0] * a[0]) / 9;
    const auto q = (27 * a[2] + a[0] * (2 * a[0] * a[0] - 9 * a[1])) / 54;
    const auto d = p * p * p + q * q;

    using std::pow;
    using std::sqrt;

    const auto s = sqrt(complex_t(d, 0));
    const auto u1 = pow(-q + s, 1.0 / 3.0);
    const auto u2 = pow(-q - s, 1.0 / 3.0);

    constexpr double sqrt3 = 1.7320508075688772935;
    // The primitive cube roots of unity
    const auto w1 = complex_t{-0.5, sqrt3 / 2.0};
    const auto w2 = complex_t{-0.5, -sqrt3 / 2.0};

    // Roots based on Cardano's formula
    const auto x1 = u1 + u2 - a[0] / 3;
    const auto x2 = w1 * u1 + w2 * u2 - a[0] / 3;
    const auto x3 = w2 * u1 + w1 * u2 - a[0] / 3;

    return {p, q, -d, {x1, x2, x3}};
  }

  result_t result_;
};

}  // namespace roots

#endif  // ROOTS_CUBIC_EQUATION_HPP