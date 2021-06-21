#include "../include/Splitter.h"

struct split_ret Splitter::random_split(double &test_pct)
{
    int test_index = floor(test_pct * this->X.size());

    std::vector<std::vector<double>> X_train;
    std::vector<int> y_train;
    std::vector<std::vector<double>> X_test;
    std::vector<int> y_test;

    // Randomly shuffle the vectors!

    unsigned int seed = 7;
    std::shuffle(this->X.begin(), this->X.end(), std::default_random_engine(seed));
    std::shuffle(this->y.begin(), this->y.end(), std::default_random_engine(seed));

    for (int i = 0; i < test_index; i++)
    {
        X_train.push_back(this->X[i]);
        y_train.push_back(this->y[i]);
    }

    for (int i = test_index; i < this->X.size(); i++)
    {
        X_test.push_back(this->X[i]);
        y_test.push_back(this->y[i]);
    }

    return {X_train, y_train, X_test, y_test};
}

int main(int argc, char const *argv[])
{
    std::vector<std::vector<double>> X = {{1.0, 2.0, 3.0, 4.0, 5.0},
                                          {1.0, 2.0, 3.0, 4.0, 6.0},
                                          {1.0, 2.0, 3.0, 4.0, 7.0},
                                          {1.0, 2.0, 3.0, 4.0, 8.0},
                                          {1.0, 2.0, 3.0, 4.0, 9.0}};
    std::vector<int> y = {
        1,
        2,
        3,
        4,
        5,
    };

    Splitter s(X, y);

    double pct = 0.75;

    std::cout << y[0] << std::endl;

    auto ret = s.random_split(pct);

    std::cout << ret.X_train.size() << " " << ret.y_train.size() << " " << ret.X_test.size() << " " << ret.y_test.size() << std::endl;

    std::cout << ret.y_train[0] << std::endl;

    return 0;
}
