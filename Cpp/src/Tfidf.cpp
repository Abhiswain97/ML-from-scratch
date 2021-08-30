#include "../include/Tfidf.h"

#include "../include/Utils.h"

double Tfidf::compute_tf(std::string& sentence, std::string& word) {
  std::vector<std::string> tokens = utils::tokenize(sentence);
  auto counts = utils::make_count_map(sentence);

  return counts[word] / double(tokens.size());
}

std::map<std::string, double> Tfidf::compute_idf() {
  std::map<std::string, double> idf_dict;

  unsigned __int64 N = this->vec.size();

  auto unq_words = utils::unique_words(this->vec);

  for (auto& word : unq_words) {
    unsigned __int64 counter = 0;
    for (auto& sentence : this->vec) {
      auto tokens = utils::tokenize(sentence);
      std::for_each(tokens.begin(), tokens.end(),
                    [&](std::string token) -> void {
                      counter += (token.compare(word)) ? 1 : 0;
                    });
    }

    idf_dict[word] = std::abs(log((N + 1) / double(counter + 1)));
  }

  return idf_dict;
}

std::vector<std::vector<double>> Tfidf::fit() {
  std::vector<std::vector<double>> Tfidf_vector;

  auto idf_dict = this->compute_idf();

  auto unq_wrds = utils::unique_words(this->vec);

  for (auto& sentence : this->vec) {
    std::vector<double> tfidf_row;

    std::for_each(unq_wrds.begin(), unq_wrds.end(), [&](std::string word) {
      tfidf_row.push_back(this->compute_tf(sentence, word) * idf_dict[word]);
    });
    Tfidf_vector.push_back(tfidf_row);
  }

  return Tfidf_vector;
}
