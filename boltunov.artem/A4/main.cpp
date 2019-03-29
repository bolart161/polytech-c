#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace boltunov;
using std::cout;
using std::endl;
using std::cerr;

void printMatrix(const Matrix ms)
{
  for (size_t i = 0; i < ms.getLayers(); ++i) {
    std::unique_ptr<std::shared_ptr<Shape>[]> layer = ms[i];
    cout << "Layer - " << i + 1 << ":" << endl;
    for (size_t j = 0; j < ms.getLayerSize(); ++j) {
      if (!layer[j]) {
        break;
      }
      cout << "Element - " << j + 1 << ":" << endl;
      layer[j]->printInfo();
    }
  }
}

int main()
{
  std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle( 3.0, {100.0, 0.0}));
  std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle( 6.0, {0.0, 0.0}));
  std::shared_ptr<Shape> circle3 = std::make_shared<Circle>(Circle( 9.0, {0.0, 0.0}));
  std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle( {1.0, 1.0, {0.0, 0.0}}));
  std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle( {1.0, 1.0, {0.0, 0.0}}));

  Matrix ms;
  ms.add(circle1);
  ms.add(circle2);
  ms.add(circle3);
  ms.add(rect1);
  ms.add(rect2);
  std::cout << "-----------Casual matrix-----------" << std::endl;
  printMatrix(ms);

  CompositeShape cs;

  cs.addShape(circle1);
  cs.addShape(circle2);
  cs.addShape(circle3);
  cs.addShape(rect1);
  cs.addShape(rect2);

  ms = cs.split();
  std::cout << "\n" << "-----Matrix from CompositeShape----" << std::endl;
  printMatrix(ms);

  std::cout << "-----------Rotate-----------" << std::endl;
  rect1->rotate(90);
  rect1->printInfo();
  cs.rotate(90);
  cs[3]->printInfo(); //rect1 in CompositeShape

}
