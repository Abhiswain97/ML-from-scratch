#include "../Cpp/NLP/feature_extraction/include/BOW.h"
#include "../Cpp/NLP/feature_extraction/include/Tfidf.h"

int main(int argc, char const *argv[])
{
    int n;

    std::cout << "Enter the method you want to use: "
              << "\n [1] Bag of Words \n [2] TFIDF"
              << "\n Press 0 to exit" << std::endl;

    std::string path = argv[1];

    std::ifstream file(path.c_str());

    std::string line;
    std::vector<std::string> corpus1;

    while (std::getline(file, line))
    {
        corpus1.push_back(line);
    }

    // BOW bow(corpus1);

    // auto bow_vector = bow.fit();

    // bow.print_vector(bow_vector);

    do
    {
        std::cin >> n;
        if (n == 1)
        {
            BOW bow(corpus1);

            auto bow_vector = bow.fit();

            bow.print_vector(bow_vector);
        }
        else if (n == 2)
        {
            Tfidf tfidf(corpus1);

            auto tfidf_vector = tfidf.fit();

            tfidf.print_vector(tfidf_vector);
        }
        else if (n == 0)
        {
            exit(0);
        }
        else
        {
            std::cout << "Invalid input" << std::endl;
        }
    } while (n != 0);

    return 0;
}