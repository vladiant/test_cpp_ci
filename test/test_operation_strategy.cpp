#include <basic_warper.hpp>
#include <catch2/catch.hpp>
#include <checked_warper.hpp>
#include <clamped_warper.hpp>
#include <cstdint>
#include <operation_strategy.hpp>

namespace vva {

TEMPLATE_TEST_CASE("GeneralOperationStrategy", "[operation-strategy-logic]",
                   BasicOperationWarper, CheckedOperationWarper,
                   ClampedOperationWarper) {
  TestType warper;
  OperationStrategy test_strategy(warper);

  REQUIRE(test_strategy(6, 2) == 4);
}

}  // namespace vva
