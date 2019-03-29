#include "rectangle.hpp"
#include <iostream>
#include <cmath>

boltunov::Rectangle::Rectangle(const boltunov::rectangle_t & rect):
  rect_(rect),
  vertices_{{rect.pos.x - rect.width / 2.0, rect.pos.y + rect.height / 2.0}, //leftTop
    {rect.pos.x + rect.width / 2.0, rect.pos.y + rect.height / 2.0}, //rightTop
    {rect.pos.x + rect.width / 2.0, rect.pos.y - rect.height / 2.0}, //rightBottom
    {rect.pos.x - rect.width / 2.0, rect.pos.y - rect.height / 2.0}} //leftBottom
{
  if ((rect_.width < 0.0) || (rect_.height < 0.0)) {
    throw std::invalid_argument("Width and height must be >= 0");
  }
};

double boltunov::Rectangle::getArea() const noexcept
{
  return rect_.width * rect_.height;
};

boltunov::rectangle_t boltunov::Rectangle::getFrameRect() const noexcept
{
  double left = std::min(std::min(vertices_[0].x, vertices_[3].x), std::min(vertices_[1].x, vertices_[2].x));
  double right = std::max(std::max(vertices_[0].x, vertices_[3].x), std::max(vertices_[1].x, vertices_[2].x));
  double down = std::min(std::min(vertices_[0].y, vertices_[3].y), std::min(vertices_[1].y, vertices_[2].y));
  double up = std::max(std::max(vertices_[0].y, vertices_[3].y), std::max(vertices_[1].y, vertices_[2].y));

  return { right - left, up - down, rect_.pos };
}

void boltunov::Rectangle::printInfo() const noexcept
{
  std::cout<<"Center of the rectangle (x = "<<rect_.pos.x<<", y = "<<rect_.pos.y
           <<"), width = "<<rect_.width<<", height = "<<rect_.height<<"\n"
           <<"vertices(leftTop, rightTop, rightBottom, leftBottom): (" << vertices_[0].x << ", " << vertices_[0].y
           << ") (" << vertices_[1].x << ", " << vertices_[1].y << ") (" << vertices_[2].x << ", "
           << vertices_[2].y << ") (" << vertices_[3].x << ", " << vertices_[3].y << ")" << std::endl;
};

void boltunov::Rectangle::move(const boltunov::point_t & newxy) noexcept
{
  move(newxy.x - rect_.pos.x, newxy.y - rect_.pos.y);
};

void boltunov::Rectangle::move(const double horizontalShift,const double verticalShift) noexcept
{
  rect_.pos.x+=horizontalShift;
  rect_.pos.y+=verticalShift;
  for (int i = 0; i < 4; i++) {
    vertices_[i].x += horizontalShift;
    vertices_[i].y += verticalShift;
  }
};

void boltunov::Rectangle::scale(const double factor){
  if (factor < 0.0) {
    throw std::invalid_argument("Factor must be >= 0");
  } else {
    rect_.width *= factor;
    rect_.height *= factor;
  }
}

void boltunov::Rectangle::rotate(const double angle) noexcept
{
  double msin = sin(angle * M_PI / 180.0);
  double mcos = cos(angle * M_PI / 180.0);

  for (int i = 0; i < 4; i++) {
    vertices_[i] = {rect_.pos.x + (vertices_[i].x - rect_.pos.x) * mcos - (vertices_[i].y - rect_.pos.y) * msin,
      rect_.pos.y + (vertices_[i].y - rect_.pos.y) * mcos + (vertices_[i].x - rect_.pos.x) * msin};
  }
}
