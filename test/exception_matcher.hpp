#pragma once
#include <catch2/catch.hpp>
#include <string>

// MSan's malloc interceptor marks heap memory as "uninitialized" even when
// allocated by uninstrumented libstdc++.  When libstdc++ writes the exception
// message into that buffer (without MSan instrumentation), the shadow stays
// "dirty".  The runtime strlen interceptor then fires on e.what().
// __msan_unpoison_string uses an internal strlen that bypasses the interceptor,
// gets the length, and marks the bytes as initialized before operator== runs.
#if defined(__has_feature)
#  if __has_feature(memory_sanitizer)
#    include <sanitizer/msan_interface.h>
#  endif
#endif

namespace Catch {
namespace Matchers {
class ExceptionWatcher : public MatcherBase<std::exception> {
 public:
  ExceptionWatcher(std::string const& expected_message)
      : expected_message_(expected_message) {}

  bool match(std::exception const& e) const override {
    const char* what_msg = e.what();
#if defined(__has_feature)
#  if __has_feature(memory_sanitizer)
    __msan_unpoison_string(what_msg);
#  endif
#endif
    return what_msg == expected_message_;
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
