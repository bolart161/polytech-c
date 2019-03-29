#include "utils.hpp"

void task1(std::istream & istream, std::ostream & ostream)
{
  QueueWithPriority<std::string> queue;
  std::string line;

  while (std::getline(istream, line)) {
    std::stringstream stream(line);
    std::string command;
    stream >> command;

    if (command == "add") {
      add(stream, queue, ostream);
    } else if ((command == "get") && (stream.eof())) {
      get(queue, ostream);
    } else if ((command == "accelerate") && (stream.eof())) {
      accelerate(queue);
    } else {
      ostream << "<INVALID COMMAND>" << std::endl;
    }

    if (std::cin.eof()) {
      break;
    }
  }
}
