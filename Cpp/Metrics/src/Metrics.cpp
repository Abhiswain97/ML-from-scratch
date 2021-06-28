#include "../include/Metrics.h"

double Metrics::accuracy()
{
    int count = 0;
    for (size_t i = 0; i < this->y_test.size(); i++)
        if (this->y_test[i] == this->y_pred[i])
            count++;

    return count / double(this->y_test.size());
}

void Metrics::binary_confusion_matrix()
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

    std::cout << "\t"
              << "0"
              << "\t"
              << "1"
              << "\n";

    std::cout << "0"
              << "\t" << this->tn << "\t" << this->fn << "\n";

    std::cout << "1"
              << "\t" << this->fp << "\t" << this->tp << "\n";
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

    metrics.binary_confusion_matrix();

    std::cout << "True positive rate: " << metrics.tpr << std::endl;

    std::cout << "Accuracy: " << metrics.accuracy();
}