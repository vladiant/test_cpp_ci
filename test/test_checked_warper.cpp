#include <utest/utest.h>
#include <checked_warper.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace {
constexpr auto kMaxValue = (std::numeric_limits<int16_t>::max)();
constexpr auto kMinValue = (std::numeric_limits<int16_t>::min)();
}  // namespace

namespace vva {
struct CheckedWarperTest {
  CheckedOperationWarper warper;
};

UTEST_F_SETUP(CheckedWarperTest) {
  static_cast<void>(utest_fixture->warper);
}

UTEST_F_TEARDOWN(CheckedWarperTest) {
  static_cast<void>(utest_fixture->warper);
}

UTEST_F(CheckedWarperTest, CheckedWarperTestAdd_OneToTwo_Three) {
  EXPECT_EQ(utest_fixture->warper.addition(1, 2) , 3);
}

// UTEST_F(CheckedWarperTest,
//                  CheckedWarperTestAdd_SignedIntOverflow_Exception) {
//   constexpr auto a = kMaxValue;
//   constexpr int16_t b = 1;
//   EXPECT_EQ_THROWS_AS(utest_fixture->warper.addition(a, b), std::overflow_error);
// }

// UTEST_F(CheckedWarperTest,
//                  CheckedWarperTestAdd_SignedIntUnderflow_Exception) {
//   constexpr auto a = kMinValue;
//   constexpr int16_t b = -1;
//   EXPECT_EQ_THROWS_AS(utest_fixture->warper.addition(a, b), std::underflow_error);
// }

UTEST_F(CheckedWarperTest, CheckedWarperTestSubtract_ThreeByFive_Two) {
  EXPECT_EQ(utest_fixture->warper.subtraction(5, 3) , 2);
}

// UTEST_F(CheckedWarperTest,
//                  CheckedWarperTestSubtract_SignedIntOverflow_Exception) {
//   constexpr auto a = kMinValue;
//   constexpr int16_t b = 1;
//   EXPECT_EQ_THROWS_AS(utest_fixture->warper.subtraction(a, b), std::underflow_error);
// }

// UTEST_F(CheckedWarperTest,
//                  CheckedWarperTestSubtract_SignedIntUnderflow_Exception) {
//   constexpr auto a = kMaxValue;
//   constexpr int16_t b = -1;
//   EXPECT_EQ_THROWS_AS(utest_fixture->warper.subtraction(a, b), std::overflow_error);
// }

UTEST_F(CheckedWarperTest,
                 CheckedWarperTestMultiply_FiveBySix_Thirty) {
  EXPECT_EQ(utest_fixture->warper.multiplication(5, 6) , 30);
}

// UTEST_F(CheckedWarperTest,
//                  CheckedWarperTestMultiply_SignedIntOverflow_Exception) {
//   constexpr auto a = kMaxValue;
//   constexpr int16_t b = 2;
//   EXPECT_EQ_THROWS_AS(utest_fixture->warper.multiplication(a, b), std::overflow_error);
// }

// UTEST_F(CheckedWarperTest,
//                  CheckedWarperTestMultiply_SignedIntUnderflow_Exception) {
//   constexpr auto a = kMinValue;
//   constexpr int16_t b = 2;
//   EXPECT_EQ_THROWS_AS(utest_fixture->warper.multiplication(a, b), std::underflow_error);
// }

UTEST_F(CheckedWarperTest, CheckedWarperTestDivide_TenByTwo_Five) {
  EXPECT_EQ(utest_fixture->warper.division(10, 2) , 5);
}

// UTEST_F(CheckedWarperTest,
//                  CheckedWarperTestDivide_DivisionByZero_Exception) {
//   constexpr auto a = 10;
//   constexpr int16_t b = 0;
//   EXPECT_EQ_THROWS_AS(utest_fixture->warper.division(a, b), std::invalid_argument);
// }

}  // namespace vva
