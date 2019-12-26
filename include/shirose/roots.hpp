// Copyright 2019 Sho Hirose (sho.hirose@gmail.com)
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

#ifndef SHIROSE_ROOTS_HPP
#define SHIROSE_ROOTS_HPP

#include <array>
#include <cmath>
#include <iostream>

namespace shirose {

template <typename T>
std::pair<std::array<T, 3>, int> roots(const std::array<T, 3>& p) noexcept {
  using std::abs;
  using std::acos;
  using std::cos;
  using std::isinf;
  using std::pow;
  using std::sqrt;

  const auto b = p[0];
  const auto c = p[1];
  const auto d = p[2];

  const auto q = (b * b - 3 * c) / 9;
  const auto r = (b * (2 * b * b - 9 * c) + 27 * d) / 54;
  const auto s = q * q * q - r * r;

  if (s > 0) {
    const auto sqrt_q = sqrt(q);
    const auto theta = acos(r / pow(q, 1.5));

    const auto x1 = -2 * sqrt_q * cos(theta / 3) - b / 3;
    const auto x2 = -2 * sqrt_q * cos((theta + 2 * M_PI) / 3) - b / 3;
    const auto x3 = -2 * sqrt_q * cos((theta + 4 * M_PI) / 3) - b / 3;

    return {{x1, x2, x3}, 3};
  } else if (s == 0) {
    if (r == 0) {
      return {{-b / 3, 0, 0}, 1};
    } else {
      const auto r13 = r >= 0 ? -pow(r, 1.0 / 3.0) : pow(-r, 1.0 / 3.0);
      const auto x1 = -b / 3 + 2 * r13;
      const auto x2 = -b / 3 - r13;
      return {{x1, x2, 0.0}, 2};
    }
  } else {
    const auto tmp1 = pow(sqrt(-s) + abs(r), 1.0 / 3.0);
    const auto tmp2 = tmp1 + q / tmp1;
    const auto x1 = r > 0 ? -tmp2 - b / 3 : tmp2 - b / 3;
    return {{x1, 0, 0}, 1};
  }
}

}  // namespace shirose

#endif  // SHIROSE_ROOTS_HPP