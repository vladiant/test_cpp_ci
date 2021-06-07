#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <i_warper.hpp>
#include <limits>
#include <operation_strategy.hpp>

namespace {
using ::testing::Return;
}  // namespace

namespace vva {

class MockWarper : public IOperationWarper {
 public:
  virtual ~MockWarper() {}

  MOCK_METHOD2(addition, int16_t(const int16_t&, const int16_t&));

  MOCK_METHOD2(subtraction, int16_t(const int16_t&, const int16_t&));

  MOCK_METHOD2(multiplication, int16_t(const int16_t&, const int16_t&));

  MOCK_METHOD2(division, int16_t(const int16_t&, const int16_t&));
};

class MockedOperationStrategyTest : public testing::Test {
 protected:
  MockWarper mockWarper_;
};

TEST_F(MockedOperationStrategyTest, MockOperationStrategy_Arg_Result) {
  constexpr int16_t first_arg = 6;
  constexpr int16_t second_arg = 2;
  constexpr int16_t operation_result = 4;

  constexpr int16_t first_stage_result = 8;
  constexpr int16_t second_stage_result = 16;
  constexpr int16_t third_stage_result = 4;

  EXPECT_CALL(mockWarper_, addition(first_arg, second_arg))
      .Times(1)
      .WillOnce(Return(first_stage_result));
  EXPECT_CALL(mockWarper_, multiplication(first_stage_result, 2))
      .Times(1)
      .WillOnce(Return(second_stage_result));
  EXPECT_CALL(mockWarper_, subtraction(first_arg, second_arg))
      .Times(1)
      .WillOnce(Return(third_stage_result));
  EXPECT_CALL(mockWarper_, division(second_stage_result, third_stage_result))
      .Times(1)
      .WillOnce(Return(operation_result));

  OperationStrategy test_strategy(mockWarper_);

  EXPECT_EQ(test_strategy(first_arg, second_arg), operation_result);
}

}  // namespace vva
