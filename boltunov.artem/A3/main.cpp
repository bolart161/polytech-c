#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace boltunov;

int main()
{
  std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 3.0, {-4.0, -4.0}}));
  std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({2.0, 2.0, {-1.0, -1.0}}));
  std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({3.0, 3.0, {1.0, 1.0}}));

  CompositeShape compositeShape = CompositeShape();
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);

  compositeShape.printInfo();

  compositeShape.scale(6);

  std::cout << "scale with coefficient = 6.0" << std::endl;

  compositeShape.printInfo();

  compositeShape.move({1, 1});
  compositeShape.move(9, 6);

  std::cout << "move to x = 1.0, y = 1.0 \t" << "move on x = 9.0, y = 6.0" << std::endl;
  compositeShape.printInfo();

  compositeShape.rmShape(1);
  compositeShape.rmShape(0);

  std::cout << "0 and 1st figures has been removed " << std::endl;
  compositeShape.printInfo();


  CompositeShape compositeShape2(rect2);
  compositeShape2.addShape(rect1);
  compositeShape2.printInfo();

  return 0;
}
