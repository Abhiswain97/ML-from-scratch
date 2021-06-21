#ifndef TFIDF_H_
#define TFIDF_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <sstream>
#include <set>
#include <fstream>

class Tfidf
{
private:
    std::vector<std::string> vec;

public:
    Tfidf(std::vector<std::string> &vec)
        : vec(vec) {}
    void print();
    std::vector<std::string> unique_words();
    std::map<std::string, int> make_count_map(std::string &sentence);
    std::vector<std::string> tokenize(std::string &sen);
    double compute_tf(std::string &sentence, std::string &word);
    std::map<std::string, double> compute_idf();
    std::vector<std::vector<double>> fit();
    void print_vector(std::vector<std::vector<double>> &vector);
};

#endif