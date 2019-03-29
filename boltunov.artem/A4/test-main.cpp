#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

using namespace boltunov;

const double EPS = 0.000001;

BOOST_AUTO_TEST_SUITE(RectangleTest)
  BOOST_AUTO_TEST_CASE(RotateTest)
  {
    Rectangle rec({11.1, 14.6, {12, 22}});
    for (size_t i = -180; i < 180; i++)
    {
      Rectangle rec2(rec);
      rec2.rotate(i);
      BOOST_CHECK_EQUAL(rec.getFrameRect().pos.x, rec2.getFrameRect().pos.x);
      BOOST_CHECK_EQUAL(rec.getFrameRect().pos.y, rec2.getFrameRect().pos.y);
      BOOST_CHECK_EQUAL(rec.getArea(), rec2.getArea());
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)
  BOOST_AUTO_TEST_CASE(Turn_Test)
  {
    Circle circ(23.1, {22, 12});
    for (size_t i = -180; i < 180; i++)
    {
      Circle circ1(circ);
      circ1.rotate(i);
      BOOST_CHECK_EQUAL(circ.getFrameRect().pos.x, circ1.getFrameRect().pos.x);
      BOOST_CHECK_EQUAL(circ.getFrameRect().pos.y, circ1.getFrameRect().pos.y);
      BOOST_CHECK_EQUAL(circ.getArea(), circ1.getArea());
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)
  BOOST_AUTO_TEST_CASE(RotateTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {1.0, 1.0}}));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(1.0, {0.0, 0.0}));

    CompositeShape cs;
    cs.addShape(rect);
    cs.addShape(circ);

    for (size_t i = -180; i < 180; i++)
    {
      std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({2.0, 3.0, {12.3, 123.2}}));
      std::shared_ptr<Shape> circ2 = std::make_shared<Circle>(Circle( 11.0, {0.0, 2.0}));

      CompositeShape cs2;
      cs2.addShape(rect2);
      cs2.addShape(circ2);

      cs2.rotate(i);

      BOOST_CHECK_EQUAL(cs.getFrameRect().pos.x, cs2.getFrameRect().pos.x);
      BOOST_CHECK_EQUAL(cs.getFrameRect().pos.y, cs2.getFrameRect().pos.y);
      BOOST_CHECK_EQUAL(cs.getArea(), cs2.getArea());
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_Tests)

  BOOST_AUTO_TEST_CASE(New_Layer)
  {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle( 13.0, {10.0, 0.0}));
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle( 3.0, {0.0, 0.0}));
    std::shared_ptr<Shape> circle3 = std::make_shared<Circle>(Circle( 2.0, {-10.0, 0.0}));
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle( {11.0, 12.0, {20.0, -20.0}}));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle( {19.0, 13.0, {10.0, 20.0}}));

    Matrix m;
    m.add(circle1);
    m.add(circle2);
    m.add(circle3);
    m.add(rect1);
    m.add(rect2);

    BOOST_CHECK(m[0][0] == circle1);
    BOOST_CHECK(m[1][0] == circle2);
    BOOST_CHECK(m[0][1] == circle3);
    BOOST_CHECK(m[0][2] == rect1);
    BOOST_CHECK(m[0][3] == rect2);
  }

  BOOST_AUTO_TEST_CASE(TestNewLayer)
  {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(11.0, {0.0, 0.0}));
    std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle(2.0, {0.0, 0.0}));

    Matrix m;
    m.add(circle1);
    m.add(circle2);

    BOOST_CHECK(m[0][0] == circle1);
    BOOST_CHECK(m[1][0] == circle2);

  }

  BOOST_AUTO_TEST_CASE(InvalidAddShape)
  {
    Matrix m;
    BOOST_CHECK_THROW(m.add(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(AddOneShape)
  {
    std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(12.0, {0.0, 0.0}));
    Matrix m;
    m.add(circle1);
    BOOST_CHECK(m[0][0] == circle1);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({12.1, 12.2, {1.3, 2.3}}));
    Matrix m;
    m.add(rect);
    Matrix m2(m);
    BOOST_CHECK(m[0][0]== m2[0][0]);
  }

  BOOST_AUTO_TEST_CASE(CopyOperatorTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({2.0, 4.0, {12.1,122}}));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({2.0, 1.0, {1.1,2}}));
    Matrix m;
    m.add(rect);
    Matrix m2;
    m2.add(rect2);
    m2 = m;
    BOOST_CHECK(m[0][0] == m2[0][0]);
  }

  BOOST_AUTO_TEST_CASE(CheckIntersectTest)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({11.0, 1.0, {0.0, 0.0}}));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({10.0, 1.0, {1.0, 13.0}}));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({10.0, 1.0, {1.0, 0.0}}));

    Matrix m;

    BOOST_CHECK(!m.checkIntersection(rect1 , rect2));
    BOOST_CHECK(m.checkIntersection(rect1 , rect3));
  }

  BOOST_AUTO_TEST_CASE(CheckCompositeShapeSplit)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({11.0, 1.0, {0.0, 0.0}}));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({10.0, 1.0, {1.0, 13.0}}));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({10.0, 1.0, {1.0, 0.0}}));

    CompositeShape cs;
    cs.addShape(rect1);
    cs.addShape(rect2);
    cs.addShape(rect3);

    Matrix m = cs.split();

    BOOST_CHECK_EQUAL(m[0][0], rect1);
    BOOST_CHECK_EQUAL(m[0][1], rect2);
    BOOST_CHECK_EQUAL(m[1][0], rect3);
  }

BOOST_AUTO_TEST_SUITE_END()
