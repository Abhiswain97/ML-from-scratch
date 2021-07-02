#include "../include/Metrics.h"

std::vector<int> Metrics::unique_lables() {
  std::set<int> lbls;
  std::vector<int> f_lbls;
  std::for_each(y_test.begin(), y_test.end(),
                [&](int ele) -> void { lbls.insert(ele); });

  std::for_each(f_lbls.begin(), f_lbls.end(),
                [&](int ele) -> void { f_lbls.push_back(ele); });

  return f_lbls;
}

void Metrics::binary_classification_report() {
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

  this->f1_score = (2 * (this->precision * this->recall)) /
                   double(this->recall + this->precision);
  this->accuracy = (this->tp + this->tn) / double(this->y_test.size());

  std::cout << "\t"
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

double Metrics::binary_log_loss(std::vector<double> &y_probs) {
  double sum = 0.0;
  for (int i = 0; i < this->y_test.size(); i++)
    sum += (this->y_test[i] * log(y_probs[i])) +
           ((1 - this->y_test[i]) * log(1 - y_probs[i]));

  return (-1) * (1 / double(this->y_test.size())) * sum;
}

// ------------------------------------------------- WIP
// ------------------------------------------------------ //
double Metrics::multiclass_log_loss(std::vector<std::vector<double>> &y_probs) {
  std::vector<int> labels = this->unique_lables();
  for (int i = 0; i < this->y_test.size(); i++) {
    for (int j = 0; j < labels.size(); j++) {
      if (labels[j] == y_test[i]) {
      }
    }
  }
}
// ------------------------------------------------- WIP
// ------------------------------------------------------ //

// int main(int argc, char const *argv[])
// {
//     std::vector<int> y_test = {1,
//                                0,
//                                0,
//                                1,
//                                0,
//                                1,
//                                1};

//     std::vector<int> y_pred = {0,
//                                0,
//                                1,
//                                1,
//                                0,
//                                1,
//                                1};

//     Metrics metrics(y_test, y_pred);

//     metrics.binary_classification_report();

//     std::cout << "True positive rate: " << metrics.tpr << std::endl;
// }