#ifndef INC_A1_RECTANGLE_HPP
#define INC_A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t & rect);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void printInfo() const override;
  virtual void move(const point_t & newxy) override;
  virtual void move(double dx, double dy) override;
private:
  rectangle_t rect_;
};

#endif //INC_A1_RECTANGLE_HPP
