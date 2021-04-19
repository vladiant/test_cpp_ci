#include <iostream>

#include "simple_calc.hpp"
#include "basic_warper.hpp"

int main() {
  const int a = 4;
  const int b = 2;

  std::cout << "a+b = " << vva::add(a, b) << '\n';
  std::cout << "a-b = " << vva::subtract(a, b) << '\n';
  std::cout << "a*b = " << vva::multiply(a, b) << '\n';
  std::cout << "a/b = " << vva::divide(a, b) << '\n';

  vva::BasicOperationWarper basic_warper;
  std::cout << "BasicOperationWarper a+b = " << basic_warper.addition(a, b) << '\n';
  std::cout << "BasicOperationWarper a-b = " << basic_warper.subtraction(a, b) << '\n';
  std::cout << "BasicOperationWarper a*b = " << basic_warper.multiplication(a, b) << '\n';
  std::cout << "BasicOperationWarper a/b = " << basic_warper.division(a, b) << '\n';

  return 0;
}
