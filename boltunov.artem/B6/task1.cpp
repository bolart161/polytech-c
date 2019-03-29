#include "task1.hpp"

void task1()
{
  std::set<std::string> set = readText();

  for (const auto &it : set) {
    std::cout << it << "\n";
  }
};

std::set<std::string> readText()
{
  std::set<std::string> set;
  std::string line;

  while (std::getline(std::cin, line)){
    std::istringstream iss(line);
    std::string word;
    while (iss >> word){
      set.insert(word);
    }
  }
  return set;
}
