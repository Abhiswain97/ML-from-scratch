#include "../include/Utils.h"

std::map<std::string, int> utils::make_count_map(std::string& sentence) {
  std::map<std::string, int> count_map;
  std::vector<std::string> tokens = tokenize(sentence);
  for (auto& word : tokens) {
    if (!count_map.count(word))
      count_map[word] = 1;
    else
      count_map[word]++;
  }

  return count_map;
}

std::vector<std::string> utils::tokenize(std::string& str) {
  std::vector<std::string> tokens;

  std::stringstream sen(str);
  std::string intermediate;

  while (std::getline(sen, intermediate, ' ')) tokens.push_back(intermediate);

  return tokens;
}

std::vector<std::string> utils::unique_words(std::vector<std::string>& corpus) {
  std::set<std::string> words;
  std::vector<std::string> unq_wrds;

  for (auto& sentence : corpus) {
    std::vector<std::string> tokens = tokenize(sentence);
    std::for_each(tokens.begin(), tokens.end(),
                  [&](auto s) { words.insert(s); });
  }

  for (auto& word : words) {
    unq_wrds.push_back(word);
  }

  return unq_wrds;
}

void utils::print_vector(std::vector<std::vector<double>>& vector) {
  for (auto& row : vector) {
    std::cout << "[ ";
    for (auto& element : row) {
      std::cout << element << "\t";
    }
    std::cout << "]" << std::endl;
  }
}

void utils::print(std::vector<std::string>& vec) {
  for (auto&& v1 : vec) {
    for (auto&& i : v1) {
      std::cout << i;
    }
    std::cout << std::endl;
  }
}

void utils::read_csv(std::string& filename) {
  std::ifstream ifs(filename);

  std::string line;

  while (std::getline(ifs, line)) {
    std::cout << line << std::endl;
  }
}