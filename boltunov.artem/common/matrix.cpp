#include "matrix.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <memory>

boltunov::Matrix::Matrix() noexcept:
  matrix_(),
  layers_(0),
  layerSize_(0)
{}

boltunov::Matrix::Matrix(const boltunov::Matrix & matrix):
  matrix_(new std::shared_ptr<Shape>[matrix.layers_ * matrix.layerSize_]),
  layers_(matrix.layers_),
  layerSize_(matrix.layerSize_)
{
  for (unsigned int i = 0; i < layers_ * layerSize_; i++) {
    matrix_[i] = matrix.matrix_[i];
  }
}

boltunov::Matrix::Matrix(boltunov::Matrix && matrix) noexcept:
  matrix_(nullptr),
  layers_(matrix.layers_),
  layerSize_(matrix.layerSize_)
{
  matrix_.swap(matrix.matrix_);
  matrix.layers_ = 0;
  matrix.layerSize_ = 0;
}

std::unique_ptr<std::shared_ptr<boltunov::Shape>[]> boltunov::Matrix::operator[] (size_t index) const
{
  if (index >= layers_) {
    throw std::out_of_range("Index out of range");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> layer(new std::shared_ptr<Shape>[layerSize_]);
  std::copy(matrix_.get() + index * layerSize_, matrix_.get() + (index + 1) * layerSize_, layer.get());
  return layer;
}


boltunov::Matrix & boltunov::Matrix::operator=(const boltunov::Matrix & matrix)
{
  if (this != & matrix) {
    layerSize_ = matrix.getLayerSize();
    layers_ = matrix.getLayers();
    std::unique_ptr<std::shared_ptr<Shape>[]> copyObj(new std::shared_ptr<Shape>[matrix.getLayers()]);
    for(size_t i = 0; i < matrix.getLayers(); i++) {
      copyObj[i] = matrix.matrix_[i];
    }
    matrix_.swap(copyObj);
  }
  return *this;
}

boltunov::Matrix & boltunov::Matrix::operator=(boltunov::Matrix && matrix) noexcept
{
  if (this != & matrix) {
    layers_ = matrix.layers_;
    layerSize_ = matrix.layerSize_;
    matrix_.swap(matrix.matrix_);
    matrix.matrix_ = nullptr;
    matrix.layers_ = 0;
    matrix.layerSize_ = 0;
  }
  return *this;
}

void boltunov::Matrix::add(const std::shared_ptr<boltunov::Shape> & shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("Invalid pointer to shape");
  }

  if ((layers_ == 0) && (layerSize_ == 0)) {
    std::unique_ptr<std::shared_ptr<Shape>[]> copyMatrix (new std::shared_ptr<Shape>[1]);
    matrix_.swap(copyMatrix);
    layers_ = layerSize_ = 1;
    matrix_[0] = shape;
    return;
  }


  size_t i = 0;
  for (; i < layers_; ++i) {
    size_t j = 0;
    for(; j < layerSize_; ++j) {
      if (!matrix_[i * layerSize_ + j]) {
        matrix_[i * layerSize_ + j] = shape;
        return;
      }
      if (checkIntersection(matrix_[i * layerSize_ + j], shape)) {
        break;
      }
    }
    if (j == layerSize_) {
      std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix(new std::shared_ptr<Shape>[layers_ * (layerSize_ + 1)]);
      for (size_t k = 0; k < layers_; ++k) {
        for (j = 0; j < layerSize_; ++j) {
          newMatrix[k * layerSize_ + j + k] = matrix_[k * layerSize_ + j];
        }
      }
      ++layerSize_;
      newMatrix[(i + 1) * layerSize_ - 1] = shape;
      matrix_ = std::move(newMatrix);
      return;
    }
  }
  if (i == layers_) {
    std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix(new std::shared_ptr<Shape>[(layers_ + 1) * layerSize_]);
    for (size_t k = 0; k < layers_ * layerSize_; ++k) {
      newMatrix[k] = matrix_[k];
    }
    newMatrix[layers_ * layerSize_] = shape;
    ++layers_;
    matrix_ = std::move(newMatrix);
  }

}

void boltunov::Matrix::clear() noexcept
{
  matrix_.reset();
  layers_ = 0;
  layerSize_ = 0;
}

size_t boltunov::Matrix::getLayers() const noexcept
{
  return layers_;
}

size_t boltunov::Matrix::getLayerSize() const noexcept
{
  return layerSize_;
}

bool boltunov::Matrix::checkIntersection(const std::shared_ptr<Shape> &shapeFirst,
  const std::shared_ptr<Shape> &shapeSecond) const
{
  rectangle_t getFrameFirst = shapeFirst->getFrameRect();
  rectangle_t getFrameSecond = shapeSecond->getFrameRect();

  double firstRectLeft = getFrameFirst.pos.x - getFrameFirst.width / 2.0;
  double firstRectRight = getFrameFirst.pos.x + getFrameFirst.width / 2.0;
  double firstRectTop = getFrameFirst.pos.y + getFrameFirst.height / 2.0;
  double firstRectBottom = getFrameFirst.pos.y - getFrameFirst.height / 2.0;

  double secondRectLeft = getFrameSecond.pos.x - getFrameSecond.width / 2.0;
  double secondRectRight = getFrameSecond.pos.x + getFrameSecond.width / 2.0;
  double secondRectTop = getFrameSecond.pos.y + getFrameSecond.height / 2.0;
  double secondRectBottom = getFrameSecond.pos.y - getFrameSecond.height / 2.0;

  if ((firstRectLeft > secondRectRight) || (firstRectRight < secondRectLeft)
    || (firstRectTop < secondRectBottom) || (firstRectBottom > secondRectTop)) {
    return false;
  } else {
    return true;
  }
}
