#include <gtest/gtest.h>

#include <basic_warper.hpp>
#include <checked_warper.hpp>
#include <clamped_warper.hpp>
#include <cstdint>
#include <operation_strategy.hpp>

namespace vva {

template <typename T>
struct OperationStrategyLogic : public testing::Test {
  using WarperType = T;
};

typedef testing::Types<BasicOperationWarper, CheckedOperationWarper,
                       ClampedOperationWarper>
    Warpers;

TYPED_TEST_SUITE(OperationStrategyLogic, Warpers);

TYPED_TEST(OperationStrategyLogic, GeneralOperationStrategy) {
  using WarperType = typename TestFixture::WarperType;

  WarperType warper;

  OperationStrategy test_strategy(warper);

  EXPECT_EQ(test_strategy(6, 2), 4);
}

}  // namespace vva
