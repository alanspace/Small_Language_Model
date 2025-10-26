# Small Language Model (SLM)

A C++ implementation of a simple k-gram based language model that can generate text based on input training data.

## Overview

This program implements a small language model that:
1. Reads a text file to learn k-gram frequencies and transition probabilities
2. Uses these statistics to generate new text that follows similar patterns

## Mathematical Model

The model works by:
1. Computing k-gram frequencies from input text
2. Calculating transition probabilities P(c|w) where:
   - w is a k-gram
   - c is the next character
   - P(c|w) = n(w,c)/n(w)
   - n(w,c) is the count of c following w
   - n(w) is the total count of w

## Building

To build the project, simply run:

```bash
make
```

This will create an executable named `slm` in the current directory.

## Usage

```bash
./slm <k> <input-file> <output-length>
```

Where:
- `k` is the length of k-grams to use (must be positive)
- `input-file` is the path to a text file to train on
- `output-length` is the number of characters to generate

Example:
```bash
./slm 2 moby_dick.txt 5
```

## Implementation Details

The project consists of two main classes:

1. `KGramStats`: Manages k-gram statistics and transition probabilities
2. `LanguageModel`: Handles text generation using the statistical model

The implementation uses C++17 features and the standard library's random number generation facilities for sampling from probability distributions.

## File Structure

```
.
├── README.md
├── Makefile
├── src/
│   ├── main.cpp
│   ├── LanguageModel.cpp
│   ├── LanguageModel.h
│   ├── KGramStats.cpp
│   └── KGramStats.h
```

## License

This project is open source and available under the MIT License.
