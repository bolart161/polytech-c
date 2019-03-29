#include "shape.hpp"

Shape::Shape(const Point & center):
  center_(center)
{}

bool Shape::isMoreLeft(Shape *shape) const
{
  return (center_.x < shape->center_.x);
}

bool Shape::isUpper(Shape *shape) const
{
  return (center_.y > shape->center_.y);
}
