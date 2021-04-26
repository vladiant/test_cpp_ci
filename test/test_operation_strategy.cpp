#include <basic_warper.hpp>
#include <catch2/catch.hpp>
#include <checked_warper.hpp>
#include <clamped_warper.hpp>
#include <cstdint>
#include <operation_strategy.hpp>

namespace vva {

TEST_CASE("GeneralOperationStrategy", "[operation-strategy-logic]") {
  BasicOperationWarper basic_warper;
  CheckedOperationWarper checked_warper;
  ClampedOperationWarper clamped_warper;

  IOperationWarper* i =
      GENERATE_REF(&basic_warper, &checked_warper, &clamped_warper);

  REQUIRE(nullptr != i);
  OperationStrategy test_strategy(*i);

  REQUIRE(test_strategy(6, 2) == 4);
}

}  // namespace vva
