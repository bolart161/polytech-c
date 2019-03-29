#ifndef ACCESS_BEHAVIOR_HPP
#define ACCESS_BEHAVIOR_HPP

#include <vector>
#include <iostream>


template <typename T>
class AccessBehavior
{
public:
  using elemType = typename T::value_type;

  virtual ~AccessBehavior() = default;
  virtual elemType* getElement(const T &collection, const typename T::iterator iter) const = 0;
};

template <typename T>
class AtAccess: public AccessBehavior<T>
{
public:
  using elemType = typename AccessBehavior<T>::elemType;

  elemType* getElement(const T &collection, const typename T::iterator iter) const
  {
    const size_t index = std::distance<typename T::const_iterator>(collection.begin(), iter);
    return const_cast<elemType*>(&collection.at(index));
  };
};

template <typename T>
class BracketAccess: public AccessBehavior<T>
{
public:
  using elemType = typename AccessBehavior<T>::elemType;

  elemType* getElement(const T &collection, const typename T::iterator iter) const
  {
    const size_t index = std::distance<typename T::const_iterator>(collection.begin(), iter);
    return const_cast<elemType*>(&collection[index]);
  };
};

template <typename T>
class IterAccess: public AccessBehavior<T>
{
public:
  using elemType = typename AccessBehavior<T>::elemType;

  elemType* getElement(const T &/*collection*/ , const typename T::iterator iter) const
  {
    return &(*iter);
  };
};

#endif
