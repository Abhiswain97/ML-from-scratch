#ifndef _PREPROCESS_H__
#define _PREPROCESS_H__

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <sstream>
#include <set>
#include <fstream>

class Preprocess
{
private:
    /**
     * @brief vecotr of string labels or categorical features
     * 
     */
    std::vector<std::string> labels;

public:
    /**
     * @brief Construct a new Preprocess object
     * 
     * @param labels 
     */
    Preprocess(std::vector<std::string> &labels)
        : labels(labels) {}

    /**
     * @brief one hot encode labels or features
     * 
     * @return std::map<std::string, std::vector<int>>
     */
    std::map<std::string, std::vector<int>> one_hot_encode();
};

#endif