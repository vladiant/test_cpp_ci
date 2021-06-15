#include <catch2/catch.hpp>
#include <checked_warper.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <utility>


namespace {
constexpr auto kMaxValue = std::numeric_limits<int16_t>::max();
constexpr auto kMinValue = std::numeric_limits<int16_t>::min();
}  // namespace

namespace Catch::Matchers {
class ExceptionWatcher : public MatcherBase<std::exception> {
 public:
  ExceptionWatcher(std::string  expected_message)
      : expected_message_(std::move(expected_message)) {}

  auto match(std::exception const& e) const -> bool override {
    return e.what() == expected_message_;
  }

  auto describe() const -> std::string override {
    return "compare the exception what() message with \"" + expected_message_ +
           "\".";
  }

 private:
  std::string expected_message_;
};

inline auto ExceptionMessage(std::string const& expeted_message) -> ExceptionWatcher {
  return ExceptionWatcher(expeted_message);
}

}  // namespace Catch

namespace vva {
class CheckedWarperTest {
 protected:
  CheckedOperationWarper warper_;
};

TEST_CASE_METHOD(CheckedWarperTest, "CheckedWarperTestAdd_OneToTwo_Three",
                 "[checked-warper]") {
  REQUIRE(warper_.addition(1, 2) == 3);
}

TEST_CASE_METHOD(CheckedWarperTest,
                 "CheckedWarperTestAdd_SignedIntOverflow_Exception",
                 "[checked-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 1;
  REQUIRE_THROWS_MATCHES(warper_.addition(a, b), std::overflow_error,
                         Catch::Matchers::ExceptionMessage("Overflow"));
}

TEST_CASE_METHOD(CheckedWarperTest,
                 "CheckedWarperTestAdd_SignedIntUnderflow_Exception",
                 "[checked-warper]") {
  constexpr auto a = kMinValue;
  constexpr int16_t b = -1;

  REQUIRE_THROWS_MATCHES(warper_.addition(a, b), std::underflow_error,
                         Catch::Matchers::ExceptionMessage("Underflow"));
}

TEST_CASE_METHOD(CheckedWarperTest, "CheckedWarperTestSubtract_ThreeByFive_Two",
                 "[checked-warper]") {
  REQUIRE(warper_.subtraction(5, 3) == 2);
}

TEST_CASE_METHOD(CheckedWarperTest,
                 "CheckedWarperTestSubtract_SignedIntOverflow_Exception",
                 "[checked-warper]") {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 1;
  REQUIRE_THROWS_AS(warper_.subtraction(a, b), std::underflow_error);
}

TEST_CASE_METHOD(CheckedWarperTest,
                 "CheckedWarperTestSubtract_SignedIntUnderflow_Exception",
                 "[checked-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = -1;
  REQUIRE_THROWS_AS(warper_.subtraction(a, b), std::overflow_error);
}

TEST_CASE_METHOD(CheckedWarperTest,
                 "CheckedWarperTestMultiply_FiveBySix_Thirty",
                 "[checked-warper]") {
  REQUIRE(warper_.multiplication(5, 6) == 30);
}

TEST_CASE_METHOD(CheckedWarperTest,
                 "CheckedWarperTestMultiply_SignedIntOverflow_Exception",
                 "[checked-warper]") {
  constexpr auto a = kMaxValue;
  constexpr int16_t b = 2;
  REQUIRE_THROWS_AS(warper_.multiplication(a, b), std::overflow_error);
}

TEST_CASE_METHOD(CheckedWarperTest,
                 "CheckedWarperTestMultiply_SignedIntUnderflow_Exception",
                 "[checked-warper]") {
  constexpr auto a = kMinValue;
  constexpr int16_t b = 2;
  REQUIRE_THROWS_AS(warper_.multiplication(a, b), std::underflow_error);
}

TEST_CASE_METHOD(CheckedWarperTest, "CheckedWarperTestDivide_TenByTwo_Five",
                 "[checked-warper]") {
  REQUIRE(warper_.division(10, 2) == 5);
}

TEST_CASE_METHOD(CheckedWarperTest,
                 "CheckedWarperTestDivide_DivisionByZero_Exception",
                 "[checked-warper]") {
  constexpr auto a = 10;
  constexpr int16_t b = 0;
  REQUIRE_THROWS_MATCHES(warper_.division(a, b), std::invalid_argument,
                         Catch::Matchers::ExceptionMessage("Division by zero"));
}

}  // namespace vva
