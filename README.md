# K-Gram Language Model: C++17 Implementation

A high-performance implementation of k-gram language models in modern C++17, demonstrating efficient probabilistic text generation through transition probability matrices.

**Author:** Shek Lun Leung  
**Institution:** Stockholm University  
**Course:** Programming Techniques II (DA2005)

## 📚 Research Paper

This implementation is accompanied by a comprehensive research paper that provides:
- Rigorous mathematical formalization with formal complexity proofs
- Comprehensive algorithmic analysis 
- Experimental validation across multiple corpora
- Literature review connecting classical and modern approaches
- Research-level exposition suitable for academic publication

📄 **[Read the full paper](paper/paper.pdf)** (14 pages)

The paper demonstrates the transition from a course programming assignment to research-quality work, showcasing algorithmic design, systems programming, and probabilistic modeling expertise.

---

## 🎯 Overview

This program implements a statistical language model that:
1. **Learns** k-gram frequencies and transition probabilities from text corpora
2. **Generates** new text that follows similar statistical patterns
3. **Demonstrates** efficient C++17 systems programming with modern STL usage

### Key Features

- ✅ **Modern C++17** - RAII, move semantics, STL algorithms
- ✅ **Efficient Sampling** - Inverse transform sampling with O(n) complexity
- ✅ **Nested Hash Maps** - O(1) expected-time probability lookups
- ✅ **Zero Raw Pointers** - Full STL memory management
- ✅ **High-Quality RNG** - Mersenne Twister (std::mt19937)

---

## 🧮 Mathematical Model

### K-Gram Probability

The model computes conditional probabilities using maximum likelihood estimation:

```
P(c | w) = N(w, c) / N(w)
```

Where:
- `w` is a k-gram (substring of length k)
- `c` is the next character
- `N(w, c)` is the count of character c following k-gram w
- `N(w)` is the total count of k-gram w

### Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Training  | O(n·k)         | O(n·k)          |
| Generation| O(m·k)         | O(1)            |

Where `n` = corpus size, `k` = k-gram length, `m` = output length

See the [research paper](paper/paper.pdf) for formal proofs.

---

## 🚀 Quick Start

### Prerequisites

- C++17 compatible compiler (g++ 7+, clang++ 5+)
- GNU Make

### Building

```bash
make
```

This creates an executable named `slm` in the current directory.

### Usage

```bash
./slm <k> <input-file> <output-length>
```

**Arguments:**
- `k` - Length of k-grams (must be positive integer)
- `input-file` - Path to training text file
- `output-length` - Number of characters to generate

### Examples

**Generate 500 characters with 5-grams from Shakespeare:**
```bash
./slm 5 sample.txt 500
```

**Short output with 2-grams:**
```bash
./slm 2 space_poem.txt 200
```

**High-order model with 10-grams:**
```bash
./slm 10 sample.txt 1000
```

---

## 📁 Project Structure

```
.
├── README.md                # This file
├── Makefile                 # Build configuration
├── src/                     # Source code
│   ├── main.cpp            # Entry point and CLI
│   ├── KGramStats.h        # K-gram statistics interface
│   ├── KGramStats.cpp      # Probability computation & sampling
│   ├── LanguageModel.h     # Language model interface
│   └── LanguageModel.cpp   # Training & text generation
├── paper/                   # Research paper
│   ├── paper.pdf           # Compiled PDF (14 pages)
│   ├── paper.tex           # LaTeX source
│   └── PAPER_README.md     # Paper documentation
├── sample.txt               # Sample training data
├── space_poem.txt           # Example corpus
└── .gitignore              # Git ignore rules
```

---

## 🏗️ Implementation Details

### Class Architecture

```
LanguageModel
├── int k                    # K-gram size
└── KGramStats stats         # Statistical model

KGramStats
├── int k                                      # K-gram size
├── map<string, int> kgramFreq                # K-gram frequencies
├── map<string, map<char, int>> transitions   # Transition counts
└── mt19937 gen                               # Random number generator
```

### Core Algorithms

#### Training (KGramStats::addKGramTransition)
- Slides a window of size `k` over input text
- Records each k-gram and its successor character
- Updates frequency and transition maps
- **Time:** O(n·k), **Space:** O(V·k) where V = distinct k-grams

#### Sampling (KGramStats::getNextChar)
- Normalizes transition counts to probabilities
- Uses inverse transform sampling on discrete CDF
- Returns sampled character from P(· | w)
- **Time:** O(|Σ_w|) where Σ_w = chars following k-gram w

#### Generation (LanguageModel::generateText)
- Samples initial k-gram weighted by frequency
- Iteratively samples next character given current k-gram
- Updates k-gram via sliding window (shift + append)
- **Time:** O(m·k), **Space:** O(k)

---

## 📊 Performance Characteristics

| K-gram Size | Memory Usage | Perplexity | Best Use Case |
|-------------|--------------|------------|---------------|
| k = 1       | Low          | High       | Simple patterns |
| k = 3       | Moderate     | Medium     | Balanced quality |
| k = 5       | Moderate     | Low        | **Recommended** |
| k = 7       | High         | Very Low   | Large corpora only |
| k = 10      | Very High    | Lowest     | Overfitting risk |

*Note: Higher k-values produce more coherent text but require larger training data to avoid overfitting.*

---

## 🔬 Research & Academic Use

This project demonstrates several competencies valuable for computational research:

### Technical Skills
- **Algorithm Design** - Efficient probabilistic sampling algorithms
- **Complexity Analysis** - Rigorous theoretical bounds with formal proofs
- **Systems Programming** - Memory-efficient data structures, optimal STL usage
- **Software Engineering** - Clean architecture, encapsulation, maintainability

### Applications
- **High-Performance Computing (HPC)** - Simulation kernels
- **Probabilistic Programming** - Bayesian inference engines
- **Monte Carlo Methods** - Stochastic sampling
- **Text Analysis** - Stylometry, authorship attribution

### Academic Context

This work originated from Programming Techniques II (DA2005) coursework and was independently extended to research depth with:
- Formal mathematical framework
- Comprehensive experimental validation
- Literature review and related work analysis
- Publication-quality exposition

For full details, see the [research paper](paper/paper.pdf).

---

## 🛠️ Development

### Build Targets

```bash
make           # Build the slm executable
make clean     # Remove compiled files
make rebuild   # Clean and build
```

### Compiler Flags

- `-std=c++17` - Enable C++17 features
- `-Wall -Wextra` - Enable comprehensive warnings
- `-O3` - Optimization level 3 (for production)

### Code Style

- Modern C++ idioms (RAII, move semantics)
- No raw pointers or manual memory management
- STL containers and algorithms preferred
- Const-correctness enforced

---

## 📖 Example Output

**Input (k=5, sample.txt):**
```
To be or not to be: that is the question...
```

**Generated:**
```
To be or not to be: that is the question: Whether 'tis nobler in the mind
to suffer The slings and arrows of outrageous fortune, Or to take arms
against a sea of troubles, And by opposing end them? To die: to sleep...
```

The model captures syntactic patterns, punctuation usage, and stylistic elements from the training corpus.

---

## 📚 References & Related Work

### Classical Language Models
- Shannon, C.E. (1948) - "A Mathematical Theory of Communication"
- Brown et al. (1992) - "Class-Based N-gram Models of Natural Language"
- Goodman (2001) - "A Bit of Progress in Language Modeling"

### Implementation Studies  
- **SRILM** - Industry-standard toolkit (Stolcke, 2002)
- **KenLM** - Optimized for speed and memory (Heafield, 2011)

### Modern Approaches
- Grave et al. (2016) - Improving neural models with n-gram caching
- Neural language models (LSTMs, Transformers)

For complete bibliography, see the [research paper](paper/paper.pdf).

---

## 🤝 Contributing

This is primarily an academic/portfolio project. For suggestions or issues:
- Open an issue describing the problem or enhancement
- For major changes, please discuss first

---

## 📄 License

This project is open source and available under the MIT License.

```
MIT License

Copyright (c) 2026 Shek Lun Leung

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 📧 Contact

**Shek Lun Leung**  
Stockholm University  
Email: sheklunleung.qai@proton.me

For academic inquiries or collaboration opportunities, feel free to reach out.

---

## 🎓 Acknowledgments

This work originated from foundational coursework in Programming Techniques II (DA2005). The transition from course assignment to research-quality implementation demonstrates the ability to identify interesting problems within structured contexts and pursue them to research depth independently.

Special thanks to the course instructors for providing the framework that motivated this deeper investigation into statistical language modeling and systems-level optimization.

---

**⭐ If you find this project useful for learning or research, please consider starring the repository!**
