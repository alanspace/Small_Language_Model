#include "LanguageModel.h"

LanguageModel::LanguageModel(int k) : k(k), stats(k) {}

void LanguageModel::train(const std::string &text) {
  if (text.length() < k)
    return;

  for (size_t i = 0; i <= text.length() - k; ++i) {
    std::string kgram = text.substr(i, k);
    if (i < text.length() - k) {
      char nextChar = text[i + k];
      stats.addKGramTransition(kgram, nextChar);
    }
  }
}

std::string LanguageModel::generateText(int length) {
  if (length <= 0)
    return "";

  std::string current = stats.getRandomKGram();
  std::string result = current;

  for (int i = 0; i < length - k; ++i) {
    if (!stats.hasKGram(current)) {
      current = stats.getRandomKGram();
    }
    char nextChar = stats.getNextChar(current);
    result += nextChar;
    current = current.substr(1) + nextChar;
  }

  return result;
}
