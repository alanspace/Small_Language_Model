CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = slm
SRCS = src/main.cpp src/LanguageModel.cpp src/KGramStats.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)