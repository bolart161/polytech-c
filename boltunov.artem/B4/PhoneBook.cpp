#include "PhoneBook.hpp"
#include <cctype>

PhoneBook::PhoneBook()
{
  marks_.insert({ "current", list_.begin() });
  currentMark_ = marks_.begin();
}

void PhoneBook::setCurrentMark(const std::string & mark)
{
  auto iter = marks_.find(mark);
  if (iter == marks_.end())
  {
    throw std::invalid_argument("Unnown mark naem");
  }
  currentMark_ = iter;
}

void PhoneBook::addRecord(const record_type & record)
{
  checkRecord(record);
  list_.push_back(record);
  if (currentMark_->second == list_.cend())
  {
    currentMark_->second--;
  }
}

PhoneBook::record_type & PhoneBook::getRecord()
{
  if (empty())
  {
    throw std::invalid_argument("Phone book is empty");
  }
  return *currentMark_->second;
}

void PhoneBook::setMarkToFirst()
{
  currentMark_->second = list_.begin();
}

void PhoneBook::setMarkToLast()
{
  currentMark_->second = --list_.end();
}

void PhoneBook::moveMark(int n)
{
  int distance = (n > 0) ? std::distance(currentMark_->second, list_.end()) : 
      std::distance(list_.begin(), currentMark_->second);
  if (distance < abs(n))
  {
    throw std::invalid_argument("Stpes out of range");
  }
  std::advance(currentMark_->second, n);
}

void PhoneBook::insertBefore(const record_type & record)
{
  checkRecord(record);
  list_.insert(currentMark_->second, record);
  if (currentMark_->second == list_.cend())
  {
    currentMark_->second--;
  }
}

void PhoneBook::insertAfter(const record_type & record)
{
  if (currentMark_->second == list_.cend())
  {
    list_.insert(currentMark_->second, record);
    currentMark_->second--;
    return;
  }
  checkRecord(record);
  list_.insert(++(currentMark_->second), record);
  moveMark(-2);
}

void PhoneBook::duplicateMark(const std::string & new_mark)
{
  if (new_mark.empty())
  {
    throw std::invalid_argument("Invalid name of new mark");
  }
  marks_.insert({ new_mark, currentMark_->second });
}

void PhoneBook::delRecord()
{
  auto delIter = currentMark_->second;
  for (auto iter = marks_.begin(); iter != marks_.end(); iter++)
  {
    if (iter->second == delIter)
    {
      iter->second++;
      if (iter->second == list_.end() && list_.size() > 1)
      {
        std::advance(iter->second, -2);
      }
    }
  }
  list_.erase(delIter);
}

bool PhoneBook::empty() const
{
  if (list_.empty())
  {
    return true;
  }
  return false;
}

void PhoneBook::checkRecord(const record_type & record) const
{
  auto iter = record.number.begin();
  while (iter != record.number.cend() && isdigit(*iter))
  {
    iter++;
  }
  if (record.name.empty() || record.number.empty() || iter != record.number.cend())
  {
    throw std::invalid_argument("Invalid new record");
  }
}
