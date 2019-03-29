#define BOOST_TEST_MODULE Test

#include "circle.hpp"
#include "rectangle.hpp"
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#define EPSILON 1E-5

using namespace boltunov;

BOOST_AUTO_TEST_SUITE(TestRect)
  BOOST_AUTO_TEST_CASE(MoveToPoint){
    Rectangle rect = Rectangle({3,4,{5,5}});

    double areaBeforeMove = rect.getArea();
    double widthBeforeMove = rect.getFrameRect().width;
    double heightBeforeMove = rect.getFrameRect().height;

    rect.move({2,4});

    BOOST_CHECK_EQUAL(areaBeforeMove, rect.getArea());
    BOOST_CHECK_EQUAL(widthBeforeMove, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBeforeMove, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove){
    Rectangle rect = Rectangle({3,4,{5,5}});

    double areaBeforeMove = rect.getArea();
    double widthBeforeMove = rect.getFrameRect().width;
    double heightBeforeMove = rect.getFrameRect().height;

    rect.move(23,-14);

    BOOST_CHECK_EQUAL(areaBeforeMove, rect.getArea());
    BOOST_CHECK_EQUAL(widthBeforeMove, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBeforeMove, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Rectangle rect = Rectangle({2,5,{2,5}});
    double areaBeforeScaling = rect.getArea();

    const double factor = 4.3;

    rect.scale(factor);
    BOOST_CHECK_CLOSE(factor * factor, rect.getArea() / areaBeforeScaling, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidParametersForConstructor)
  {
    BOOST_CHECK_THROW(Rectangle({-43.0, -11.0, {2,4}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameterForScale)
  {
    Rectangle rect = Rectangle({5,3,{12.0, 32.0}});
    BOOST_CHECK_THROW(rect.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCirc)
  BOOST_AUTO_TEST_CASE(MoveToPoint){
    Circle circ = Circle(23,{3,9});

    double areaBeforeMove = circ.getArea();
    double widthBeforeMove = circ.getFrameRect().width;
    double heightBeforeMove = circ.getFrameRect().height;

    circ.move({2,4});

    BOOST_CHECK_EQUAL(areaBeforeMove, circ.getArea());
    BOOST_CHECK_EQUAL(widthBeforeMove, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBeforeMove, circ.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove){
    Circle circ = Circle(23,{3,9});

    double areaBeforeMove = circ.getArea();
    double widthBeforeMove = circ.getFrameRect().width;
    double heightBeforeMove = circ.getFrameRect().height;

    circ.move(23,-14);

    BOOST_CHECK_EQUAL(areaBeforeMove, circ.getArea());
    BOOST_CHECK_EQUAL(widthBeforeMove, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBeforeMove, circ.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Circle circ = Circle(25,{2,5});
    double areaBeforeScaling = circ.getArea();

    const double factor = 12.3;

    circ.scale(factor);
    BOOST_CHECK_CLOSE(factor * factor, circ.getArea() / areaBeforeScaling, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidParametersForConstructor)
  {
    BOOST_CHECK_THROW(Circle(-43.0,{1,23}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameterForScale)
  {
    Circle circ = Circle(3,{12.0, 32.0});
    BOOST_CHECK_THROW(circ.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
