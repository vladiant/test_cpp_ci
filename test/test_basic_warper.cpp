#include <gtest/gtest.h>

#include <basic_warper.hpp>
#include <cstdint>
#include <limits>

namespace {
constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();
}  // namespace

namespace vva {
class BasicWarperTest : public testing::Test {
 protected:
  BasicOperationWarper warper;
};

TEST_F(BasicWarperTest, BasicWarperTestAdd_OneToTwo_Three) {
  EXPECT_EQ(warper.addition(1, 2), 3);
}

TEST_F(BasicWarperTest, BasicWarperTestAdd_SignedIntOverflow) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  EXPECT_EQ(warper.addition(a, b), kMinValue);
}

TEST_F(BasicWarperTest, BasicWarperTestSubtract_ThreeByFive_Two) {
  EXPECT_EQ(warper.subtraction(5, 3), 2);
}

TEST_F(BasicWarperTest, BasicWarperTestMultiply_FiveBySix_Thirty) {
  EXPECT_EQ(warper.multiplication(5, 6), 30);
}

TEST_F(BasicWarperTest, BasicWarperTestDivide_TenByTwo_Five) {
  EXPECT_EQ(warper.division(10, 2), 5);
}

}  // namespace vva
