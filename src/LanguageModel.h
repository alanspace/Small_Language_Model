#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include "KGramStats.h"
#include <string>

class LanguageModel {
public:
    LanguageModel(int k);

    void train(const std::string& text);
    
    std::string generateText(int length);

private:
    int k;
    KGramStats stats;
};

#endif