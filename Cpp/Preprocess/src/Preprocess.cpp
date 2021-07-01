#include "../include/Preproces.h"

std::map<std::string, std::vector<int>> Preprocess::one_hot_encode()
{
    std::map<std::string, std::vector<int>> encoded_dict;

    int i = 0;

    std::for_each(this->labels.begin(), this->labels.end(), [&](std::string label) -> void
                  {
                      std::vector<int> vec(this->labels.size(), 0);

                      vec[i++] = 1;

                      encoded_dict[label] = vec;
                  });

    return encoded_dict;
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> labels = {"Red", "Green", "Blue"};

    Preprocess p(labels);

    auto vec = p.one_hot_encode();

    std::for_each(labels.begin(), labels.end(), [&](auto label) -> void
                  {
                      std::cout << label << " : ";
                      std::for_each(vec[label].begin(), vec[label].end(), [&](int i) -> void
                                    { std::cout << i << " "; });
                      std::cout << std::endl;
                  });

    return 0;
}
