#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace boltunov{
  class Shape {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const point_t&) noexcept = 0;
    virtual void move(const double,const double) noexcept = 0;
    virtual void scale(double factor) = 0;
    virtual void printInfo() const noexcept = 0;
    virtual void rotate(double angle) noexcept = 0;
  };
}//boltunov
#endif //SHAPE_HPP
