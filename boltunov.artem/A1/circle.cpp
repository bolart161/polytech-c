#include "circle.hpp"
#include <iostream>
#include <math.h>

Circle::Circle(const double radius, const point_t & pos):
  radius_(radius),
  pos_(pos)
{
  if (radius < 0) {
    throw std::invalid_argument("Radius must be >= 0");
  }
};

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
};

rectangle_t Circle::getFrameRect() const
{
  return {2*radius_,2*radius_,pos_};
};

void Circle::printInfo() const
{
  std::cout << "Center of the circle (x = " << pos_.x << ", y = " << pos_.y 
            << "), radius = " << radius_ <<"\n";
};

void Circle::move(const point_t & newxy)
{
  pos_=newxy;
};

void Circle::move(const double horizontalShift,const double verticalShift)
{
  pos_.x+=horizontalShift;
  pos_.y+=verticalShift;
};
