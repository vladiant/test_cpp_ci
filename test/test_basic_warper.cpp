#include <basic_warper.hpp>
#include <utest/utest.h>
#include <cstdint>
#include <limits>

namespace {
constexpr auto kMaxValue = (std::numeric_limits<int16_t>::max)();
constexpr auto kMinValue = (std::numeric_limits<int16_t>::min)();
}  // namespace

namespace vva {
struct BasicWarperTest {
  BasicOperationWarper warper;
};

UTEST_F_SETUP(BasicWarperTest) {
  static_cast<void>(utest_fixture->warper);
}

UTEST_F_TEARDOWN(BasicWarperTest) {
  static_cast<void>(utest_fixture->warper);
}

UTEST_F(BasicWarperTest, BasicWarperTestAdd_OneToTwo_Three) {
  EXPECT_EQ(utest_fixture->warper.addition(1, 2) , 3);
}

UTEST_F(BasicWarperTest, BasicWarperTestAdd_SignedIntOverflow) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  EXPECT_EQ(utest_fixture->warper.addition(a, b) , kMinValue);
}

UTEST_F(BasicWarperTest, BasicWarperTestSubtract_ThreeByFive_Two) {
  EXPECT_EQ(utest_fixture->warper.subtraction(5, 3) , 2);
}

UTEST_F(BasicWarperTest, BasicWarperTestMultiply_FiveBySix_Thirty) {
  EXPECT_EQ(utest_fixture->warper.multiplication(5, 6) , 30);
}

UTEST_F(BasicWarperTest, BasicWarperTestDivide_TenByTwo_Five) {
  EXPECT_EQ(utest_fixture->warper.division(10, 2) , 5);
}

}  // namespace vva
