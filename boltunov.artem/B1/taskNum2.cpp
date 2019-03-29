#include <fstream>
#include <vector>
#include <memory>
#include <iostream>


int taskNum2(const char *fileName)
{
  std::ifstream inputStream(fileName);
  if (!inputStream) {
    std::cerr << "This file doesn't exist;";
    return 1;
  }

  inputStream.seekg(0, inputStream.end);
  const size_t length = inputStream.tellg();
  inputStream.seekg(0, inputStream.beg);

  std::unique_ptr<char[]> array (new char[length]);

  inputStream.read(array.get(), length);
  if (inputStream) {
    std::vector<char> vector(array.get(), array.get() + length);
    for (auto i = vector.begin(); i != vector.end(); i++) {
      std::cout << *i;
    }
  }
  inputStream.close();
  return 0;
}
