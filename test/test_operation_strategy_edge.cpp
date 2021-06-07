#include <gtest/gtest.h>

#include <basic_warper.hpp>
#include <checked_warper.hpp>
#include <clamped_warper.hpp>
#include <cstdint>
#include <limits>
#include <operation_strategy.hpp>
#include <stdexcept>

namespace {
constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();
}  // namespace

namespace vva {

class StrategyClampedTest : public testing::Test {
 protected:
  ClampedOperationWarper warper_;
  OperationStrategy test_strategy_{warper_};
};

TEST_F(StrategyClampedTest, StrategyClampedTest_FirstStageOverflow_Exception) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  EXPECT_EQ(test_strategy_(a, b), 1);
}

TEST_F(StrategyClampedTest, StrategyClampedTest_FirstStageUnderflow_Exception) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = -1;
  EXPECT_EQ(test_strategy_(a, b), 1);
}

TEST_F(StrategyClampedTest, StrategyClampedTest_SecondStageOverflow_Exception) {
  constexpr auto a = kMaxValue / 2;
  constexpr int16_t b = 1;
  EXPECT_EQ(test_strategy_(a, b), 2);
}

TEST_F(StrategyClampedTest,
       StrategyClampedTest_SecondStageUnderflow_Exception) {
  constexpr auto a = kMinValue / 2;
  constexpr int16_t b = -1;
  EXPECT_EQ(test_strategy_(a, b), 2);
}

TEST_F(StrategyClampedTest, StrategyClampedTest_ThirdStageOverflow_Exception) {
  constexpr auto a = 1 + kMaxValue / 2;
  constexpr int16_t b = kMinValue / 2;
  EXPECT_EQ(test_strategy_(a, b), 0);
}

TEST_F(StrategyClampedTest, StrategyClampedTest_ThirdStageUnderflow_Exception) {
  constexpr auto a = 1 - kMaxValue / 2;
  constexpr int16_t b = kMinValue / 2;
  EXPECT_EQ(test_strategy_(a, b), kMinValue / 2);
}

TEST_F(StrategyClampedTest,
       StrategyClampedTest_ThirdStagedivisionByZero_Exception) {
  constexpr auto a = 1;
  constexpr int16_t b = 1;
  EXPECT_THROW(test_strategy_(a, b), std::invalid_argument);
}

class StrategyCheckedTest : public testing::Test {
 protected:
  CheckedOperationWarper warper_;
  OperationStrategy test_strategy_{warper_};
};

TEST_F(StrategyCheckedTest, StrategyCheckedTest_FirstStageOverflow_Exception) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  EXPECT_THROW(test_strategy_(a, b), std::overflow_error);
}

TEST_F(StrategyCheckedTest, StrategyCheckedTest_FirstStageUnderflow_Exception) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = -1;
  EXPECT_THROW(test_strategy_(a, b), std::underflow_error);
}

TEST_F(StrategyCheckedTest, StrategyCheckedTest_SecondStageOverflow_Exception) {
  constexpr auto a = kMaxValue / 2;
  constexpr int16_t b = 1;
  EXPECT_THROW(test_strategy_(a, b), std::overflow_error);
}

TEST_F(StrategyCheckedTest,
       StrategyCheckedTest_SecondStageUnderflow_Exception) {
  constexpr auto a = kMinValue / 2;
  constexpr int16_t b = -1;
  EXPECT_THROW(test_strategy_(a, b), std::underflow_error);
}

TEST_F(StrategyCheckedTest, StrategyCheckedTest_ThirdStageOverflow_Exception) {
  constexpr auto a = 1 + kMaxValue / 2;
  constexpr int16_t b = kMinValue / 2;
  EXPECT_THROW(test_strategy_(a, b), std::overflow_error);
}

TEST_F(StrategyCheckedTest, StrategyCheckedTest_ThirdStageUnderflow_Exception) {
  constexpr auto a = 1 - kMaxValue / 2;
  constexpr int16_t b = kMinValue / 2;
  EXPECT_THROW(test_strategy_(a, b), std::underflow_error);
}

TEST_F(StrategyCheckedTest,
       StrategyCheckedTest_ThirdStagedivisionByZero_Exception) {
  constexpr auto a = 1;
  constexpr int16_t b = 1;
  EXPECT_THROW(test_strategy_(a, b), std::invalid_argument);
}

}  // namespace vva
