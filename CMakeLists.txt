cmake_minimum_required(VERSION 3.4...3.18)
project(my_cpp_model)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# Find pybind11
# If pybind11 is not found, try to find it using python
find_package(pybind11 CONFIG)
if(NOT pybind11_FOUND)
    execute_process(
        COMMAND python -m pybind11 --cmakedir
        OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    if(EXISTS "${PYBIND11_CMAKE_DIR}")
        list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CMAKE_DIR}")
        find_package(pybind11 CONFIG REQUIRED)
    else()
        message(FATAL_ERROR "pybind11 not found. Please install it via pip: pip install pybind11")
    endif()
endif()

# Add the module
pybind11_add_module(my_cpp_model
    src/bindings.cpp
    src/LanguageModel.cpp
    src/KGramStats.cpp
)

# Include directories
target_include_directories(my_cpp_model PRIVATE src)
