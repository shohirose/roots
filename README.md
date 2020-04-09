# roots
[![Build Status](https://travis-ci.com/shohirose/roots.svg?branch=master)](https://travis-ci.com/shohirose/roots) [![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://opensource.org/licenses/MIT)

`roots` is a header-only library in C++ to compute roots of polynomial equations. Currently, roots of quadratic and cubic equations can be computed.

## Example

### Quadratic equation

Discriminant and roots of a quadratic equation can be computed in the following mannter:

```cpp:quadratic_equation
using quadratic_equation_t = roots::quadratic_equation<double>;
using coeffs_t = quadratic_equation_t::coeffs_t;

// x^2 + a[0] x + a[1] = 0
const coeffs_t a = {1.0, 2.0};
const auto eq = quadratic_equation_t(a);
const auto d = eq.discriminant();
const auto x = eq.roots();
```

### Cubic equation

Discriminant and roots of a cubic equation can be computed in the following mannter:

```cpp:cubic_equation
using cubic_equation_t = roots::cubic_equation<double>;
using coeffs_t = cubic_equation_t::coeffs_t;

// x^3 + a[0] x^2 + a[1] x + a[2] = 0
const coeffs_t a = {1.0, 2.0, 3.0};
const auto eq = cubic_equation_t(a);
const auto d = eq.discriminant();
const auto x = eq.roots();
```