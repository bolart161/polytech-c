#include "task2.hpp"

void task2()
{
  std::list<std::shared_ptr<Shape>> shapes;

  std::string currentLine;
  while (std::getline(std::cin, currentLine)) {
    if (!hasData(currentLine)) {
      continue;
    }
    std::istringstream iss(currentLine);

    const std::string shapeName = readShapeName(iss);
    const Point point = readPoint(iss ,currentLine.length());
    shapes.push_back(createShape(shapeName, point));
  }

  printList(shapes.begin(), shapes.end(), "Original");

  shapes.sort(std::bind(&Shape::isMoreLeft,
                std::bind(&std::shared_ptr< Shape >::get, std::placeholders::_1),
                  std::bind(&std::shared_ptr< Shape >::get, std::placeholders::_2)));

  printList(shapes.begin(), shapes.end(), "Left-Right");
  printList(shapes.rbegin(), shapes.rend(), "Right-Left");

  shapes.sort(std::bind(&Shape::isUpper,
                std::bind(&std::shared_ptr< Shape >::get, std::placeholders::_1),
                  std::bind(&std::shared_ptr< Shape >::get, std::placeholders::_2)));

  printList(shapes.begin(), shapes.end(), "Top-Bottom");
  printList(shapes.rbegin(), shapes.rend(), "Bottom-Top");
}

std::shared_ptr<Shape> createShape(const std::string & figureName, const Point & point)
{
  if (figureName == "CIRCLE") {
    return std::make_shared< Circle >(Circle(point));
  } else if (figureName == "SQUARE") {
    return std::make_shared< Square >(Square(point));
  } else if (figureName == "TRIANGLE") {
    return std::make_shared< Triangle >(Triangle(point));
  } else {
    throw std::invalid_argument("Invalid shape name;\n");
  }
}

Point readPoint(std::istringstream & iss, const size_t & lineWidth)
{
  iss.ignore(lineWidth, '(');
  int x = 0;
  iss >> x;
  iss.ignore(lineWidth, ';');
  int y = 0;
  iss >> y;
  iss.ignore(lineWidth, ')');
  if (iss.fail()) {
    throw std::invalid_argument("Invalid point data;\n");
  }
  return {x, y};
}

std::string readShapeName(std::istringstream & iss)
{
  std::string shapeName;
  std::getline(iss, shapeName, '(');
  iss.unget();
  shapeName.erase(std::remove_if(shapeName.begin(), shapeName.end(), isspace), shapeName.end());

  if (shapeName != "CIRCLE" && shapeName != "SQUARE" && shapeName != "TRIANGLE") {
    throw std::invalid_argument("Invalid shape name;\n");
  }
  return shapeName;
}

bool hasData(const std::string & line)
{
  bool hasData = false;
  for (char i : line) {
    if (std::isspace(i)) {
      continue;
    } else {
      hasData = true;
      break;
    }
  }
  return hasData;
}
