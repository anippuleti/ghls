# ghls
Generic Hardware Logic Simulator

A minimal C++ project scaffold using CMake and Catch2 for unit tests.

Build (Linux):

```bash
mkdir -p build
cd build
cmake ..
cmake --build . -- -j
ctest --output-on-failure
```

Run the sample app:

```bash
./build/ghls_app
```
