
# ghls - Generic Hardware Logic Simulator

## Introduction

The Generic Hardware Logic Simulator (ghls) is a C++ project designed for hardware simulation with a focus on precise time management.

### Key Features
- **Google C++ Style**: Follows Google C++ coding guidelines
- **Comprehensive Testing**: Extensive unit tests using Catch2 framework

## Project Structure

```
ghls/
├── infra/
│   └── engine/
│       ├── src/
│       │   ├── simTime.hpp       # SimTime class declaration and SimTimeUnit enum
│       │   ├── simTime.cpp       # SimTime implementation
│       │   └── main.cpp          # Main application entry point
│       └── tests/
│           └── test_simTime.cpp  # Comprehensive unit tests
├── build/                        # Build directory (generated)
├── CMakeLists.txt               # Root CMake configuration
└── README.md                    # This file
```

- All source code is located in `infra/engine/src`
- All unit tests are located in `infra/engine/tests`
- Catch2 testing framework is automatically downloaded via CMake FetchContent

## Prerequisites

- **CMake**: Version 3.14 or higher
- **C++ Compiler**: Supporting C++17 standard (GCC 7+, Clang 5+, or MSVC 2017+)
- **Build Tools**: make or ninja
- **Operating System**: Linux, macOS, or Windows

## Build Instructions

### Linux / macOS

1. **Clone the repository** (if not already done):
   ```bash
   git clone <repository-url>
   cd ghls
   ```

2. **Create build directory and configure**:
   ```bash
   mkdir -p build
   cd build
   cmake ..
   ```

3. **Build the project**:
   ```bash
   cmake --build . -- -j
   ```
   
   The `-j` flag enables parallel compilation for faster builds.

### Build Outputs

After a successful build, you'll find:
- **Main executable**: `build/infra/engine/simTime_main`
- **Test executable**: `build/infra/engine/test_simTime`
- **Library**: `build/infra/engine/libengine.a`

## Running the Project

### Run Main Application

From the build directory:

```bash
./infra/engine/simTime_main
```

Or with an absolute path from project root:

```bash
./build/infra/engine/simTime_main
```

## Running Unit Tests

### Option 1: Run All Tests with CTest

CTest provides a convenient way to run all registered tests:

```bash
cd build
ctest --output-on-failure
```

For more verbose output:

```bash
ctest --verbose
```

### Option 2: Run SimTime Tests Directly

Run the test executable directly for detailed Catch2 output:

```bash
cd build
./infra/engine/test_simTime
```

### Option 3: Run Specific Test Cases

Catch2 allows running specific test cases by name:

```bash
./infra/engine/test_simTime "SimTime operator+ exhaustive tests"
./infra/engine/test_simTime "SimTime operator* exhaustive tests"
```

List all available test cases:

```bash
./infra/engine/test_simTime --list-tests
```

### Test Coverage

The project includes comprehensive unit tests covering:
- **Default constructor and initialization**
- **Unit conversions** (s, ms, us, ns, ps)
- **String formatting** (conv2str function)
- **Addition operator** (`operator+`) with 117 test assertions
  - Same unit additions
  - Mixed unit additions
  - Zero value handling
  - Fractional values
  - Large values
  - Chained operations
  - All unit combinations
- **Multiplication operator** (`operator*`) with 52 test assertions
  - Different units × scalars
  - Zero value multiplications
  - Large scalar multiplications
  - Fractional time values
  - Chained operations
  - Mixed operations with addition

**Total: 169+ assertions** across all test cases

## Development

### Code Style

The project follows **Google C++ Style Guide** with automatic formatting via clang-format.

### Naming Conventions

- **Function arguments**: Prefixed with `f_` (e.g., `f_time`, `f_unit`)
- **Local variables**: Prefixed with `l_` (e.g., `l_val`, `l_unit`)
- **Class members**: Prefixed with `c_` (e.g., `c_simTime`, `c_simUnits`)

### Adding New Tests

To add new tests, edit `infra/engine/tests/test_simTime.cpp` and use Catch2 macros:

```cpp
TEST_CASE("Description of test") {
  SECTION("Subsection description") {
    // Your test code
    REQUIRE(condition);
  }
}
```

Rebuild and run tests to verify your changes.

## Clean Build

To clean and rebuild from scratch:

```bash
cd build
rm -rf *
cmake ..
cmake --build . -- -j
```

## Troubleshooting

### Build Fails with CMake Errors

- Ensure CMake version is 3.14 or higher: `cmake --version`
- Delete the build directory and try again

### Tests Fail

- Ensure the build completed successfully
- Check for any precision issues in floating-point comparisons
- Run tests with verbose output: `./infra/engine/test_simTime -v`

### Missing Dependencies

- The project automatically downloads Catch2 via FetchContent
- Ensure you have internet connectivity during the first build

## License

[Specify your license here]

## Contributors

[List contributors here]
