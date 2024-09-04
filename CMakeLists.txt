cmake_minimum_required(VERSION 3.22)
project(pybdin11_examples)

# fetch Pybind11
include(FetchContent)
FetchContent_Declare(pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v2.13.5
        GIT_SHALLOW TRUE
        QUIET
        )
FetchContent_MakeAvailable(pybind11)

# explicitly set all source files
set(SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/classes/example.cpp
        ${CMAKE_CURRENT_LIST_DIR}/enums/example.cpp
        ${CMAKE_CURRENT_LIST_DIR}/exceptions/example.cpp
        ${CMAKE_CURRENT_LIST_DIR}/functions/example.cpp
        ${CMAKE_CURRENT_LIST_DIR}/numpy_performance/example.cpp
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        )

# create Python module
pybind11_add_module(showcase ${SOURCES})

# set necessary target properties
target_compile_features(showcase PRIVATE cxx_std_17)
target_include_directories(showcase PRIVATE ${pybind11_SOURCE_DIR}/include)

# find required python libraries
find_package(Python REQUIRED)
target_include_directories(showcase PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(showcase PRIVATE ${GPU_SAMPLER_LIBRARY_NAME})
