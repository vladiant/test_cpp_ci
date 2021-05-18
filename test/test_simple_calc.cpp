#include <gtest/gtest.h>

#include <cstdint>
#include <simple_calc.hpp>

namespace vva {
TEST(SimpleCalc, TestAdd_OneToTwo_Three) { EXPECT_EQ(add(1, 2), 3); }

TEST(SimpleCalc, TestAdd_UnsignedIntOverflow) {
  constexpr uint8_t a = 255;
  constexpr uint8_t b = 1;
  // Note: 8 bit integer will be printed as char
  EXPECT_EQ(add(a, b), 0);
}

TEST(SimpleCalc, TestAdd_SignedIntOverflow) {
  constexpr int8_t a = 127;
  constexpr int8_t b = 1;
  // Note: 8 bit integer will be printed as char
  EXPECT_EQ(int(add(a, b)), -128);
}

TEST(SimpleCalc, TestSubtract_ThreeByFive_Two) { EXPECT_EQ(subtract(5, 3), 2); }

TEST(SimpleCalc, TestMultiply_FiveBySix_Thirty) {
  EXPECT_EQ(multiply(5, 6), 30);
}

TEST(SimpleCalc, TestDivide_TenByTwo_Five) { EXPECT_EQ(divide(10, 2), 5); }

}  // namespace vva
