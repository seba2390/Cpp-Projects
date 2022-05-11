# include <iostream>
class Fruit  // The class
{            
    public:                  // Access specifier for class 
    std::string fruitType;   // Attribute (string variable)

    // Member Functions()
    void printname()
    {
        std::cout << "The fruit type is: " << fruitType;
    }
};

int main() {
  Fruit myFruit;  // Create an instance of MyClass

  // Access attributes and set values
  myFruit.fruitType = "Banana";

  // Print attribute values
  myFruit.printname();
  return 0;
}