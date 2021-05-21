#include <utest/utest.h>
#include <cstdint>
#include <fakeit/fakeit.hpp>
#include <i_warper.hpp>
#include <limits>
#include <stdexcept>

namespace {
using fakeit::Mock;
using fakeit::When;

constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();

template <typename Func, typename... Args>
int16_t CallMock(vva::IOperationWarper& warper, Func func, Args... args) {
  return std::invoke(func, warper, args...);
}

}  // namespace

namespace vva {
struct MockedWarperTest {
  fakeit::Mock<IOperationWarper> mockWarper;
};

UTEST_F_SETUP(MockedWarperTest) {
  static_cast<void>(utest_fixture->mockWarper);
}

UTEST_F_TEARDOWN(MockedWarperTest) {
  static_cast<void>(utest_fixture->mockWarper);
}

UTEST_F(MockedWarperTest, MockedWarperTestAdd_OneToTwo_Three) {
  When(Method(utest_fixture->mockWarper, addition).Using(1, 2)).Return(3);

  EXPECT_EQ(CallMock(utest_fixture->mockWarper.get(), &IOperationWarper::addition, 1, 2) , 3);
}

// This test intentionally produces wrong result
UTEST_F(MockedWarperTest, MockedWarperTestAdd_OneToTwo_Four) {
  When(Method(utest_fixture->mockWarper, addition)).Return(4);

  EXPECT_EQ(CallMock(utest_fixture->mockWarper.get(), &IOperationWarper::addition, 1, 2) , 4);
}

// UTEST_F(MockedWarperTest,
//                  MockedWarperTestAdd_SignedIntOverflowException) {
//   constexpr auto a = kMaxValue;
//   constexpr int16_t b = 1;

//   When(Method(utest_fixture->mockWarper, addition).Using(a, b))
//       .Throw(std::overflow_error(EXPECT_EQ_THROWS_MATCHES));

//   EXPECT_EQ_THROWS_AS(
//       CallMock(utest_fixture->mockWarper.get(), &IOperationWarper::addition, a, b),
//       std::overflow_error);
// }

UTEST_F(MockedWarperTest,
                 MockedWarperTestAdd_SignedIntOverflowClamped) {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;

  When(Method(utest_fixture->mockWarper, addition).Using(a, b)).Return(a);

  EXPECT_EQ(CallMock(utest_fixture->mockWarper.get(), &IOperationWarper::addition, a, b) , a);
}

}  // namespace vva
