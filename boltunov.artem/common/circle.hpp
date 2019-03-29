#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace boltunov{
  class Circle : public Shape {
  public:
    Circle(const double radius,const point_t & pos);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void printInfo() const noexcept override;
    virtual void move(const point_t & newxy) noexcept override;
    virtual void move(double dx, double dy) noexcept override;
    virtual void scale(double factor) override;
    virtual void rotate(double angle) noexcept override;
  private:
    double radius_;
    point_t pos_;
  };
}//boltunov
#endif //CIRCLE_HPP
