#include "../include/Splitter.h"

utils::dataset Splitter::random_split(double& test_pct) {
  int test_index = floor(test_pct * this->X.size());

  std::vector<std::vector<double>> X_train;
  std::vector<int> y_train;
  std::vector<std::vector<double>> X_test;
  std::vector<int> y_test;

  // Randomly shuffle the vectors!
  unsigned int seed = 42;
  std::shuffle(this->X.begin(), this->X.end(),
               std::default_random_engine(seed));
  std::shuffle(this->y.begin(), this->y.end(),
               std::default_random_engine(seed));

  for (int i = 0; i < test_index; i++) {
    X_train.push_back(this->X[i]);
    y_train.push_back(this->y[i]);
  }

  for (int i = test_index; i < this->X.size(); i++) {
    X_test.push_back(this->X[i]);
    y_test.push_back(this->y[i]);
  }

  return {X_train, y_train, X_test, y_test};
}
