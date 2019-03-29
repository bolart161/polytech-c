
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>
#include <stdexcept>

template<typename T>
class QueueWithPriority
{
public:
  enum  ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void putElementToQueue(const T & element, ElementPriority priority);
  const T & getElementFromQueue() const;
  void pop();
  void accelerate();
  bool empty() const;

private:
  std::list<T> queue_[3];
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T & element, ElementPriority priority)
{
  queue_[priority].push_back(element);
}

template<typename T>
const T & QueueWithPriority<T>::getElementFromQueue() const
{
  if (empty()) {
    throw std::out_of_range("Trying get element in empty queue");
  }

  ElementPriority priority = ElementPriority::LOW;

  if (!queue_[ElementPriority::HIGH].empty()) {
    priority = ElementPriority::HIGH;
  } else if (!queue_[ElementPriority::NORMAL].empty()) {
    priority = ElementPriority::NORMAL;
  }
  return queue_[priority].front();
}

template<typename T>
void QueueWithPriority<T>::pop()
{
  if (empty()) {
    throw std::out_of_range("Trying get element in empty queue");
  }

  ElementPriority priority = ElementPriority::LOW;

  if (!queue_[ElementPriority::HIGH].empty()) {
    priority = ElementPriority::HIGH;
  } else if (!queue_[ElementPriority::NORMAL].empty()) {
    priority = ElementPriority::NORMAL;
  }
  queue_[priority].pop_front();
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  queue_[ElementPriority::HIGH].splice(queue_[ElementPriority::HIGH].end(), queue_[ElementPriority::LOW]);
}

template<typename T>
bool QueueWithPriority<T>::empty() const
{
  for (std::size_t i = 0; i < 3; i++) {
    if (!queue_[i].empty()) {
      return false;
    }
  }
  return true;
}

#endif // QUEUE_HPP
