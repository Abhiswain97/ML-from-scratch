#include "../include/BOW.h"

/**
 * Print the contents of the corpus.
 */
void BOW::print()
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

/**
 * Print the contents of the bow_vector
 * 
 * @param vector which is to be printed
 */
void BOW::print_vector(std::vector<std::vector<int>> &vector)
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

/**
 * Create a map of counts of each word in string
 * @param sentence: The string
 * @return map containing counts of each word
 */
std::map<std::string, int> BOW::make_count_map(std::string &sentence)
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

/**
 * Tokenize a sentence by spaces
 * @param str: The string to tokenize
 * @return vector containing tokens
 */
std::vector<std::string> BOW::tokenize(std::string &str)
{
    std::vector<std::string> tokens;

    std::stringstream sen(str);
    std::string intermediate;

    while (std::getline(sen, intermediate, ' '))
        tokens.push_back(intermediate);

    return tokens;
}

/**
 * Create a vector of unique words from the corpus
 * @return vector of unique words
 */

std::vector<std::string> BOW::unique_words()
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

/**
 * Calculate the Bag of words vector from the corpus.
 * @return Bag of words vector
 */
std::vector<std::vector<int>> BOW::fit()
{
    std::vector<std::vector<int>> bow_vector;

    for (auto &sentence : this->vec)
    {
        std::vector<int> bow_row;

        std::map<std::string, int> counts = this->make_count_map(sentence);
        std::vector<std::string> words = this->unique_words();

        for (auto &word : words)
        {
            if (counts.count(word))
                bow_row.push_back(counts[word]);
            else
                bow_row.push_back(0);
        }
        bow_vector.push_back(bow_row);
    }

    return bow_vector;
}

int main(int argc, char const *argv[])
{
    // std::vector<std::string> corpus = {
    //     "this is the first document mostly",
    //     "this document is the second document",
    //     "and this is the third one",
    //     "is this the first document here",
    // };

    std::ifstream file("C:/Users/abhi0/Desktop/ML-from-scratch/Cpp/NLP/feature_extraction/test.txt");

    std::string line;
    std::vector<std::string> corpus1;

    while (std::getline(file, line))
    {
        corpus1.push_back(line);
    }

    BOW bow(corpus1);

    auto bow_vector = bow.fit();

    bow.print_vector(bow_vector);

    return 0;
}