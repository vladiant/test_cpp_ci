# test_cpp_ci

[![Clang Sanitizers](https://github.com/vladiant/test_cpp_ci/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/vladiant/test_cpp_ci/actions/workflows/sanitizers.yml)
[![Valgrind](https://github.com/vladiant/test_cpp_ci/actions/workflows/valgrind.yml/badge.svg)](https://github.com/vladiant/test_cpp_ci/actions/workflows/valgrind.yml)
[![CppCheck](https://github.com/vladiant/test_cpp_ci/actions/workflows/static_check.yml/badge.svg)](https://github.com/vladiant/test_cpp_ci/actions/workflows/static_check.yml)
[![Clang Tidy](https://github.com/vladiant/test_cpp_ci/actions/workflows/static_check.yml/badge.svg)](https://github.com/vladiant/test_cpp_ci/actions/workflows/static_check.yml)
[![Coverage 70%](https://img.shields.io/badge/coverage-70%25-brightgreen)](https://github.com/vladiant/test_cpp_ci/actions/workflows/coverage.yml)

Test C++ CI project

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

## Test frameworks

### Catch2
* https://github.com/catchorg/Catch2
* commit 182c910b4b63ff587a3440e08f84f70497e49a81
* v2.13.10

### FakeIt
* https://github.com/eranpeer/FakeIt
* commit 1576b26efca0a91361ff1974062c6da25ca944f6
* 2.0.7
