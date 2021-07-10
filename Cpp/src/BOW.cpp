#include "../include/BOW.h"

void BOW::print() {
  for (auto &&vec : this->vec) {
    for (auto &&i : vec) {
      std::cout << i;
    }
    std::cout << std::endl;
  }
}

void BOW::print_vector(std::vector<std::vector<double>> &vector) {
  for (auto &row : vector) {
    std::cout << "[ ";
    for (auto &element : row) {
      std::cout << element << " ";
    }
    std::cout << "]" << std::endl;
  }
}

std::map<std::string, int> BOW::make_count_map(std::string &sentence) {
  std::map<std::string, int> count_map;
  std::vector<std::string> tokens = this->tokenize(sentence);
  for (auto &word : tokens) {
    if (!count_map.count(word))
      count_map[word] = 1;
    else
      count_map[word]++;
  }

  return count_map;
}

std::vector<std::string> BOW::tokenize(std::string &str) {
  std::vector<std::string> tokens;

  std::stringstream sen(str);
  std::string intermediate;

  while (std::getline(sen, intermediate, ' ')) tokens.push_back(intermediate);

  return tokens;
}

std::vector<std::string> BOW::unique_words() {
  std::set<std::string> words;
  std::vector<std::string> unq_wrds;

  for (auto &sentence : this->vec) {
    std::vector<std::string> tokens = this->tokenize(sentence);
    std::for_each(tokens.begin(), tokens.end(),
                  [&](auto s) { words.insert(s); });
  }

  for (auto &word : words) {
    unq_wrds.push_back(word);
  }

  return unq_wrds;
}

std::vector<std::vector<double>> BOW::fit() {
  std::vector<std::vector<double>> bow_vector;

  for (auto &sentence : this->vec) {
    std::vector<double> bow_row;

    std::map<std::string, int> counts = this->make_count_map(sentence);
    std::vector<std::string> words = this->unique_words();

    for (auto &word : words) {
      if (counts.count(word))
        bow_row.push_back((double)counts[word]);
      else
        bow_row.push_back(0.0);
    }
    bow_vector.push_back(bow_row);
  }

  return bow_vector;
}