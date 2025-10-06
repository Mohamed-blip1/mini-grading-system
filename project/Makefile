# Makefile
GXX = g++
CXXFLAGS = -Wall -Werror -std=c++20 -Iinclude

BUILD_DIR= build
TARGET = $(BUILD_DIR)/main

all: release

release: CXXFLAGS += -O3
release: $(TARGET)

# Debug
debug: CXXFLAGS += -O0 -g -DDEBUG
debug: $(TARGET)

# Link
$(TARGET) : $(BUILD_DIR)/main.o $(BUILD_DIR)/student.o
	@mkdir -p $(BUILD_DIR)
	$(GXX) $^ -o $@

# Compile
$(BUILD_DIR)/main.o : src/main.cpp
	@mkdir -p $(BUILD_DIR)
	$(GXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/student.o : src/student.cpp
	@mkdir -p $(BUILD_DIR)
	$(GXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean all release debug