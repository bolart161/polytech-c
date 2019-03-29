#include "figures.hpp"

Circle::Circle(const Point & center):
  Shape(center)
{}

void Circle::draw(std::ostream & out)
{
  out << "CIRCLE (" << center_.x << ";" << center_.y << ")\n";
}

Triangle::Triangle(const Point & center):
  Shape(center)
{}

void Triangle::draw(std::ostream & out)
{
  out << "TRIANGLE (" << center_.x << ";" << center_.y << ")\n";
}

Square::Square(const Point & center):
  Shape(center)
{}

void Square::draw(std::ostream & out)
{
  out << "SQUARE (" << center_.x << ";" << center_.y << ")\n";
}
