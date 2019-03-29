#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>

using namespace boltunov;

int main(){
  try{
    Rectangle rect = Rectangle({20, 10, {5,4}});
    Circle circ = Circle{10, point_t {4,2}};

    std::cout << "Before changing scale:" << std::endl;

    rect.printInfo();
    circ.printInfo();

    rect.scale(2);
    circ.scale(5);

    std::cout << std::endl << "After changing scale:" << std::endl;

    rect.printInfo();
    circ.printInfo();
  }catch(std::invalid_argument& invarg){
    std::cerr << invarg.what() << std::endl;
  }
}
