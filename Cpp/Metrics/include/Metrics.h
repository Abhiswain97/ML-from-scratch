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
    double tpr, fpr, fnr, tnr, precision, recall, f1_score, accuracy;
    Metrics(std::vector<int> y_test, std::vector<int> y_pred)
        : y_test(y_test), y_pred(y_pred),
          tp(0), fp(0), tn(0), fn(0), fpr(0.0),
          fnr(0.0), tpr(0.0), tnr(0.0),
          precision(0.0), recall(0.0),
          f1_score(0.0), accuracy(0.0) {}

    /**
     * @brief Create a a binary classification report containing: 
     * true positive rate, false positive rate, false negative rate, true negative rate, 
     * precision, recall, 
     * f1_score, accuracy
     * 
     */
    void binary_classification_report();

    /**
     * @brief Calculate log loss for binary labels
     * log-loss = -(1/n) * sum((log(y_hat ^ i) * y ^ i) + ((1 - log(y_hat ^ i)) * (1 - y ^ i)))
     * 
     * @return double 
     */
    double binary_log_loss(std::vector<double> &y_probs);
};

#endif