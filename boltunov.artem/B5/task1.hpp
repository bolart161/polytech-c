#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

int readKey(std::istringstream & iss);
std::string readStr(std::istringstream & iss);
std::vector<DataStruct> readVector();

bool cmpKey(const DataStruct & struct1, const DataStruct & struct2);

void task1();

#endif // TASK_HPP
