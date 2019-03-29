#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace boltunov{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape() noexcept;
    CompositeShape(const std::shared_ptr<Shape>& shape);
    CompositeShape(const CompositeShape& object);
    CompositeShape(CompositeShape&& object) noexcept;

    CompositeShape& operator=(const CompositeShape& otherObj);
    CompositeShape& operator=(CompositeShape&& otherObj) noexcept;
    std::shared_ptr<Shape> operator[](const unsigned int index) const;

    void addShape(const std::shared_ptr<Shape>& shape);
    void rmShape(const unsigned int index);
    size_t getCount() const noexcept;
    void printInfo() const noexcept override;
    void move(const point_t& newxy) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double factor) override;
    virtual void rotate(double angle) noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void clear() noexcept;
    Matrix split() const;

  private:
    size_t countShapes_;
    std::unique_ptr <std::shared_ptr<Shape>[]> shapes_;
  };
}

#endif
