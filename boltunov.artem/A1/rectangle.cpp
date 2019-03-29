#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if ((rect_.width < 0) || (rect_.height < 0)) {
    throw std::invalid_argument("Width and height must be >= 0");
  }
};

double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
};

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
};

void Rectangle::printInfo() const
{
  std::cout<<"Center of the rectangle (x = "<<rect_.pos.x<<", y = "<<rect_.pos.y
           <<"), width = "<<rect_.width<<", height = "<<rect_.height<<"\n";
};

void Rectangle::move(const point_t & newxy)
{
  rect_.pos=newxy;
};

void Rectangle::move(const double horizontalShift,const double verticalShift)
{
  rect_.pos.x+=horizontalShift;
  rect_.pos.y+=verticalShift;
};
