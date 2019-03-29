#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>
#include <list>
#include <map>
#include <iterator>

class PhoneBook
{
public:
  typedef struct
  {
    std::string number;
    std::string name;
  } record_type;

  PhoneBook();
  void setCurrentMark(const std::string & mark);
  void addRecord(const record_type & record);
  record_type & getRecord();
  void moveMark(int n);
  void setMarkToFirst();
  void setMarkToLast();
  void insertBefore(const record_type & record);
  void insertAfter(const record_type & record);
  void duplicateMark(const std::string & new_mark);
  void delRecord();
  bool empty() const;

private:
  
  typedef std::list<record_type> list_type;

  list_type list_;
  std::map<std::string, list_type::iterator> marks_;
  std::map<std::string, list_type::iterator>::iterator currentMark_;
  void checkRecord(const record_type & record) const;
};
    


#endif
