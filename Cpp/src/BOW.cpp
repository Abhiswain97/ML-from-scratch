#include "../include/BOW.h"

#include "../include/Utils.h"

std::vector<std::vector<double>> BOW::fit() {
  std::vector<std::vector<double>> bow_vector;

  for (auto& sentence : this->vec) {
    std::vector<double> bow_row;

    std::map<std::string, int> counts = utils::make_count_map(sentence);
    std::vector<std::string> words = utils::unique_words(this->vec);

    for (auto& word : words) {
      if (counts.count(word))
        bow_row.push_back((double)counts[word]);
      else
        bow_row.push_back(0.0);
    }
    bow_vector.push_back(bow_row);
  }

  return bow_vector;
}