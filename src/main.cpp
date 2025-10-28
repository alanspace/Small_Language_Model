#include "LanguageModel.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <k> <input-file> <output-length>" << std::endl;
        return 1;
    }

    // Parse command line arguments
    int k = std::stoi(argv[1]);
    std::string filename = argv[2];
    int length = std::stoi(argv[3]);

    if (k < 1) {
        std::cerr << "Error: k must be positive" << std::endl;
        return 1;
    }

    if (length < 1) {
        std::cerr << "Error: output length must be positive" << std::endl;
        return 1;
    }

    // Create and train the model
    LanguageModel model(k);
    std::string text = readFile(filename);
    model.train(text);

    // Generate and output text
    std::string generated = model.generateText(length);
    std::cout << generated << std::endl;

    return 0;
}
