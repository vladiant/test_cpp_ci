#include <utest/utest.h>
#include <clamped_warper.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace {
constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();
}  // namespace

namespace vva {
struct ClampedWarperTest {
  ClampedOperationWarper warper;
};

UTEST_F_SETUP(ClampedWarperTest) {
  static_cast<void>(utest_fixture->warper);
}

UTEST_F_TEARDOWN(ClampedWarperTest) {
  static_cast<void>(utest_fixture->warper);
}

UTEST_F(ClampedWarperTest, ClampedWarperTestAdd_OneToTwo_Three) {
  EXPECT_EQ(utest_fixture->warper.addition(1, 2) , 3);
}

UTEST_F(ClampedWarperTest,
                 ClampedWarperTestAdd_SignedIntOverflow_ClampedToMax) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  EXPECT_EQ(utest_fixture->warper.addition(a, b) , kMaxValue);
}

UTEST_F(ClampedWarperTest,
                 ClampedWarperTestAdd_SignedIntUnderflow_ClampedToMin) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = -1;
  EXPECT_EQ(utest_fixture->warper.addition(a, b) , kMinValue);
}

UTEST_F(ClampedWarperTest, ClampedWarperTestSubtract_ThreeByFive_Two) {
  EXPECT_EQ(utest_fixture->warper.subtraction(5, 3) , 2);
}

UTEST_F(ClampedWarperTest,
                 ClampedWarperTestSubtract_SignedIntOverflow_ClampedToMax) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 1;
  EXPECT_EQ(utest_fixture->warper.subtraction(a, b) , kMinValue);
}

UTEST_F(ClampedWarperTest,
                 ClampedWarperTestSubtract_SignedIntUnderflow_ClampedToMin) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = -1;
  EXPECT_EQ(utest_fixture->warper.subtraction(a, b) , kMaxValue);
}

UTEST_F(ClampedWarperTest,
                 ClampedWarperTestMultiply_FiveBySix_Thirty) {
  EXPECT_EQ(utest_fixture->warper.multiplication(5, 6) , 30);
}

UTEST_F(ClampedWarperTest,
                 ClampedWarperTestMultiply_SignedIntOverflow_ClampedToMax) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 2;
  EXPECT_EQ(utest_fixture->warper.multiplication(a, b) , kMaxValue);
}

UTEST_F(ClampedWarperTest,
                 ClampedWarperTestMultiply_SignedIntUnderflow_ClampedToMin) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 2;
  EXPECT_EQ(utest_fixture->warper.multiplication(a, b) , kMinValue);
}

UTEST_F(ClampedWarperTest, ClampedWarperTestDivide_TenByTwo_Five) {
  EXPECT_EQ(utest_fixture->warper.division(10, 2) , 5);
}

// UTEST_F(ClampedWarperTest,
//                  ClampedWarperTestDivide_DivisionByZero_Exception) {
//   constexpr auto a = 10;
//   constexpr int16_t b = 0;
//   EXPECT_EQ_THROWS_AS(utest_fixture->warper.division(a, b), std::invalid_argument);
// }

}  // namespace vva
