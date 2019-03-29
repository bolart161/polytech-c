#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace boltunov;

const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    CompositeShape compositeShape = CompositeShape();
    compositeShape.addShape(rect1);
    compositeShape.addShape(circle1);
    double heightBeforeChange = compositeShape.getFrameRect().height;
    double widthBeforeChange = compositeShape.getFrameRect().width;
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.move({3.0, 2.0});
    BOOST_CHECK(compositeShape.getFrameRect().pos.x == 3.0 && compositeShape.getFrameRect().pos.y == 2.0);
    BOOST_CHECK_CLOSE(heightBeforeChange, compositeShape.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, compositeShape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveAxis)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    CompositeShape compositeShape(rectangle1);
    compositeShape.addShape(circle1);
    double heightBeforeChange = compositeShape.getFrameRect().height;
    double widthBeforeChange = compositeShape.getFrameRect().width;
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.move(3.0, 2.0);
    BOOST_CHECK_CLOSE(heightBeforeChange, compositeShape.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, compositeShape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    CompositeShape compositeShape(rectangle1);
    compositeShape.addShape(circle1);
    BOOST_CHECK_THROW(compositeShape.scale(-2.9), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScaleTestCompositeShape)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    CompositeShape compositeShape(rectangle1);
    compositeShape.addShape(circle1);
    double areaBeforeChange = compositeShape.getArea();
    compositeShape.scale(3.0);
    BOOST_CHECK_CLOSE(3.0 * 3.0 * areaBeforeChange, compositeShape.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(CheckAdd)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    CompositeShape compositeShape(rectangle1);
    compositeShape.addShape(circle1);
    BOOST_CHECK_EQUAL(compositeShape.getCount(), 2);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidAdd)
  {
    std::shared_ptr<Shape> rect1 = nullptr;
    CompositeShape compositeShape = CompositeShape();
    BOOST_CHECK_THROW(compositeShape.addShape(rect1), std::invalid_argument); 
  }
  
  BOOST_AUTO_TEST_CASE(CheckAddinEmptyList)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    CompositeShape compositeShape = CompositeShape();
    compositeShape.addShape(circle1);
    compositeShape.addShape(rect1);
    BOOST_CHECK_EQUAL(compositeShape.getCount(), 2);
  }

  BOOST_AUTO_TEST_CASE(CheckRemove)
  {
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));
    CompositeShape compositeShape(rectangle1);
    compositeShape.addShape(circle1);
    compositeShape.rmShape(1);
    BOOST_CHECK_EQUAL(compositeShape.getCount(), 1);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidIndex)
  {
   std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1.0, 4.0, {2.0, 2.0}}));
   CompositeShape compositeShape = CompositeShape();
   compositeShape.addShape(rect1);
   BOOST_CHECK_THROW(compositeShape[2], std::out_of_range);
   compositeShape.clear();
  }


BOOST_AUTO_TEST_SUITE_END()
