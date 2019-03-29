#ifndef FIGURES_HPP
#define FIGURES_HPP

#include <iostream>
#include "shape.hpp"

class Circle: public Shape{
public:
  explicit Circle(const Point &center);
  void draw(std::ostream &out) override;
};

class Triangle: public Shape{
public:
  explicit Triangle(const Point &center);
  void draw(std::ostream &out) override;
};

class Square: public Shape{
public:
  explicit Square(const Point &center);
  void draw(std::ostream &out) override;
};

#endif //FIGURES_HPP
