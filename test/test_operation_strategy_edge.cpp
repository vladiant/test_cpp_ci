#include <basic_warper.hpp>
#include <utest/utest.h>
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

struct StrategyClampedTest {
  ClampedOperationWarper warper;
  OperationStrategy test_strategy{warper};
};

UTEST_F_SETUP(StrategyClampedTest) {
  static_cast<void>(utest_fixture->warper);
  static_cast<void>(utest_fixture->test_strategy);
}

UTEST_F_TEARDOWN(StrategyClampedTest) {
  static_cast<void>(utest_fixture->warper);
  static_cast<void>(utest_fixture->test_strategy);
}

UTEST_F(StrategyClampedTest,
                 StrategyClampedTest_FirstStageOverflow_Exception) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  EXPECT_EQ(utest_fixture->test_strategy(a, b) , 1);
}

UTEST_F(StrategyClampedTest,
                 StrategyClampedTest_FirstStageUnderflow_Exception) {
  constexpr auto a = kMinValue;
  constexpr int16_t b = -1;
  EXPECT_EQ(utest_fixture->test_strategy(a, b) , 1);
}

UTEST_F(StrategyClampedTest,
                 StrategyClampedTest_SecondStageOverflow_Exception) {
  constexpr auto a = kMaxValue / 2;
  constexpr int16_t b = 1;
  EXPECT_EQ(utest_fixture->test_strategy(a, b) , 2);
}

UTEST_F(StrategyClampedTest,
                 StrategyClampedTest_SecondStageUnderflow_Exception) {
  constexpr auto a = kMinValue / 2;
  constexpr int16_t b = -1;
  EXPECT_EQ(utest_fixture->test_strategy(a, b) , 2);
}

UTEST_F(StrategyClampedTest,
                 StrategyClampedTest_ThirdStageOverflow_Exception) {
  constexpr auto a = 1 + kMaxValue / 2;
  constexpr int16_t b = kMinValue / 2;
  EXPECT_EQ(utest_fixture->test_strategy(a, b) , 0);
}

UTEST_F(StrategyClampedTest,
                 StrategyClampedTest_ThirdStageUnderflow_Exception) {
  constexpr auto a = 1 - kMaxValue / 2;
  constexpr int16_t b = kMinValue / 2;
  EXPECT_EQ(utest_fixture->test_strategy(a, b) , kMinValue / 2);
}

// UTEST_F(StrategyClampedTest,
//                  StrategyClampedTest_ThirdStagedivisionByZero_Exception) {
//   constexpr auto a = 1;
//   constexpr int16_t b = 1;
//   EXPECT_EQ_THROWS_AS(test_strategy(a, b), std::invalid_argument);
// }

struct StrategyCheckedTest {
  CheckedOperationWarper warper;
  OperationStrategy test_strategy{warper};
};

UTEST_F_SETUP(StrategyCheckedTest) {
  static_cast<void>(utest_fixture->warper);
  static_cast<void>(utest_fixture->test_strategy);
}

UTEST_F_TEARDOWN(StrategyCheckedTest) {
  static_cast<void>(utest_fixture->warper);
  static_cast<void>(utest_fixture->test_strategy);
}

// UTEST_F(StrategyCheckedTest,
//                  StrategyCheckedTest_FirstStageOverflow_Exception) {
//   constexpr auto a = kMaxValue;
//   constexpr int16_t b = 1;
//   EXPECT_EQ_THROWS_AS(test_strategy(a, b), std::overflow_error);
// }

// UTEST_F(StrategyCheckedTest,
//                  StrategyCheckedTest_FirstStageUnderflow_Exception) {
//   constexpr auto a = kMinValue;
//   constexpr int16_t b = -1;
//   EXPECT_EQ_THROWS_AS(test_strategy(a, b), std::underflow_error);
// }

// UTEST_F(StrategyCheckedTest,
//                  StrategyCheckedTest_SecondStageOverflow_Exception) {
//   constexpr auto a = kMaxValue / 2;
//   constexpr int16_t b = 1;
//   EXPECT_EQ_THROWS_AS(test_strategy(a, b), std::overflow_error);
// }

// UTEST_F(StrategyCheckedTest,
//                  StrategyCheckedTest_SecondStageUnderflow_Exception) {
//   constexpr auto a = kMinValue / 2;
//   constexpr int16_t b = -1;
//   EXPECT_EQ_THROWS_AS(test_strategy(a, b), std::underflow_error);
// }

// UTEST_F(StrategyCheckedTest,
//                  StrategyCheckedTest_ThirdStageOverflow_Exception) {
//   constexpr auto a = 1 + kMaxValue / 2;
//   constexpr int16_t b = kMinValue / 2;
//   EXPECT_EQ_THROWS_AS(test_strategy(a, b), std::overflow_error);
// }

// UTEST_F(StrategyCheckedTest,
//                  StrategyCheckedTest_ThirdStageUnderflow_Exception) {
//   constexpr auto a = 1 - kMaxValue / 2;
//   constexpr int16_t b = kMinValue / 2;
//   EXPECT_EQ_THROWS_AS(test_strategy(a, b), std::underflow_error);
// }

// UTEST_F(StrategyCheckedTest,
//                  StrategyCheckedTest_ThirdStagedivisionByZero_Exception) {
//   constexpr auto a = 1;
//   constexpr int16_t b = 1;
//   EXPECT_EQ_THROWS_AS(test_strategy(a, b), std::invalid_argument);
// }

}  // namespace vva
