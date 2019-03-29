#include "task1.hpp"

int readKey(std::istringstream & iss)
{
  int key = 0;
  iss >> key;

  if ((key < -5) || (key > 5)) {
    throw std::invalid_argument("Invalid key\n");
  }
  return key;
}

std::string readStr(std::istringstream & iss)
{
  iss >> std::ws; // skip wordspace
  std::string str;
  std::getline(iss, str);

  if (str.empty()) {
    throw std::invalid_argument("Invalid str\n");
  }
  return str;
}

std::vector<DataStruct> readVector()
{
  std::vector<DataStruct> vector;

  std::string line;

  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);

    const int key1 = readKey(iss);
    iss.ignore(line.length(), ',');
    const int key2 = readKey(iss);
    iss.ignore(line.length(), ',');
    std::string string = readStr(iss);
    vector.push_back(DataStruct{key1, key2, string});
  }
  return vector;
}

bool cmpKey(const DataStruct & dataStruct1, const DataStruct & dataStruct2)
{
  if (dataStruct1.key1 != dataStruct2.key1) {
    return dataStruct1.key1 < dataStruct2.key1;
  } else if (dataStruct1.key2 != dataStruct2.key2) {
    return dataStruct1.key2 < dataStruct2.key2;
  } else {
    return dataStruct1.str.size() < dataStruct2.str.size();
  }
}

void task1()
{
  std::vector<DataStruct> vector = readVector();
  std::sort(vector.begin(), vector.end(), cmpKey);

  for (auto & it : vector) {
    std::cout << it.key1 << "," << it.key2 << "," << it.str << "\n";
  }
}
