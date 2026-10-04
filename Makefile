kkkkkCXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = scheduler
TEST_TARGET = tests/test_scheduler

SOURCES = \
	src/main.cpp \
	src/fcfs.cpp \
	src/sjf.cpp \
	src/priority.cpp \
	src/round_robin.cpp \
	src/comparison.cpp \
	src/performance.cpp

OBJECTS = $(SOURCES:.cpp=.o)

TEST_SOURCES = \
	tests/test_scheduler.cpp \
	src/fcfs.cpp \
	src/sjf.cpp \
	src/priority.cpp \
	src/round_robin.cpp \
	src/performance.cpp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all test clean run
