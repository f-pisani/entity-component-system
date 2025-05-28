# Entity Component System (ECS) Framework

A C++11 Entity Component System framework implementation created as a hobby project. This framework provides a flexible and efficient architecture commonly used in game development and simulation systems.

> **Note**: This is an old hobby project that was created for learning purposes. It may require updates to work with modern compilers and development environments.

## What is ECS?

Entity Component System (ECS) is a software architectural pattern that follows the composition over inheritance principle. It consists of:

- **Entities**: Unique identifiers that represent game objects
- **Components**: Pure data containers attached to entities
- **Systems**: Logic processors that operate on entities with specific component combinations

## Project Structure

```
EntityComponentSystem/
├── src/                    # Core ECS framework implementation
│   ├── Entity.*           # Entity management
│   ├── Component.*        # Component base classes
│   ├── System.*           # System base classes
│   └── World.*            # Main ECS world container
├── benchmarks/            # Performance benchmarking suite
│   ├── BenchmarkECS_Entity.*    # Entity operation benchmarks
│   ├── BenchmarkECS_Component.* # Component operation benchmarks
│   └── BenchmarkECS_System.*    # System operation benchmarks
├── ecs.hpp                # Main include file
└── main.cpp               # Benchmark runner application
```

## Requirements

- C++11 compatible compiler (g++, clang++, or similar)
- GNU Make
- Standard C++ library

## Building

The project uses a standard Makefile for building:

```bash
# Build release version (optimized)
make

# Build debug version (with debug symbols)
make debug

# Build both debug and release
make all

# Clean build artifacts
make clean
```

Build artifacts will be placed in the `build/` directory:
- `build/debug/` - Debug build with symbols
- `build/release/` - Optimized release build

## Running

The project includes a benchmark suite to test the ECS framework performance:

```bash
# Run release version
make run

# Run debug version
make run-debug

# Or run directly
./build/release/ECS
```

The benchmark application provides an interactive menu to run performance tests on:
1. Entity operations (creation, deletion, retrieval)
2. Component operations (adding, removing, accessing)
3. System operations (processing entities)

Results are saved to `benchmark.csv` for analysis.

## Usage Example

While this project is primarily a framework with benchmarks, here's a conceptual example of how the ECS system works:

```cpp
// Create a world
ECS::World world;

// Create entities
ECS::Entity* player = world.CreateEntity();
ECS::Entity* enemy = world.CreateEntity();

// Add components (user-defined component types)
player->AddComponent<PositionComponent>(0.0f, 0.0f);
player->AddComponent<VelocityComponent>(1.0f, 0.0f);

// Create systems to process entities
auto* movementSystem = world.CreateSystem<MovementSystem>();

// Process all systems
world.Process();
```
