#include "utils.hpp"

void add(std::stringstream & istream, QueueWithPriority<std::string> & queue, std::ostream & ostream) {
  std::string priority;
  istream >> priority;
  std::string data;
  istream.ignore();
  std::getline(istream, data);


  if (data.empty()) {
    ostream << "<INVALID COMMAND>" << std::endl;
  } else if (priority == "high") {
    queue.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::HIGH);
  } else if (priority == "normal") {
    queue.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::NORMAL);
  } else if (priority == "low") {
    queue.putElementToQueue(data, QueueWithPriority<std::string>::ElementPriority::LOW);
  } else {
    ostream << "<INVALID COMMAND>" << std::endl;
  }
}

void get(QueueWithPriority<std::string> & queue, std::ostream & ostream) {
  if (queue.empty()) {
    ostream << "<EMPTY>" << std::endl;
  } else {
    ostream << queue.getElementFromQueue() << std::endl;
    queue.pop();
  }
}

void accelerate(QueueWithPriority<std::string> & queue) {
  queue.accelerate();
}
