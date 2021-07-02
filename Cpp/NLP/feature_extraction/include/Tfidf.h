#ifndef TFIDF_H_
#define TFIDF_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

/**
 * Class containing utilities for computing TFIDF of a corpus of sentences.
 */
class Tfidf {
 private:
  /**
   * Stores the corpus as a vector of strings.
   */
  std::vector<std::string> vec;

 public:
  /**
   * Default constructor taking in the vector of strings
   */
  Tfidf(std::vector<std::string> &vec) : vec(vec) {}

  /**
   * Print the contents of the corpus.
   */
  void print();

  /**
   * Create a vector of unique words from the corpus
   * @return vector of unique words
   */
  std::vector<std::string> unique_words();

  /**
   * Create a map of counts of each word in string
   * @param sentence: The string
   * @return map containing counts of each word
   */
  std::map<std::string, int> make_count_map(std::string &sentence);

  /**
   * Tokenize a sentence by spaces
   * @param str: The string to tokenize
   * @return vector containing tokens
   */
  std::vector<std::string> tokenize(std::string &sen);

  /**
   * Computes the term-frequency of a word in a sentence
   * tf(sentence, word) = (# occurences of word in the sentence) / (# words in
   * the sentence)
   * @param sentence: the sentence/document
   * @param word: the word
   * @return computed tf value
   */
  double compute_tf(std::string &sentence, std::string &word);

  /**
   * Computes the inverse-document-frequency of all unique words in the corpus
   * idf[word] = (# documents) / (# documents containing the word)
   *
   * @return A map containing all the unique words with their correpsonding idf
   * values
   */
  std::map<std::string, double> compute_idf();

  /**
   * Calculate the TFIDF vector from the corpus.
   * @return TFIDF vector
   */
  std::vector<std::vector<double>> fit();

  /**
   * Print the contents of the Tfidf_vector
   * @param vector which is to be printed
   */
  void print_vector(std::vector<std::vector<double>> &vector);
};

#endif