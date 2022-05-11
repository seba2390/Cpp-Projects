#include <iostream>

int main() {

  int first_number, second_number, sum;
    
  std::cout << "Enter two integers: ";
  std::cin >> first_number >> second_number;

  // sum of two numbers in stored in variable sumOfTwoNumbers
  sum = first_number + second_number;

  // prints sum 
  std::cout << first_number << " + " <<  second_number << " = " << sum;     

  return 0;
}