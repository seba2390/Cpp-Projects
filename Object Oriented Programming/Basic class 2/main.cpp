// example: class constructor
#include <iostream>

class Rectangle 
{
  int width, height;        // private attributes (before public)
  public:
    Rectangle(int a, int b) // constructor
    {
        width  = a;
        height = b;
    }  
    
  int area()                // class method
  {
    return (width * height);
  } 

};


int main () {
  Rectangle rect (3,4);
  Rectangle rectb (5,6);
  std::cout << "rect area: " << rect.area() << std::endl;
  std::cout << "rectb area: " << rectb.area() << std::endl;
  return 0;
}