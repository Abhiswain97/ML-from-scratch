#include "../include/Metrics.h"

void Metrics::binary_classification_report()
{
    for (size_t i = 0; i < this->y_test.size(); i++)
        if (this->y_test[i] == 1 && this->y_pred[i] == 1)
            this->tp++;
        else if (this->y_test[i] == 0 && this->y_pred[i] == 0)
            this->tn++;
        else if (this->y_test[i] == 0 && this->y_pred[i] == 1)
            this->fp++;
        else
            this->fn++;

    this->tpr = this->tp / double(this->fn + this->tp);
    this->fnr = this->fn / double(this->fn + this->tp);
    this->tnr = this->tn / double(this->fp + this->tn);
    this->fpr = this->fp / double(this->fp + this->tn);

    this->precision = this->tp / double(this->tp + this->fp);
    this->recall = this->tpr;

    this->f1_score = (2 * (this->precision * this->recall)) / double(this->recall + this->precision);
    this->accuracy = (this->tp + this->tn) / double(this->y_test.size());

    std::cout
        << "\t"
        << "0"
        << "\t"
        << "1"
        << "\n";

    std::cout << "0"
              << "\t" << this->tn << "\t" << this->fn << "\n";

    std::cout << "1"
              << "\t" << this->fp << "\t" << this->tp << "\n";

    std::cout << "Precision: " << this->precision << "\n";
    std::cout << "Recall: " << this->recall << "\n";
    std::cout << "F1-score: " << this->f1_score << "\n";
    std::cout << "Accuracy: " << this->accuracy << "\n";
}

int main(int argc, char const *argv[])
{
    std::vector<int> y_test = {1,
                               0,
                               0,
                               1,
                               0,
                               1,
                               1};

    std::vector<int> y_pred = {0,
                               0,
                               1,
                               1,
                               0,
                               1,
                               1};

    Metrics metrics(y_test, y_pred);

    metrics.binary_classification_report();

    std::cout << "True positive rate: " << metrics.tpr << std::endl;
}