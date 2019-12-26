#include "shirose/roots.hpp"
#include <gtest/gtest.h>

TEST(RootsTest, RootsTest) {
  // Only one real root
  {
    const std::array<double, 3> p = {-3.0, 3.0, -1.0};
    const auto result = shirose::roots(p);
    const auto roots = result.first;
    const auto num_of_roots = result.second;
    EXPECT_EQ(num_of_roots, 1);
    EXPECT_NEAR(roots[0], 1.0, 1e-10);
  }

  // Three real roots
  {
    const std::array<double, 3> p = {0.0, -1.0, 0.0};
    const auto result = shirose::roots(p);
    const auto roots = result.first;
    const auto num_of_roots = result.second;
    EXPECT_EQ(num_of_roots, 3);
    EXPECT_NEAR(roots[0], -1.0, 1e-10);
    EXPECT_NEAR(roots[1], 1.0, 1e-10);
    EXPECT_NEAR(roots[2], 0.0, 1e-10);
  }

  // Two real roots
  {
    const std::array<double, 3> p = {-2.0, 1.0, 0.0};
    const auto result = shirose::roots(p);
    const auto roots = result.first;
    const auto num_of_roots = result.second;
    EXPECT_EQ(num_of_roots, 2);
    EXPECT_NEAR(roots[0], 0.0, 1e-10);
    EXPECT_NEAR(roots[1], 1.0, 1e-10);
  }
}
