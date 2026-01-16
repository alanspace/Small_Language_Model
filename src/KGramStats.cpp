#include "KGramStats.h"
#include <numeric>
#include <stdexcept>

KGramStats::KGramStats(int k) : gen(rd()) { (void)k; }

void KGramStats::addKGramTransition(const std::string &kgram, char nextChar) {
  kgramFreq[kgram]++;
  transitions[kgram][nextChar]++;
}

char KGramStats::getNextChar(const std::string &kgram) {
  if (!hasKGram(kgram)) {
    return ' ';
  }

  std::vector<std::pair<char, double>> probDist;
  double total = 0;

  for (const auto &pair : transitions[kgram]) {
    total += pair.second;
  }

  for (const auto &pair : transitions[kgram]) {
    probDist.emplace_back(pair.first, pair.second / total);
  }

  std::uniform_real_distribution<> dis(0.0, 1.0);
  double random = dis(gen);

  double cumProb = 0.0;
  for (const auto &pair : probDist) {
    cumProb += pair.second;
    if (random <= cumProb) {
      return pair.first;
    }
  }

  return probDist.back().first;
}

std::string KGramStats::getRandomKGram() {
  if (kgramFreq.empty()) {
    throw std::runtime_error("Model has not been trained (no k-grams found).");
  }

  double total = std::accumulate(
      kgramFreq.begin(), kgramFreq.end(), 0.0,
      [](double sum, const auto &pair) { return sum + pair.second; });

  std::uniform_real_distribution<> dis(0.0, total);
  double random = dis(gen);

  double cumSum = 0;
  for (const auto &pair : kgramFreq) {
    cumSum += pair.second;
    if (random <= cumSum) {
      return pair.first;
    }
  }

  return kgramFreq.begin()->first;
}

bool KGramStats::hasKGram(const std::string &kgram) const {
  return kgramFreq.find(kgram) != kgramFreq.end();
}
