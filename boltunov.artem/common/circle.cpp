#include "circle.hpp"
#include <iostream>
#include <math.h>

boltunov::Circle::Circle(const double radius, const boltunov::point_t & pos):
  radius_(radius),
  pos_(pos)
{
  if (radius < 0.0) {
    throw std::invalid_argument("Radius must be >= 0");
  }
};

double boltunov::Circle::getArea() const noexcept
{
  return M_PI*radius_*radius_;
};

boltunov::rectangle_t boltunov::Circle::getFrameRect() const noexcept
{
  return {2.0 * radius_, 2.0 * radius_, pos_};
};

void boltunov::Circle::printInfo() const noexcept
{
  std::cout << "Center of the circle (x = " << pos_.x << ", y = " << pos_.y
            << "), radius = " << radius_ <<"\n";
};

void boltunov::Circle::move(const boltunov::point_t & newxy)  noexcept
{
  pos_=newxy;
};

void boltunov::Circle::move(const double horizontalShift,const double verticalShift)  noexcept
{
  pos_.x+=horizontalShift;
  pos_.y+=verticalShift;
};

void boltunov::Circle::scale(const double factor)
{
  if (factor < 0.0) {
    throw std::invalid_argument("Factor must be >= 0");
  } else {
    radius_ *= factor;
  }
}

void boltunov::Circle::rotate(double /*angle*/) noexcept
{}
