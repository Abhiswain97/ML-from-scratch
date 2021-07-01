#ifndef PLOT_H_
#define PLOT_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <set>

using two_d_vector = std::vector<std::vector<double>>;
using one_d_vector = std::vector<int>;

template <typename T1, typename T2>
class Plot
{
private:
    T1 x;
    T2 y;

public:
    /**
     * @brief Construct a new Plot object
     * 
     */
    Plot()
        : x(x), y(y) {}

    /**
     * @brief Plot x and y 
     * 
     */
    void plot();
};

#endif