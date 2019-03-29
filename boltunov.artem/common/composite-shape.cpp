#include "composite-shape.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

boltunov::CompositeShape::CompositeShape() noexcept:
  countShapes_(0),
  shapes_(nullptr)
{}

boltunov::CompositeShape::CompositeShape(const std::shared_ptr<boltunov::Shape> &shape):
  countShapes_(0),
  shapes_(nullptr)
{
  if (!shape) {
    throw std::invalid_argument("Error. Invalid pointer shape");
  }
  addShape(shape);
}

boltunov::CompositeShape::CompositeShape(const boltunov::CompositeShape& object):
  countShapes_(object.getCount())
{
  std::unique_ptr<std::shared_ptr <Shape>[]> copyObject (new std::shared_ptr<boltunov::Shape>[object.getCount()]);
  for (size_t i = 0; i < object.getCount(); i++) {
    copyObject[i] = object.shapes_[i];
  }
  shapes_.swap(copyObject);
}

boltunov::CompositeShape::CompositeShape(boltunov::CompositeShape&& object) noexcept:
  countShapes_(object.getCount())
{
  shapes_.swap(object.shapes_);
}

boltunov::CompositeShape & boltunov::CompositeShape::operator=(const boltunov::CompositeShape& otherObj)
{
  if (this != &otherObj)
  {
    countShapes_ = otherObj.getCount();
    std::unique_ptr<std::shared_ptr<Shape>[]> copyObject (new std::shared_ptr<Shape>[otherObj.getCount()]);
    for (size_t i = 0; i < otherObj.getCount(); i++) {
      copyObject[i] = otherObj.shapes_[i];
    }
    shapes_.swap(copyObject);
  }
  return *this;
}

boltunov::CompositeShape & boltunov::CompositeShape::operator=(boltunov::CompositeShape&& otherObj) noexcept
{
  if (this != & otherObj)
  {
    countShapes_ = otherObj.countShapes_;
    shapes_.swap(otherObj.shapes_);
    otherObj.shapes_ = nullptr;
    otherObj.countShapes_ = 0;
  }
  return *this;
}

std::shared_ptr<boltunov::Shape> boltunov::CompositeShape::operator[](const unsigned int index) const
{
  if (index >= countShapes_ || index <= 0){
    throw std::out_of_range("Index is out of range");
  }
  return shapes_[index];
}

void boltunov::CompositeShape::addShape(const std::shared_ptr<boltunov::Shape>& shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Incorrect pointer");
  }
  if (shape.get() == this)
  {
    throw std::invalid_argument("This is the same shape (Addresses are the same)");
  }

  std::unique_ptr <std::shared_ptr<Shape>[]> tempArray (new std::shared_ptr<Shape>[countShapes_ + 1]);

  for (size_t i = 0; i < countShapes_; i++)
  {
    tempArray[i] = shapes_[i];
  }

  tempArray[countShapes_] = shape;
  shapes_.swap(tempArray);
  countShapes_++;
}

void boltunov::CompositeShape::rmShape(const unsigned int index)
{
  if (index >= countShapes_)
  {
    throw std::out_of_range("Index is out of range");
  }
  if (countShapes_ <= 0)
  {
    throw std::invalid_argument("Composite figure consists of 0 figures");
  }

  if (countShapes_ == 1)
  {
    clear();
    return;
  } else {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp (new std::shared_ptr<Shape>[countShapes_-1]);
    for (size_t i = 0; i < index; i++)
    {
      temp[i] = shapes_[i];
    }
    for (size_t i = index; i < countShapes_ - 1; i++)
    {
      temp[i] = shapes_[i + 1];
    }
    shapes_.swap(temp);
    countShapes_--;
  }
}

size_t boltunov::CompositeShape::getCount() const noexcept
{
  return countShapes_;
}

void boltunov::CompositeShape::move(const boltunov::point_t& newxy) noexcept
{
  const point_t pos = getFrameRect().pos;
  move(newxy.x - pos.x, newxy.y - pos.y);
}

void boltunov::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (size_t i = 0; i < countShapes_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void boltunov::CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < countShapes_; i++)
  {
    shapes_[i]->move({pos.x + (shapes_[i]->getFrameRect().pos.x - pos.x) * factor,
      pos.y + (shapes_[i]->getFrameRect().pos.y - pos.y) * factor});
    shapes_[i]->scale(factor);
  }
}

void boltunov::CompositeShape::rotate(const double angle) noexcept
{
  double mcos = cos(angle * M_PI / 180.0);
  double msin = sin(angle * M_PI / 180.0);

  point_t center = getFrameRect().pos;
  for (size_t i = 0; i < 4; i++) {
    point_t shapePos = shapes_[i]->getFrameRect().pos;
    double newX = center.x + (shapePos.x - center.x) * mcos - (shapePos.y - center.y) * msin;
    double newY = center.y + (shapePos.y - center.y) * mcos + (shapePos.x - center.x) * msin;

    shapes_[i]->move({newX, newY});
    shapes_[i]->rotate(angle);
  }
}

double boltunov::CompositeShape::getArea() const noexcept
{
  double area = 0.0;
  for (size_t i = 0; i < countShapes_; i++)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}

void boltunov::CompositeShape::printInfo() const noexcept
{
  std::cout << "area of composite shape = " << getArea() << std::endl
            << "width FrameRect = " << getFrameRect().width << std::endl
            << "height FrameRect = " << getFrameRect().height << std::endl
            << "x CompositeShape = " <<  getFrameRect().pos.x << std::endl
            << "y CompositeShape = " << getFrameRect().pos.y << std::endl
            << "count shapes = " << countShapes_ << std::endl << std::endl;
}

boltunov::rectangle_t boltunov::CompositeShape::getFrameRect() const noexcept
{
  if (countShapes_ <= 0)
  {
    return  {NAN, NAN, {NAN, NAN}};
  }
  else
  {
    rectangle_t rectangle = shapes_[0]->getFrameRect();

    double maxX = rectangle.pos.x + rectangle.width / 2;
    double maxY = rectangle.pos.y + rectangle.height / 2;
    double minX = rectangle.pos.x - rectangle.width / 2;
    double minY = rectangle.pos.y - rectangle.height / 2;


    for (size_t i = 1; i <countShapes_; i++)
    {
      rectangle = shapes_[i]->getFrameRect();
      point_t pos = shapes_[i]->getFrameRect().pos;

      double nowMaxX = pos.x + rectangle.width / 2;
      double nowMinX = pos.x - rectangle.width / 2;
      double nowMaxY = pos.y + rectangle.height / 2;
      double nowMinY = pos.y - rectangle.height / 2;

      if (nowMinX < minX) {
        minX = nowMinX;
      }

      if (nowMaxX > maxX) {
        maxX = nowMaxX;
      }

      if (nowMinY < minY) {
        minY = nowMinY;
      }

      if (nowMaxY > maxY) {
        maxY = nowMaxY;
      }
    }
    return {(maxX - minX), (maxY - minY), {((maxX + minX) / 2), ((maxY + minY) / 2)}};
  }
}

void boltunov::CompositeShape::clear() noexcept
{
  shapes_.reset();
  shapes_ = nullptr;
  countShapes_ = 0;
}

boltunov::Matrix boltunov::CompositeShape::split() const
{
  Matrix matrix;
  for (size_t i = 0; i < countShapes_; i++) {
    matrix.add(shapes_[i]);
  }
  return matrix;
}
