#pragma once
#ifndef SPLITTER_H_
#define SPLITTER_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "../include/Utils.h"

class Splitter {
 private:
  std::vector<std::vector<double>> X;
  std::vector<int> y;

 public:
  Splitter(std::vector<std::vector<double>>& X, std::vector<int>& y)
      : X(X), y(y) {}

  /**
   * Randomly splits the dataset into train and test dataset
   * @param test_pct: The percentage of test split
   * @return a struct containing X_train, y_train, X_test & y_test
   */
  utils::dataset random_split(double& test_pct);
};

#endif