#include <catch2/catch.hpp>
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

namespace Catch {
namespace Matchers {
class ExceptionWatcher : public MatcherBase<std::exception> {
 public:
  ExceptionWatcher(std::string const& expected_message)
      : expected_message_(expected_message) {}

  bool match(std::exception const& e) const override {
    return e.what() == expected_message_;
  }

  std::string describe() const override {
    return "compare the exception what() message with \"" + expected_message_ +
           "\".";
  }

 private:
  std::string expected_message_;
};

ExceptionWatcher ExceptionMessage(std::string const& expeted_message) {
  return ExceptionWatcher(expeted_message);
}

}  // namespace Matchers
}  // namespace Catch

namespace vva {
class MockedWarperTest {
 protected:
  fakeit::Mock<IOperationWarper> mockWarper_;
};

TEST_CASE_METHOD(MockedWarperTest, "MockedWarperTestAdd_OneToTwo_Three",
                 "[mock-warper]") {
  When(Method(mockWarper_, addition).Using(1, 2)).Return(3);

  REQUIRE(CallMock(mockWarper_.get(), &IOperationWarper::addition, 1, 2) == 3);
}

// This test intentionally produces wrong result
TEST_CASE_METHOD(MockedWarperTest, "MockedWarperTestAdd_OneToTwo_Four",
                 "[mock-warper]") {
  When(Method(mockWarper_, addition)).Return(4);

  REQUIRE(CallMock(mockWarper_.get(), &IOperationWarper::addition, 1, 2) == 4);
}

TEST_CASE_METHOD(MockedWarperTest,
                 "MockedWarperTestAdd_SignedIntOverflowException",
                 "[mock-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;

  // Message intentionally is different than the actual one
  const auto exception_message = "Overflow Error";

  When(Method(mockWarper_, addition).Using(a, b))
      .Throw(std::overflow_error(exception_message));

  REQUIRE_THROWS_MATCHES(
      CallMock(mockWarper_.get(), &IOperationWarper::addition, a, b),
      std::overflow_error,
      Catch::Matchers::ExceptionMessage(exception_message));
}

TEST_CASE_METHOD(MockedWarperTest,
                 "MockedWarperTestAdd_SignedIntOverflowClamped",
                 "[mock-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;

  When(Method(mockWarper_, addition).Using(a, b)).Return(a);

  REQUIRE(CallMock(mockWarper_.get(), &IOperationWarper::addition, a, b) == a);
}

}  // namespace vva
