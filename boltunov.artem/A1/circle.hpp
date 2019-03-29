#ifndef INC_A1_CIRCLE_HPP
#define INC_A1_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape {
public:
  Circle(const double radius,const point_t & pos);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void printInfo() const override;
  virtual void move(const point_t & newxy) override;
  virtual void move(double dx, double dy) override;
private:
  double radius_;
  point_t pos_;
};

#endif //INC_A1_CIRCLE_HPP
