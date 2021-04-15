#include <iostream>

#include "simple_calc.hpp"

int main() {
  const int a = 4;
  const int b = 2;

  std::cout << "a+b = " << vva::add(a, b) << '\n';
  std::cout << "a-b = " << vva::subtract(a, b) << '\n';
  std::cout << "a*b = " << vva::multiply(a, b) << '\n';
  std::cout << "a/b = " << vva::divide(a, b) << '\n';

  return 0;
}