#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace boltunov
{
  class Matrix
  {
  public:
    Matrix() noexcept;
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix) noexcept;

    std::unique_ptr<std::shared_ptr<Shape>[]> operator[] (size_t index) const;
    Matrix & operator= (const Matrix & rhs);
    Matrix & operator= (Matrix && rhs) noexcept;

    void add(const std::shared_ptr<Shape> &shape);
    void clear() noexcept;
    size_t getLayers() const noexcept;
    size_t getLayerSize() const noexcept;
    void printInfo() const noexcept;

    bool checkIntersection(const std::shared_ptr<Shape> &shapeFirst,
      const std::shared_ptr<Shape> &shapeSecond) const;
  private:
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix_;
    size_t layers_;
    size_t layerSize_;
  };
} // boltunov

#endif // MATRIX_HPP
