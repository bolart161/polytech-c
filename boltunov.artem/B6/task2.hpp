#ifndef TASK2_HPP
#define TASK2_HPP

#include <vector>
#include <sstream>
#include <numeric>
#include <iterator>
#include "line.hpp"

struct Point
{
  int x, y;
};

using Shape = std::vector<Point>;

void task2();

Shape readShapeData(const Line &line);

int countVertices(const std::vector<Shape> & vector);
size_t countTriangles(const std::vector<Shape> & vector);
size_t countSquares(const std::vector<Shape> & vector);
size_t countRectangles(const std::vector<Shape> & vector);
void removePentagon(std::vector<Shape> & vector);
std::vector< Point > createPointVector(const std::vector<Shape> & vector);

bool isTriangle(const Shape & shape);
bool isRectangle(const Shape & shape);
bool isSquare(const Shape & shape);

bool compareX(const Point & point1, const Point & point2);
bool compareY(const Point & point1, const Point & point2);

#endif //TASK2_HPP
