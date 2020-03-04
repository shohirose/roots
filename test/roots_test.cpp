#include "roots/roots.hpp"
#include <gtest/gtest.h>

TEST(RootsTest, QuadraticEquationTest) {
  using quadratic_equation_t = roots::quadratic_equation<double>;
  using coeffs_t = quadratic_equation_t::coeffs_t;

  // Only one real root
  {
    const coeffs_t a = {-2, 1};
    const auto eq = quadratic_equation_t(a);
    const auto x = eq.roots();

    EXPECT_EQ(eq.num_of_real_roots(), 1);

    EXPECT_NEAR(x[0].imag(), 0.0, 1e-10);
    EXPECT_NEAR(x[1].imag(), 0.0, 1e-10);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), 1.0, 1e-10);
  }

  // Two real roots
  {
    const coeffs_t a = {-3, 2};
    const auto eq = quadratic_equation_t(a);
    const auto x = eq.roots();

    EXPECT_EQ(eq.num_of_real_roots(), 2);

    EXPECT_NEAR(x[0].imag(), 0.0, 1e-10);
    EXPECT_NEAR(x[1].imag(), 0.0, 1e-10);

    EXPECT_NEAR(x[0].real(), 2.0, 1e-10);
    EXPECT_NEAR(x[1].real(), 1.0, 1e-10);
  }

  // Two complex roots
  {
    const coeffs_t a = {1, 1};
    const auto eq = quadratic_equation_t(a);
    const auto x = eq.roots();

    EXPECT_EQ(eq.num_of_real_roots(), 0);

    EXPECT_NEAR(x[0].imag(), std::sqrt(3.0) / 2, 1e-10);
    EXPECT_NEAR(x[1].imag(), -std::sqrt(3.0) / 2, 1e-10);

    EXPECT_NEAR(x[0].real(), -0.5, 1e-10);
    EXPECT_NEAR(x[1].real(), -0.5, 1e-10);
  }
}

TEST(RootsTest, CubicEquationTest) {
  using cubic_equation_t = roots::cubic_equation<double>;
  using coeffs_t = cubic_equation_t::coeffs_t;

  // Only one real root
  {
    const coeffs_t a = {-3.0, 3.0, -1.0};
    const auto eq = cubic_equation_t(a);
    const auto x = eq.roots();

    EXPECT_EQ(eq.num_of_real_roots(), 1);

    EXPECT_DOUBLE_EQ(x[0].imag(), 0);
    EXPECT_DOUBLE_EQ(x[1].imag(), 0);
    EXPECT_DOUBLE_EQ(x[2].imag(), 0);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[2].real(), 1.0, 1e-10);
  }

  // Three real roots
  {
    const coeffs_t a = {0.0, -1.0, 0.0};
    const auto eq = cubic_equation_t(a);
    const auto x = eq.roots();

    EXPECT_EQ(eq.num_of_real_roots(), 3);

    EXPECT_DOUBLE_EQ(x[0].imag(), 0);
    EXPECT_DOUBLE_EQ(x[1].imag(), 0);
    EXPECT_DOUBLE_EQ(x[2].imag(), 0);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), -1.0, 1e-10);
    EXPECT_NEAR(x[2].real(), 0.0, 1e-10);
  }

  // Two real roots
  {
    const coeffs_t a = {-2.0, 1.0, 0.0};
    const auto eq = cubic_equation_t(a);
    const auto x = eq.roots();

    EXPECT_EQ(eq.num_of_real_roots(), 2);

    EXPECT_DOUBLE_EQ(x[0].imag(), 0);
    EXPECT_DOUBLE_EQ(x[1].imag(), 0);
    EXPECT_DOUBLE_EQ(x[2].imag(), 0);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), 0.0, 1e-10);
    EXPECT_NEAR(x[2].real(), 1.0, 1e-10);
  }

  // One real root and two complex roots
  {
    const coeffs_t a = {0, 0, -1};
    const auto eq = cubic_equation_t(a);
    const auto x = eq.roots();

    EXPECT_EQ(eq.num_of_real_roots(), 1);

    EXPECT_NEAR(x[0].imag(), 0, 1e-10);
    EXPECT_NEAR(x[1].imag(), 0.8660254037, 1e-10);
    EXPECT_NEAR(x[2].imag(), -0.8660254037, 1e-10);

    EXPECT_NEAR(x[0].real(), 1.0, 1e-10);
    EXPECT_NEAR(x[1].real(), -0.5, 1e-10);
    EXPECT_NEAR(x[2].real(), -0.5, 1e-10);
  }
}
