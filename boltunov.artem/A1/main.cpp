#include "rectangle.hpp"
#include "circle.hpp"

int main() {
  point_t posRect = {5,2};
  rectangle_t startRect = {5,12,posRect};
  Rectangle rect = Rectangle(startRect);
  rect.move(point_t {2,4});
  rect.printInfo();

  point_t posCircle = {2,9};
  Circle circle = Circle(5.0,posCircle);
  circle.move(20.2,20.9);
  circle.printInfo();

  return 0;
}
