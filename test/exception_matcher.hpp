#pragma once
#include <catch2/catch.hpp>
#include <string>

namespace Catch {
namespace Matchers {
class ExceptionWatcher : public MatcherBase<std::exception> {
 public:
  ExceptionWatcher(std::string const& expected_message)
      : expected_message_(expected_message) {}

  // noinline + no_sanitize("memory"): e.what() returns a const char* backed by
  // uninstrumented libstdc++ memory, causing MSan false positives when strlen
  // scans it.  Preventing inlining keeps this frame visible so the MSan
  // ignorelist entry can fire; no_sanitize("memory") disables MSan within the
  // function body itself.
  __attribute__((noinline, no_sanitize("memory"))) bool match(
      std::exception const& e) const override {
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
