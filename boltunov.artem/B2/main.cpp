#include "symbolsReader.hpp"
#include "parserText.hpp"

void formatText(int argc, char** argv){
  if ((argc > 3) || (argc == 2)) {
    throw std::invalid_argument("Wrong options;");
  }

  size_t width = 40;

  if (argc == 3) {
    if (std::string(argv[1]) != "--line-width") {
      throw std::invalid_argument("Incorrect option;");
    }

    width = std::atoi(argv[2]);
    // MinWidth = 20 + 3 + 1 + 1   20(MaxSizeWord/Number) 3(dash) 1(punctuation) 1(gap)
    if (width < 24) {
      throw std::invalid_argument("Invalid line width;");
    }
  }

  SymbolsReader symbolsReader;
  ParserText parser(symbolsReader, width);
  parser.parse();
  parser.printText();
}

int main(int argc, char** argv) {
  try {
    formatText(argc, argv);
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
