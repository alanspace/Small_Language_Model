#ifndef KGRAMSTATS_H
#define KGRAMSTATS_H

#include <map>
#include <random>
#include <string>

class KGramStats {
public:
  KGramStats(int k);

  void addKGramTransition(const std::string &kgram, char nextChar);

  char getNextChar(const std::string &kgram);

  std::string getRandomKGram();

  bool hasKGram(const std::string &kgram) const;

private:
  std::map<std::string, int> kgramFreq;
  std::map<std::string, std::map<char, int>> transitions;
  std::random_device rd;
  std::mt19937 gen;
};

#endif
