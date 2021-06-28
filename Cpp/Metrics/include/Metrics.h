#ifndef METRICS_H_
#define METRICS_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <set>

class Metrics
{
private:
    std::vector<int> y_test, y_pred;

public:
    int tp, fp, tn, fn;
    double tpr, fpr, fnr, tnr;
    Metrics(std::vector<int> y_test, std::vector<int> y_pred)
        : y_test(y_test), y_pred(y_pred),
          tp(0), fp(0), tn(0), fn(0), fpr(0.0),
          fnr(0.0), tpr(0.0), tnr(0.0) {}

    /**
     * @brief Create a confusion matrix by calculating tpr, fpr, tnr, fnr and their rates
     * 
     */
    void binary_confusion_matrix();

    /**
     * @brief Calculates the accuracy of the predictions
     * 
     * @return double 
     */
    double accuracy();
};

#endif