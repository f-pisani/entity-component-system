# Entity Component System Framework Makefile
# Portable C++11 build configuration

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -fexceptions -Isrc -Ibenchmarks
LDFLAGS = 

# Build directories
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release

# Source files
SRC_FILES = $(wildcard src/*.cpp)
BENCHMARK_FILES = $(wildcard benchmarks/*.cpp)
MAIN_FILE = main.cpp

# Object files
SRC_OBJS_DEBUG = $(patsubst src/%.cpp,$(DEBUG_DIR)/src/%.o,$(SRC_FILES))
SRC_OBJS_RELEASE = $(patsubst src/%.cpp,$(RELEASE_DIR)/src/%.o,$(SRC_FILES))

BENCHMARK_OBJS_DEBUG = $(patsubst benchmarks/%.cpp,$(DEBUG_DIR)/benchmarks/%.o,$(BENCHMARK_FILES))
BENCHMARK_OBJS_RELEASE = $(patsubst benchmarks/%.cpp,$(RELEASE_DIR)/benchmarks/%.o,$(BENCHMARK_FILES))

MAIN_OBJ_DEBUG = $(DEBUG_DIR)/main.o
MAIN_OBJ_RELEASE = $(RELEASE_DIR)/main.o

# Targets
DEBUG_TARGET = $(DEBUG_DIR)/ECS
RELEASE_TARGET = $(RELEASE_DIR)/ECS

# Default target
.DEFAULT_GOAL := release

# Phony targets
.PHONY: all debug release clean run run-debug directories

# Build targets
all: debug release

debug: CXXFLAGS += -g -O0 -DDEBUG
debug: directories $(DEBUG_TARGET)

release: CXXFLAGS += -O3 -DNDEBUG
release: directories $(RELEASE_TARGET)

# Create build directories
directories:
	@mkdir -p $(DEBUG_DIR)/src $(DEBUG_DIR)/benchmarks
	@mkdir -p $(RELEASE_DIR)/src $(RELEASE_DIR)/benchmarks

# Link debug executable
$(DEBUG_TARGET): $(SRC_OBJS_DEBUG) $(BENCHMARK_OBJS_DEBUG) $(MAIN_OBJ_DEBUG)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Debug build complete: $@"

# Link release executable
$(RELEASE_TARGET): $(SRC_OBJS_RELEASE) $(BENCHMARK_OBJS_RELEASE) $(MAIN_OBJ_RELEASE)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Release build complete: $@"

# Compile source files (debug)
$(DEBUG_DIR)/src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DEBUG_DIR)/benchmarks/%.o: benchmarks/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_OBJ_DEBUG): $(MAIN_FILE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile source files (release)
$(RELEASE_DIR)/src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(RELEASE_DIR)/benchmarks/%.o: benchmarks/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_OBJ_RELEASE): $(MAIN_FILE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run targets
run: release
	./$(RELEASE_TARGET)

run-debug: debug
	./$(DEBUG_TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	@echo "Build artifacts cleaned"

# Help target
help:
	@echo "Entity Component System Framework - Build Targets:"
	@echo "  make              - Build release version (default)"
	@echo "  make debug        - Build debug version with symbols"
	@echo "  make release      - Build optimized release version"
	@echo "  make all          - Build both debug and release"
	@echo "  make run          - Build and run release version"
	@echo "  make run-debug    - Build and run debug version"
	@echo "  make clean        - Remove all build artifacts"
	@echo "  make help         - Show this help message"