#include <catch2/catch.hpp>
#include <cstdint>
#include <simple_calc.hpp>

namespace vva {
TEST_CASE("TestAdd_OneToTwo_Three", "[single-file]") {
  REQUIRE(add(1, 2) == 3);
}

TEST_CASE("TestAdd_UnsignedIntOverflow", "[single-file]") {
  constexpr uint8_t a = 255;
  constexpr uint8_t b = 1;
  // Note: 8 bit integer will be printed as char
  REQUIRE(add(a, b) == 0);
}

TEST_CASE("TestAdd_SignedIntOverflow", "[single-file]") {
  constexpr int8_t a = 127;
  constexpr int8_t b = 1;
  // Note: 8 bit integer will be printed as char
  REQUIRE(int(add(a, b)) == -128);
}

TEST_CASE("TestSubtract_ThreeByFive_Two", "[single-file]") {
  REQUIRE(subtract(5, 3) == 2);
}

TEST_CASE("TestMultiply_FiveBySix_Thirty", "[single-file]") {
  REQUIRE(multiply(5, 6) == 30);
}

TEST_CASE("TestDivide_TenByTwo_Five", "[single-file]") {
  REQUIRE(divide(10, 2) == 5);
}

}  // namespace vva
