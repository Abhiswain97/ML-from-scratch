#include "../include/Tfidf.h"

void Tfidf::print()
{
    for (auto &&vec : this->vec)
    {
        for (auto &&i : vec)
        {
            std::cout << i;
        }
        std::cout << std::endl;
    }
}

void Tfidf::print_vector(std::vector<std::vector<double>> &vector)
{
    for (auto &row : vector)
    {
        std::cout << "[ ";
        for (auto &element : row)
        {
            std::cout << element << " ";
        }
        std::cout << "]" << std::endl;
    }
}

double Tfidf::compute_tf(std::string &sentence, std::string &word)
{
    std::vector<std::string> tokens = this->tokenize(sentence);
    auto counts = this->make_count_map(sentence);

    return counts[word] / double(tokens.size());
}

std::map<std::string, double> Tfidf::compute_idf()
{
    std::map<std::string, double> idf_dict;

    int N = this->vec.size();

    auto unq_words = this->unique_words();

    for (auto &word : unq_words)
    {
        int counter = 0;
        for (auto &sentence : this->vec)
        {
            auto tokens = this->tokenize(sentence);
            std::for_each(
                tokens.begin(), tokens.end(), [&](std::string token) -> void
                { counter += (token.compare(word)) ? 1 : 0; });
        }

        idf_dict[word] = std::abs(log((N + 1) / double(counter + 1)));
    }

    return idf_dict;
}

std::map<std::string, int> Tfidf::make_count_map(std::string &sentence)
{
    std::map<std::string, int> count_map;
    std::vector<std::string> tokens = this->tokenize(sentence);
    for (auto &word : tokens)
    {
        if (!count_map.count(word))
            count_map[word] = 1;
        else
            count_map[word]++;
    }

    return count_map;
}

std::vector<std::string> Tfidf::tokenize(std::string &str)
{
    std::vector<std::string> tokens;

    std::stringstream sen(str);
    std::string intermediate;

    while (std::getline(sen, intermediate, ' '))
        tokens.push_back(intermediate);

    return tokens;
}

std::vector<std::string> Tfidf::unique_words()
{
    std::set<std::string> words;
    std::vector<std::string> unq_wrds;

    for (auto &sentence : this->vec)
    {
        std::vector<std::string> tokens = this->tokenize(sentence);
        std::for_each(tokens.begin(), tokens.end(), [&](auto s)
                      { words.insert(s); });
    }

    for (auto &word : words)
    {
        unq_wrds.push_back(word);
    }

    return unq_wrds;
}

std::vector<std::vector<double>> Tfidf::fit()
{
    std::vector<std::vector<double>> Tfidf_vector;

    auto idf_dict = this->compute_idf();

    auto unq_wrds = this->unique_words();

    for (auto &sentence : this->vec)
    {
        std::vector<double> tfidf_row;

        std::for_each(unq_wrds.begin(), unq_wrds.end(), [&](std::string word)
                      { tfidf_row.push_back(this->compute_tf(sentence, word) * idf_dict[word]); });
        Tfidf_vector.push_back(tfidf_row);
    }

    return Tfidf_vector;
}
