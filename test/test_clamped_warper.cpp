#include <catch2/catch.hpp>
#include <clamped_warper.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace {
constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();
}  // namespace

namespace vva {
class ClampedWarperTest {
 protected:
  ClampedOperationWarper warper;
};

TEST_CASE_METHOD(ClampedWarperTest, "ClampedWarperTestAdd_OneToTwo_Three",
                 "[clamped-warper]") {
  REQUIRE(warper.addition(1, 2) == 3);
}

TEST_CASE_METHOD(ClampedWarperTest,
                 "ClampedWarperTestAdd_SignedIntOverflow_ClampedToMax",
                 "[clamped-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  REQUIRE(warper.addition(a, b) == kMaxValue);
}

TEST_CASE_METHOD(ClampedWarperTest,
                 "ClampedWarperTestAdd_SignedIntUnderflow_ClampedToMin",
                 "[clamped-warper]") {
  constexpr auto a = kMinValue;
  constexpr int16_t b = -1;
  REQUIRE(warper.addition(a, b) == kMinValue);
}

TEST_CASE_METHOD(ClampedWarperTest, "ClampedWarperTestSubtract_ThreeByFive_Two",
                 "[clamped-warper]") {
  REQUIRE(warper.subtraction(5, 3) == 2);
}

TEST_CASE_METHOD(ClampedWarperTest,
                 "ClampedWarperTestSubtract_SignedIntOverflow_ClampedToMax",
                 "[clamped-warper]") {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 1;
  REQUIRE(warper.subtraction(a, b) == kMinValue);
}

TEST_CASE_METHOD(ClampedWarperTest,
                 "ClampedWarperTestSubtract_SignedIntUnderflow_ClampedToMin",
                 "[clamped-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = -1;
  REQUIRE(warper.subtraction(a, b) == kMaxValue);
}

TEST_CASE_METHOD(ClampedWarperTest,
                 "ClampedWarperTestMultiply_FiveBySix_Thirty",
                 "[clamped-warper]") {
  REQUIRE(warper.multiplication(5, 6) == 30);
}

TEST_CASE_METHOD(ClampedWarperTest,
                 "ClampedWarperTestMultiply_SignedIntOverflow_ClampedToMax",
                 "[clamped-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 2;
  REQUIRE(warper.multiplication(a, b) == kMaxValue);
}

TEST_CASE_METHOD(ClampedWarperTest,
                 "ClampedWarperTestMultiply_SignedIntUnderflow_ClampedToMin",
                 "[clamped-warper]") {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 2;
  REQUIRE(warper.multiplication(a, b) == kMinValue);
}

TEST_CASE_METHOD(ClampedWarperTest, "ClampedWarperTestDivide_TenByTwo_Five",
                 "[clamped-warper]") {
  REQUIRE(warper.division(10, 2) == 5);
}

TEST_CASE_METHOD(ClampedWarperTest,
                 "ClampedWarperTestDivide_DivisionByZero_Exception",
                 "[clamped-warper]") {
  constexpr auto a = 10;
  constexpr int16_t b = 0;
  REQUIRE_THROWS_AS(warper.division(a, b), std::invalid_argument);
}

}  // namespace vva
