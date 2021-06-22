#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

struct split_ret
{
    std::vector<std::vector<double>> X_train;
    std::vector<int> y_train;
    std::vector<std::vector<double>> X_test;
    std::vector<int> y_test;
};

class Splitter
{
private:
    std::vector<std::vector<double>> X;
    std::vector<int> y;

public:
    Splitter(std::vector<std::vector<double>> &X, std::vector<int> &y)
        : X(X), y(y) {}

    struct split_ret random_split(double &test_pct);
};