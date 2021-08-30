#pragma once

#ifndef UTILS_H_
#define UTILS_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

namespace utils {

struct dataset {
  std::vector<std::vector<double>> X_train;
  std::vector<int> y_train;
  std::vector<std::vector<double>> X_test;
  std::vector<int> y_test;
};

/**
 * Create a map of counts of each word in string
 * @param sentence: The string
 * @return map containing counts of each word
 */
std::map<std::string, int> make_count_map(std::string& sentence);

/**
 * Tokenize a sentence by spaces
 * @param str: The string to tokenize
 * @return vector containing tokens
 */
std::vector<std::string> tokenize(std::string& str);

/**
 * Create a vector of unique words from the corpus
 * @return vector of unique words
 */
std::vector<std::string> unique_words(std::vector<std::string>& corpus);

/**
 * Print the contents of the bow_vector
 *
 * @param vector which is to be printed
 */
void print_vector(std::vector<std::vector<double>>& vector);

/**
 * Print the contents of the corpus.
 */
void print(std::vector<std::string>& vec);

/**
 * @brief Read and parse a CSV file.
 *
 * @param filename: The name of the file to read.
 */
void read_csv(std::string& filename);

}  // namespace utils
#endif  // !UTILS_H_
