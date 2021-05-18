#include <gtest/gtest.h>

#include <checked_warper.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace {
constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();
}  // namespace

namespace vva {
class CheckedWarperTest : public testing::Test {
 protected:
  CheckedOperationWarper warper;
};

TEST_F(CheckedWarperTest, CheckedWarperTestAdd_OneToTwo_Three) {
  EXPECT_EQ(warper.addition(1, 2), 3);
}

TEST_F(CheckedWarperTest, CheckedWarperTestAdd_SignedIntOverflow_Exception) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  EXPECT_THROW(warper.addition(a, b), std::overflow_error);
}

TEST_F(CheckedWarperTest, CheckedWarperTestAdd_SignedIntUnderflow_Exception) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = -1;
  EXPECT_THROW(warper.addition(a, b), std::underflow_error);
}

TEST_F(CheckedWarperTest, CheckedWarperTestSubtract_ThreeByFive_Two) {
  EXPECT_EQ(warper.subtraction(5, 3), 2);
}

TEST_F(CheckedWarperTest,
       CheckedWarperTestSubtract_SignedIntOverflow_Exception) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 1;
  EXPECT_THROW(warper.subtraction(a, b), std::underflow_error);
}

TEST_F(CheckedWarperTest,
       CheckedWarperTestSubtract_SignedIntUnderflow_Exception) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = -1;
  EXPECT_THROW(warper.subtraction(a, b), std::overflow_error);
}

TEST_F(CheckedWarperTest, CheckedWarperTestMultiply_FiveBySix_Thirty) {
  EXPECT_EQ(warper.multiplication(5, 6), 30);
}

TEST_F(CheckedWarperTest,
       CheckedWarperTestMultiply_SignedIntOverflow_Exception) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 2;
  EXPECT_THROW(warper.multiplication(a, b), std::overflow_error);
}

TEST_F(CheckedWarperTest,
       CheckedWarperTestMultiply_SignedIntUnderflow_Exception) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 2;
  EXPECT_THROW(warper.multiplication(a, b), std::underflow_error);
}

TEST_F(CheckedWarperTest, CheckedWarperTestDivide_TenByTwo_Five) {
  EXPECT_EQ(warper.division(10, 2), 5);
}

TEST_F(CheckedWarperTest, CheckedWarperTestDivide_DivisionByZero_Exception) {
  constexpr auto a = 10;
  constexpr int16_t b = 0;
  EXPECT_THROW(warper.division(a, b), std::invalid_argument);
}

}  // namespace vva
