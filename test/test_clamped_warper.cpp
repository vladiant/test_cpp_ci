#include <gtest/gtest.h>

#include <clamped_warper.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace {
constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();
}  // namespace

namespace vva {
class ClampedWarperTest : public testing::Test {
 protected:
  ClampedOperationWarper warper;
};

TEST_F(ClampedWarperTest, ClampedWarperTestAdd_OneToTwo_Three) {
  EXPECT_EQ(warper.addition(1, 2), 3);
}

TEST_F(ClampedWarperTest, ClampedWarperTestAdd_SignedIntOverflow_ClampedToMax) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  EXPECT_EQ(warper.addition(a, b), kMaxValue);
}

TEST_F(ClampedWarperTest,
       ClampedWarperTestAdd_SignedIntUnderflow_ClampedToMin) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = -1;
  EXPECT_EQ(warper.addition(a, b), kMinValue);
}

TEST_F(ClampedWarperTest, ClampedWarperTestSubtract_ThreeByFive_Two) {
  EXPECT_EQ(warper.subtraction(5, 3), 2);
}

TEST_F(ClampedWarperTest,
       ClampedWarperTestSubtract_SignedIntOverflow_ClampedToMax) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 1;
  EXPECT_EQ(warper.subtraction(a, b), kMinValue);
}

TEST_F(ClampedWarperTest,
       ClampedWarperTestSubtract_SignedIntUnderflow_ClampedToMin) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = -1;
  EXPECT_EQ(warper.subtraction(a, b), kMaxValue);
}

TEST_F(ClampedWarperTest, ClampedWarperTestMultiply_FiveBySix_Thirty) {
  EXPECT_EQ(warper.multiplication(5, 6), 30);
}

TEST_F(ClampedWarperTest,
       ClampedWarperTestMultiply_SignedIntOverflow_ClampedToMax) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 2;
  EXPECT_EQ(warper.multiplication(a, b), kMaxValue);
}

TEST_F(ClampedWarperTest,
       ClampedWarperTestMultiply_SignedIntUnderflow_ClampedToMin) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 2;
  EXPECT_EQ(warper.multiplication(a, b), kMinValue);
}

TEST_F(ClampedWarperTest, ClampedWarperTestDivide_TenByTwo_Five) {
  EXPECT_EQ(warper.division(10, 2), 5);
}

TEST_F(ClampedWarperTest, ClampedWarperTestDivide_DivisionByZero_Exception) {
  constexpr auto a = 10;
  constexpr int16_t b = 0;
  EXPECT_THROW(warper.division(a, b), std::invalid_argument);
}

}  // namespace vva
