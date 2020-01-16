#include "shirose/roots.hpp"
#include <gtest/gtest.h>
#include <cmath>  // std::sqrt

using shirose::roots;

TEST(RootsTest, QuadraticEqRootsTest) {
  // Only one real root
  {
    const std::array<double, 2> a = {-2, 1};
    const auto x = roots(a);

    EXPECT_NEAR(x[0].imag(), 0.0, 1e-10);
    EXPECT_NEAR(x[1].imag(), 0.0, 1e-10);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), 1.0, 1e-10);
  }

  // Two real roots
  {
    const std::array<double, 2> a = {-3, 2};
    const auto x = roots(a);

    EXPECT_NEAR(x[0].imag(), 0.0, 1e-10);
    EXPECT_NEAR(x[1].imag(), 0.0, 1e-10);

    EXPECT_NEAR(x[0].real(), 2.0, 1e-10);
    EXPECT_NEAR(x[1].real(), 1.0, 1e-10);
  }

  // Two complex roots
  {
    const std::array<double, 2> a = {1, 1};
    const auto x = roots(a);

    EXPECT_NEAR(x[0].imag(), std::sqrt(3.0) / 2, 1e-10);
    EXPECT_NEAR(x[1].imag(), -std::sqrt(3.0) / 2, 1e-10);

    EXPECT_NEAR(x[0].real(), -0.5, 1e-10);
    EXPECT_NEAR(x[1].real(), -0.5, 1e-10);
  }
}

TEST(RootsTest, CubicEqRootsTest) {
  // Only one real root
  {
    const std::array<double, 3> a = {-3.0, 3.0, -1.0};
    const auto x = roots(a);

    EXPECT_DOUBLE_EQ(x[0].imag(), 0);
    EXPECT_DOUBLE_EQ(x[1].imag(), 0);
    EXPECT_DOUBLE_EQ(x[2].imag(), 0);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[2].real(), 1.0, 1e-10);
  }

  // Three real roots
  {
    const std::array<double, 3> a = {0.0, -1.0, 0.0};
    const auto x = roots(a);

    EXPECT_DOUBLE_EQ(x[0].imag(), 0);
    EXPECT_DOUBLE_EQ(x[1].imag(), 0);
    EXPECT_DOUBLE_EQ(x[2].imag(), 0);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), -1.0, 1e-10);
    EXPECT_NEAR(x[2].real(), 0.0, 1e-10);
  }

  // Two real roots
  {
    const std::array<double, 3> a = {-2.0, 1.0, 0.0};
    const auto x = roots(a);

    EXPECT_DOUBLE_EQ(x[0].imag(), 0);
    EXPECT_DOUBLE_EQ(x[1].imag(), 0);
    EXPECT_DOUBLE_EQ(x[2].imag(), 0);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), 0.0, 1e-10);
    EXPECT_NEAR(x[2].real(), 1.0, 1e-10);
  }

  // One real root and two complex roots
  {
    const std::array<double, 3> a = {0, 0, -1};
    const auto x = roots(a);

    EXPECT_NEAR(x[0].imag(), 0, 1e-10);
    EXPECT_NEAR(x[1].imag(), 0.8660254037, 1e-10);
    EXPECT_NEAR(x[2].imag(), -0.8660254037, 1e-10);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), -0.5, 1e-10);
    EXPECT_NEAR(x[2].real(), -0.5, 1e-10);
  }
}
