CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++20 -Iinclude
LDFLAGS = -ltbb -pthread

SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/student_system

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: release

release: CXXFLAGS += -O3
release: $(TARGET)

debug: CXXFLAGS += -O0 -g -DDEBUG
debug: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all release debug clean
