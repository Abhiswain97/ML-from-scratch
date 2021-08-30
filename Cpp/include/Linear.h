#pragma once

#ifndef LINEAR_H_
#define LINEAR_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

#include "../include/Utils.h"

class LinearModels {
 public:
  utils::dataset dataset;

  /**
   * @brief Construct a new Linear Models object
   *
   * @param dataset The dataset to use for the linear models
   */
  LinearModels(utils::dataset& dataset) : dataset(dataset) {}

  /**
   * @brief
   *
   */
  void initialize_weight_bias();

  /**
   * @brief Find h_theta(x) for a given x
   *
   */
  double h_theta(const std::vector<double>& x);
};

#endif