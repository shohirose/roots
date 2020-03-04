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

#ifndef ROOTS_QUADRATIC_EQUATION_HPP
#define ROOTS_QUADRATIC_EQUATION_HPP

#include <array>    // std::array
#include <cmath>    // std::sqrt, std::fabs
#include <complex>  // std::complex

namespace roots {

/// @brief Quadratic equation with real coefficients.
/// @tparam T Value type for coefficients. It must be a scalar type.
template <typename T>
class quadratic_equation {
 public:
  using value_t = T;
  using coeffs_t = std::array<value_t, 2>;
  using roots_t = std::array<std::complex<value_t>, 2>;

  quadratic_equation() = default;

  /// @brief Computes roots.
  /// @param[in] a Coefficients of the equation.
  explicit quadratic_equation(const coeffs_t& a) noexcept
      : result_{calc_roots(a)} {}

  /// @brief Computes roots.
  /// @param[in] a Coefficients of the equation.
  void compute(const coeffs_t& a) noexcept { result_ = calc_roots(a); }

  /// @brief Returns discriminant.
  value_t discriminant() const noexcept { return result_.discriminant; }

  /// @brief Returns roots.
  const roots_t& roots() const noexcept { return result_.roots; }

  /// @brief Returns the number of real roots.
  int num_of_real_roots() const noexcept {
    constexpr double tolerance = 1e-10;
    const auto d = this->discriminant();
    using std::fabs;
    if (d < 0) {
      return 0;
    } else if (fabs(d) < tolerance) {
      return 1;
    } else {
      return 2;
    }
  }

 private:
  /// @brief Result of the root calculation.
  struct result {
    value_t discriminant;
    roots_t roots;
  };

  using result_t = result;

  /// @brief Computes roots.
  /// @param[in] a Coefficients of the quadratic equation.
  static result_t calc_roots(const coeffs_t& a) noexcept {
    const auto d = a[0] * a[0] - 4 * a[1];

    using std::complex;
    using std::sqrt;

    const auto s = sqrt(complex<T>(d, 0));
    const auto x1 = (-a[0] + s) / 2.0;
    const auto x2 = (-a[0] - s) / 2.0;

    return {d, {x1, x2}};
  }

  result_t result_;
};

}  // namespace roots

#endif  // ROOTS_QUADRATIC_EQUATION_HPP