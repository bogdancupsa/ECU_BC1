CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pthread 
LDFLAGS := 
BUILD_DIR := build
SRC_DIR := src/scheduler


SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

EXECUTABLE := $(BUILD_DIR)/ECU_BC1

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
