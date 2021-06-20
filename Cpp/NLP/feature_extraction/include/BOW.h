#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <sstream>
#include <set>

class BOW
{
private:
    std::vector<std::string> vec;

public:
    BOW(std::vector<std::string> &vec)
        : vec(vec) {}
    void print();
    std::vector<std::string> unique_words();
    std::map<std::string, int> make_count_map(std::string &sentence);
    std::vector<std::string> tokenize(std::string &sen);
    std::vector<std::vector<int>> fit();
    void print_vector(std::vector<std::vector<int>> &vector);
};