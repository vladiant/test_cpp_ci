# test_cpp_ci

[![Clang Sanitizers](https://github.com/vladiant/test_cpp_ci/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/vladiant/test_cpp_ci/actions/workflows/sanitizers.yml)
[![Valgrind](https://github.com/vladiant/test_cpp_ci/actions/workflows/valgrind.yml/badge.svg)](https://github.com/vladiant/test_cpp_ci/actions/workflows/valgrind.yml)
[![CppCheck](https://github.com/vladiant/test_cpp_ci/actions/workflows/static_check.yml/badge.svg)](https://github.com/vladiant/test_cpp_ci/actions/workflows/static_check.yml)
[![Clang Tidy](https://github.com/vladiant/test_cpp_ci/actions/workflows/static_check.yml/badge.svg)](https://github.com/vladiant/test_cpp_ci/actions/workflows/static_check.yml)
[![Coverage 70%](https://img.shields.io/badge/coverage-70%25-brightgreen)](https://github.com/vladiant/test_cpp_ci/actions/workflows/coverage.yml)

Test C++ CI project

## C++ standard modernization

This project now targets C++20 as its baseline language standard, with C++23 available on toolchains that support it. The move from C++17 is intentional:

- C++20 brings concepts, ranges, coroutines, and improved standard library support that reduce boilerplate and make modern C++ code clearer and safer.
- The language and library features added in C++20 are now widely available in current GCC, Clang, and MSVC toolchains, so the project can stay modern without sacrificing portability.
- C++23 continues the evolution of the standard and is useful for newer compilers, but C++20 is the safer default for CI because it remains broadly supported across Linux, macOS, and Windows.
- Keeping the project at C++20 also avoids unnecessary churn from compiler-specific workarounds while still enabling a future upgrade to C++23 when the toolchain baseline is updated.

To build with C++23 on a compatible compiler, pass `-DCMAKE_CXX_STANDARD=23` during configuration.

## Quick start

Use the bundled CMake preset for the standard CI flow:

```bash
cmake --preset ci
cmake --build --preset ci
ctest --preset ci
```

This keeps the local and CI configuration aligned with a single, reproducible build entry point.

## Use this template

To create a new project based on this repository:

1. Open the repository on GitHub.
2. Click the green "Use this template" button in the upper-right corner.
3. Choose a repository name and visibility for your new project.
4. Create the repository, clone it locally, and start extending the C++ CI setup.

## Tool coverage comparison

| Tool | Main categories / focus | Typical issues it catches |
| --- | --- | --- |
| clang-tidy | Static analysis: correctness, bugprone, performance, readability, portability, concurrency, modernize, cppcoreguidelines, cert, clang-analyzer | Suspect logic, unsafe casts, unused values, copy/move issues, dead code, questionable API usage, resource lifetime mistakes |
| Sanitizers (ASan/UBSan/TSan/MSan/LSan) | Runtime instrumentation: memory safety, UB, thread safety, leak detection | Out-of-bounds access, use-after-free, stack/global buffer overflows, signed overflow, misaligned access, data races, memory leaks |
| CppCheck | Static analysis for C/C++ code quality and safety | Null dereferences, uninitialized variables, redundant conditions, invalid pointer use, out-of-range indexing, possible memory leaks |
| Valgrind | Runtime memory and thread debugging | Memory leaks, invalid reads/writes, uninitialized memory use, bad frees, race conditions (with tool variants such as DRD/Helgrind) |

In short: clang-tidy is best for code-quality and static-analysis warnings, sanitizers catch runtime failures during execution, CppCheck adds another static-analysis layer, and Valgrind is especially valuable for detecting memory errors and leak patterns that only show up at runtime.

## Bugs this would have caught

These intentionally broken PRs are the kinds of mistakes the CI is designed to catch before a branch is merged. Each one is realistic, small, and easy to miss in a normal local build.

### 1. Use-after-free: "Simplify shutdown path"

```cpp
std::string* buffer = new std::string("payload");
delete buffer;
std::cout << buffer->size() << '\n';
```

A normal debug build can appear to work; ASan fails immediately because the pointer is dereferenced after free.

### 2. Data race: "Parallelize histogram build"

```cpp
int hits = 0;
std::thread t1([&]() { for (int i = 0; i < 1'000'000; ++i) ++hits; });
std::thread t2([&]() { for (int i = 0; i < 1'000'000; ++i) ++hits; });
t1.join();
t2.join();
```

This is not safe without a lock or atomic. ThreadSanitizer catches the race during the test run and points at the unsynchronized access.

### 3. Leak: "Cache parser state"

```cpp
struct ParserState {
    explicit ParserState(std::string s) : path(std::move(s)) {}
    std::string path;
};

void parse_file(const std::string& path) {
    auto* state = new ParserState(path);
    state->path += ".tmp";
}
```

The code appears correct until a long-running process leaks memory repeatedly. The Valgrind CI job flags the leaked allocation (and LSan can also catch this in sanitizer runs).

### 4. Integer overflow: "Optimize packet length check"

```cpp
int len = std::numeric_limits<int>::max();
len += 1; // signed overflow UB
```

This is a classic overflow bug. With UBSan enabled, the CI catches the invalid arithmetic at runtime.

### 5. Undefined behavior: "Inline fast path"

```cpp
int x = 1;
int y = 32;
int value = x << y; // shift count too large for 32-bit int
```

This is undefined behavior in C++. UBSan reports the invalid shift during test execution.

These examples are intentionally bad, but they reflect the same class of issues that the repository's sanitizer, static-analysis, and valgrind jobs are specifically meant to catch.

## Test frameworks

### Catch2
* https://github.com/catchorg/Catch2
* commit 182c910b4b63ff587a3440e08f84f70497e49a81
* v2.13.10

### FakeIt
* https://github.com/eranpeer/FakeIt
* commit 1576b26efca0a91361ff1974062c6da25ca944f6
* 2.0.7
