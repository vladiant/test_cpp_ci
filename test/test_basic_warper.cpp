#include <basic_warper.hpp>
#include <doctest/doctest.h>
#include <cstdint>
#include <limits>

namespace {
constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();
}  // namespace

namespace vva {
class BasicWarperTest {
 protected:
  BasicOperationWarper warper;
};

 TEST_CASE_FIXTURE(BasicWarperTest, "BasicWarperTestAdd_OneToTwo_Three [basic-warper]") {
  REQUIRE(warper.addition(1, 2) == 3);
}

 TEST_CASE_FIXTURE(BasicWarperTest, "BasicWarperTestAdd_SignedIntOverflow [basic-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  REQUIRE(warper.addition(a, b) == kMinValue);
}

 TEST_CASE_FIXTURE(BasicWarperTest, "BasicWarperTestSubtract_ThreeByFive_Two [basic-warper]") {
  REQUIRE(warper.subtraction(5, 3) == 2);
}

 TEST_CASE_FIXTURE(BasicWarperTest, "BasicWarperTestMultiply_FiveBySix_Thirty [basic-warper]") {
  REQUIRE(warper.multiplication(5, 6) == 30);
}

 TEST_CASE_FIXTURE(BasicWarperTest, "BasicWarperTestDivide_TenByTwo_Five [basic-warper]") {
  REQUIRE(warper.division(10, 2) == 5);
}

}  // namespace vva
