# Few Pybind11 examples

Small examples for the Pybind11 wrapper library to expose C++ functions in Python.

The bindings library can be build using the normal git and CMake workflow:

```
git clone https://github.com/breyerml/pybind11_examples.git
cd pybind11_examples
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

In order to execute the Python examples, one has to add the build directory to the `PYTHONPATH` environment variable.
