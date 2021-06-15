#include "basic_warper.hpp"

#include "simple_calc.hpp"

namespace vva {

auto BasicOperationWarper::addition(const int16_t& a, const int16_t& b) -> int16_t {
  return add(a, b);
}

auto BasicOperationWarper::subtraction(const int16_t& a, const int16_t& b) -> int16_t {
  return subtract(a, b);
}

auto BasicOperationWarper::multiplication(const int16_t& a,
                                             const int16_t& b) -> int16_t {
  return multiply(a, b);
}

auto BasicOperationWarper::division(const int16_t& a, const int16_t& b) -> int16_t {
  return divide(a, b);
}

}  // namespace vva