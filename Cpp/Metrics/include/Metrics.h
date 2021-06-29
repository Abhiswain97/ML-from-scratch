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
    /**
     * @brief Finds vector of all the unique labels
     * 
     * @return std::vector<int> 
     */
    std::vector<int> unique_lables();

public:
    int tp, fp, tn, fn;
    /** True positive rate */
    double tpr,
        /** False positive rate */
        fpr,
        /** Flase negative rate */
        fnr,
        /** True negative rate */
        tnr,
        /** precision */
        precision,
        /** recall */
        recall,
        /** f1-score */
        f1_score,
        /** accuracy */
        accuracy;
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
     * log-loss = -(1/n) * sum((log(y^hat_i) * y_i) + ((1 - log(y^hat_i)) * (1 - y_i)))
     * 
     * @param y_probs: vector of predicted probabilities
     * @return double 
     */
    double binary_log_loss(std::vector<double> &y_probs);

    /**
     * @brief Calculate log loss for multi-class labels
     * log-loss = -(1/n) * sum(sum(y_ij * y^hat_ij)) 
     * where, y_ij = 1 if i'th data point belongs to j'th class other wise 0
     * @param y_probs: vector of predicted probabilities 
     * @param labels: vector of unique labels
     * @return double 
     */
    double multiclass_log_loss(std::vector<std::vector<double>> &y_probs);
};

#endif