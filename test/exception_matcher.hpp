#pragma once
#include <catch2/catch.hpp>
#include <string>

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

inline ExceptionWatcher ExceptionMessage(std::string const& expected_message) {
  return ExceptionWatcher(expected_message);
}

}  // namespace Matchers
}  // namespace Catch
