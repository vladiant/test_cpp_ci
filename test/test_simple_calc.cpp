#include <utest/utest.h>

#include <cstdint>
#include <simple_calc.hpp>

namespace vva {
UTEST(TestAdd_OneToTwo_Three, simple_calc) { EXPECT_EQ(add(1, 2), 3); }

UTEST(TestAdd_UnsignedIntOverflow, simple_calc) {
  constexpr uint8_t a = 255;
  constexpr uint8_t b = 1;
  // Note: 8 bit integer will be printed as char
  EXPECT_EQ(add(a, b), 0);
}

UTEST(TestAdd_SignedIntOverflow, simple_calc) {
  constexpr int8_t a = 127;
  constexpr int8_t b = 1;
  // Note: 8 bit integer will be printed as char
  EXPECT_EQ(int(add(a, b)), -128);
}

UTEST(TestSubtract_ThreeByFive_Two, simple_calc) {
  EXPECT_EQ(subtract(5, 3), 2);
}

UTEST(TestMultiply_FiveBySix_Thirty, simple_calc) {
  EXPECT_EQ(multiply(5, 6), 30);
}

UTEST(TestDivide_TenByTwo_Five, simple_calc) { EXPECT_EQ(divide(10, 2), 5); }

}  // namespace vva
