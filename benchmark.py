import time
import random
import sys
from collections import defaultdict

# Import the C++ module
try:
    import my_cpp_model
    print("Successfully imported C++ module 'my_cpp_model'")
except ImportError as e:
    print(f"Failed to import my_cpp_model: {e}")
    sys.exit(1)

# Pure Python Implementation for comparison
class PythonLanguageModel:
    def __init__(self, k):
        self.k = k
        self.transitions = defaultdict(lambda: defaultdict(int))
        self.kgrams = []
        self.kgram_freq = defaultdict(int)

    def train(self, text):
        # Optimized Python training loop
        k = self.k
        transitions = self.transitions
        kgram_freq = self.kgram_freq
        kgrams = self.kgrams
        
        for i in range(len(text) - k):
            kgram = text[i:i+k]
            next_char = text[i+k]
            transitions[kgram][next_char] += 1
            if kgram_freq[kgram] == 0:
                kgrams.append(kgram)
            kgram_freq[kgram] += 1

    def generate_text(self, length):
        if not self.kgrams:
            return ""
        
        # Weighted random choice for start kgram to match C++ implementation logic
        kgrams = list(self.kgram_freq.keys())
        weights = list(self.kgram_freq.values())
        if not kgrams:
             return ""
        current_kgram = random.choices(kgrams, weights=weights, k=1)[0]
        
        output = current_kgram
        output_list = [current_kgram] # Use list for faster appending
        
        k = self.k
        transitions = self.transitions
        
        for _ in range(length - k):
            if current_kgram not in transitions:
                break
                
            trans = transitions[current_kgram]
            choices = list(trans.keys())
            counts = list(trans.values())
            
            next_char = random.choices(choices, weights=counts, k=1)[0]
            output_list.append(next_char)
            # Efficiently update current_kgram
            current_kgram = (current_kgram + next_char)[1:]
            
        return "".join(output_list)

def run_benchmark():
    # Load data
    try:
        with open("sample.txt", "r", encoding="utf-8") as f:
            original_text = f.read()
            # Make it larger to notice the difference
            text = original_text * 2000  
    except FileNotFoundError:
        print("sample.txt not found. Using dummy text.")
        text = "To be or not to be that is the question " * 5000

    print(f"Training on text of size: {len(text)} chars")
    
    k = 5
    gen_len = 50000 
    
    # --- C++ Benchmark ---
    print("\n--- C++ Model ---")
    start = time.time()
    cpp_model = my_cpp_model.LanguageModel(k)
    cpp_model.train(text)
    train_time_cpp = time.time() - start
    print(f"Training time: {train_time_cpp:.6f}s")
    
    start = time.time()
    generated_cpp = cpp_model.generate_text(gen_len)
    gen_time_cpp = time.time() - start
    print(f"Generation time ({gen_len} chars): {gen_time_cpp:.6f}s")
    
    # --- Python Benchmark ---
    print("\n--- Python Model ---")
    start = time.time()
    py_model = PythonLanguageModel(k)
    py_model.train(text)
    train_time_py = time.time() - start
    print(f"Training time: {train_time_py:.6f}s")
    
    start = time.time()
    generated_py = py_model.generate_text(gen_len)
    gen_time_py = time.time() - start
    print(f"Generation time ({gen_len} chars): {gen_time_py:.6f}s")
    
    # --- Results ---
    print("\n--- Comparison ---")
    print(f"Training C++ vs Python Speedup: {train_time_py / train_time_cpp:.2f}x")
    print(f"Generation C++ vs Python Speedup: {gen_time_py / gen_time_cpp:.2f}x")

if __name__ == "__main__":
    run_benchmark()
