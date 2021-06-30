#include "../Cpp/NLP/feature_extraction/include/Tfidf.h"
#include "../Cpp/NLP/feature_extraction/include/BOW.h"
#include "../Cpp/Data/include/Splitter.h"
#include "../Cpp/Metrics/include/Metrics.h"

std::vector<int> dummy_model(std::vector<std::vector<double>> &X_train, std::vector<int> &y_train)
{
    double sum = 0.0, avg = 0.0;
    std::vector<int> y_pred;

    for (auto &feature : X_train)
    {
        std::for_each(feature.begin(), feature.end(), [&](double f) -> void
                      { sum += f; });
        avg = sum / (double)feature.size();

        if (avg < 0.5)
            y_pred.push_back(0);
        else
            y_pred.push_back(1);
    }

    return y_pred;
}

int main(int argc, char const *argv[])
{
    int n;

    std::cout << "Enter the method you want to use: "
              << "\n [1] Bag of Words \n [2] TFIDF"
              << "\n Press 0 to exit" << std::endl;

    std::cin >> n;

    std::string features_path = argv[1];
    std::string labels_path = argv[2];

    std::ifstream file(features_path.c_str());
    std::ifstream file1(labels_path.c_str());

    std::string line;
    std::vector<std::string> corpus;

    while (std::getline(file, line))
    {
        corpus.push_back(line);
    }

    std::string line2;
    std::vector<int> labels;
    int t;

    while (std::getline(file1, line2))
    {
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

    auto y_pred = dummy_model(X_train, y_train);

    Metrics metrics(y_test, y_pred);

    metrics.binary_classification_report();

    std::cout << metrics.precision << " " << metrics.recall;

    return 0;
}