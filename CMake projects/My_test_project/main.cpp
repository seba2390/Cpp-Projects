#include <iostream>
#include "my_lib/myfunctions.h"

int main() {
    double x1 = 2;
    double x2 = 3;
	std::cout<<"Hello CMake!"<<std::endl;
    std::cout<<"Sum of 2 and 3 is :"<<std::endl;
    std::cout<< sum(x1,x2) <<std::endl;
    std::cout<<"Product of 2 and 3 is :"<<std::endl;
    std::cout<< product(x1,x2) <<std::endl;
}