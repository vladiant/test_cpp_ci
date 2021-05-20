#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <i_warper.hpp>
#include <limits>
#include <stdexcept>

namespace {
using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();

template <typename Func, typename... Args>
int16_t CallMock(vva::IOperationWarper& warper, Func func, Args... args) {
  return std::invoke(func, warper, args...);
}

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

class MockedWarperTest : public testing::Test {
 protected:
  MockWarper mockWarper;
};

TEST_F(MockedWarperTest, MockedWarperTestAdd_OneToTwo_Three) {
  EXPECT_CALL(mockWarper, addition(1, 2)).Times(1).WillOnce(Return(3));

  EXPECT_EQ(CallMock(mockWarper, &IOperationWarper::addition, 1, 2), 3);
}

// This test intentionally produces wrong result
TEST_F(MockedWarperTest, MockedWarperTestAdd_OneToTwo_Four) {
  EXPECT_CALL(mockWarper, addition(_, _)).Times(1).WillOnce(Return(4));

  EXPECT_EQ(CallMock(mockWarper, &IOperationWarper::addition, 1, 2), 4);
}

TEST_F(MockedWarperTest, MockedWarperTestAdd_SignedIntOverflowException) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;

  EXPECT_CALL(mockWarper, addition(a, b))
      .Times(1)
      .WillOnce(Throw(std::overflow_error("REQUIRE_THROWS_MATCHES")));

  EXPECT_THROW(CallMock(mockWarper, &IOperationWarper::addition, a, b),
               std::overflow_error);
}

TEST_F(MockedWarperTest, MockedWarperTestAdd_SignedIntOverflowClamped) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;

  EXPECT_CALL(mockWarper, addition(a, b)).Times(1).WillOnce(Return(a));

  EXPECT_EQ(CallMock(mockWarper, &IOperationWarper::addition, a, b), a);
}

}  // namespace vva
