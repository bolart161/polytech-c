#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace boltunov{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t & rect);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void printInfo() const noexcept override;
    virtual void move(const point_t & newxy) noexcept override;
    virtual void move(double dx, double dy) noexcept override;
    virtual void scale(double factor) override;
    virtual void rotate(double angle) noexcept override;
  private:
    rectangle_t rect_;
    point_t vertices_[4];
  };
}//boltunov
#endif //RECTANGLE_HPP
