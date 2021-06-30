#ifndef BOW_H_
#define BOW_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <sstream>
#include <set>
#include <fstream>

class BOW
{
private:
    std::vector<std::string> vec;

public:
    BOW(std::vector<std::string> &vec)
        : vec(vec) {}
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
     * Calculate the Bag of words vector from the corpus.
     * @return Bag of words vector
     */
    std::vector<std::vector<double>> fit();

    /**
     * Print the contents of the bow_vector
     * 
     * @param vector which is to be printed
     */
    void print_vector(std::vector<std::vector<double>> &vector);
};

#endif