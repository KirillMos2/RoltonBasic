CXX = g++
CXXFLAGS = -I include/ -std=c++11 -Wall
TARGET = roltonbasic
BUILD_DIR = build
SRC_DIR = .

SRCS = lexer.cpp parser.cpp compiler.cpp rolton-basic.cpp
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean $(TARGET)

.PHONY: clean rebuild
