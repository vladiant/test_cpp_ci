#pragma once
#include <catch2/catch.hpp>
#include <string>

// __msan_unpoison_string is used below to suppress false positives when
// reading the char* returned by std::exception::what(), whose backing memory
// is allocated by uninstrumented libstdc++ and therefore has no MSan shadow.
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

  // e.what() returns a const char* backed by uninstrumented libstdc++ memory.
  // MSan has no shadow bits for it and flags any read (e.g. strlen inside
  // operator==) as use-of-uninitialized-value.  __msan_unpoison_string marks
  // the string as initialised before comparing, making the check correct.
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
