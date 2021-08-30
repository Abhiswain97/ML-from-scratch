#pragma once
#ifndef BOW_H_
#define BOW_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

class BOW {
 private:
  std::vector<std::string> vec;

 public:
  BOW(std::vector<std::string>& vec) : vec(vec) {}

  /**
   * Calculate the Bag of words vector from the corpus.
   * @return Bag of words vector
   */
  std::vector<std::vector<double>> fit();
};

#endif