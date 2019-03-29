#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iosfwd>

struct Point{
  int x;
  int y;
};

class Shape{
public:
  explicit Shape(const Point &center);
  virtual ~Shape() = default;

  bool isMoreLeft(Shape *shape) const;
  bool isUpper(Shape *shape) const;

  virtual void draw(std::ostream &out) = 0;

protected:
  Point center_;
};

#endif //SHAPE_HPP
