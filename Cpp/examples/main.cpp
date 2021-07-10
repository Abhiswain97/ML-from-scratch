#include "../include/BOW.h"
#include "../include/Metrics.h"
#include "../include/Splitter.h"
#include "../include/Tfidf.h"

using pred_probs = std::pair<std::vector<int>, std::vector<double>>;

pred_probs dummy_model(std::vector<std::vector<double>> &X_train,
                       std::vector<int> &y_train) {
  double sum = 0.0, avg = 0.0;
  std::vector<int> y_pred;
  std::vector<double> y_probs;

  for (auto &feature : X_train) {
    std::for_each(feature.begin(), feature.end(),
                  [&](double f) -> void { sum += f; });
    avg = sum / (double)feature.size();

    y_probs.push_back(avg);

    // std::cout << avg << " ";

    if (avg < 0.5)
      y_pred.push_back(0);
    else
      y_pred.push_back(1);
  }

  return std::make_pair(y_pred, y_probs);
}

int main(int argc, char const *argv[]) {
  int n;

  std::cout << "Enter the method you want to use: "
            << "\n [1] Bag of Words \n [2] TFIDF" << std::endl;

  std::cin >> n;

  if (argc < 2) {
    std::cout << "One or more arguments are missing"
              << "\n"
              << "Making a graceful exit"
              << "\n";
    exit(0);
  } else {
    std::string features_path = argv[1];
    std::string labels_path = argv[2];

    std::ifstream file(features_path.c_str());
    std::ifstream file1(labels_path.c_str());

    std::string line;
    std::vector<std::string> corpus;

    while (std::getline(file, line)) {
      corpus.push_back(line);
    }

    std::string line2;
    std::vector<int> labels;
    int t;

    while (std::getline(file1, line2)) {
      sscanf(line2.c_str(), "%d", t);
      labels.push_back(t);
    }

    Tfidf tfidf(corpus);
    BOW bow(corpus);

    auto features = (n == 1) ? bow.fit() : tfidf.fit();

    Splitter splitter(features, labels);

    double pct = 0.75;

    auto dataset = splitter.random_split(pct);

    auto X_train = dataset.X_train;
    auto y_train = dataset.y_train;
    auto X_test = dataset.X_test;
    auto y_test = dataset.y_test;

    auto values = dummy_model(X_train, y_train);

    Metrics metrics(y_test, values.first);

    metrics.binary_classification_report();

    std::cout << "Binary log-loss: " << metrics.binary_log_loss(values.second);
  }

  return 0;
}