# Makefile for PedestriansTragedy on macOS

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I./include

# Linker flags for macOS
LDFLAGS = -framework OpenGL -framework GLUT -framework OpenAL

# Directories
SRC_DIR = source
INC_DIR = include
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable name
TARGET = PedestriansTragedy

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Clean complete!"

# Run the game
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
