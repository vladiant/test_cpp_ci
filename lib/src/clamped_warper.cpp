#include "clamped_warper.hpp"

#include <limits>
#include <stdexcept>

#include "simple_calc.hpp"

namespace {
using WarperType = int32_t;

constexpr WarperType kMaxValue = std::numeric_limits<int16_t>::max();
constexpr WarperType kMinValue = std::numeric_limits<int16_t>::min();

auto clampValue(WarperType value) -> WarperType {
  if (value > kMaxValue) {
    return kMaxValue;
  }

  if (value < kMinValue) {
    return kMinValue;
  }

  return value;
}

}  // namespace

namespace vva {

auto ClampedOperationWarper::addition(
    const OperandType& a, const OperandType& b) -> ClampedOperationWarper::OperandType {
  const auto result = add<WarperType>(a, b);

  const auto clamped_result = clampValue(result);
  return static_cast<OperandType>(clamped_result);
}

auto ClampedOperationWarper::subtraction(
    const OperandType& a, const OperandType& b) -> ClampedOperationWarper::OperandType {
  const auto result = subtract<WarperType>(a, b);

  const auto clamped_result = clampValue(result);
  return static_cast<OperandType>(clamped_result);
}

auto ClampedOperationWarper::multiplication(
    const OperandType& a, const OperandType& b) -> ClampedOperationWarper::OperandType {
  const auto result = multiply<WarperType>(a, b);

  const auto clamped_result = clampValue(result);
  return static_cast<OperandType>(clamped_result);
}

auto ClampedOperationWarper::division(
    const OperandType& a, const OperandType& b) -> ClampedOperationWarper::OperandType {
  if (b == 0) {
    throw std::invalid_argument("Division by zero");
  }

  const auto result = divide<WarperType>(a, b);
  return static_cast<OperandType>(result);
}

}  // namespace vva