kCXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = scheduler

SOURCES = \
	src/main.cpp \
	src/fcfs.cpp \
	src/sjf.cpp \
	src/priority.cpp \
	src/round_robin.cpp \
	src/comparison.cpp \
	src/performance.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
