#ifndef INC_A1_SHAPE_HPP
#define INC_A1_SHAPE_HPP

#include "base-types.hpp"

class Shape {
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t&) = 0;
  virtual void move(const double,const double) = 0;
  virtual void printInfo() const = 0;
};
#endif //INC_A1_SHAPE_HPP
