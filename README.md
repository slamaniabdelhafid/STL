# Circular List - STL Style Container

## Overview

This repository contains a C++ STL-style implementation of a circular list container. The circular list is a cyclic data structure where the last element points back to the first, creating a continuous loop without a traditional beginning or end.

## Features

- **STL-compliant implementation** following standard container conventions
- **Full iterator system** including:
  - Forward iterators
  - Reverse iterators
  - Const iterators
- **Support for standard concepts**:
  - Container
  - SequenceContainer
  - ReversibleContainer
- **Comprehensive error handling** with meaningful exceptions
- **Standard operator support** including:
  - Comparison operators (==, !=, , =)
  - Assignment operators
  - Stream insertion/extraction
- **Clean, modern C++ code** following best practices
- **Extensive test suite** covering all functionality
- **Continuous Integration (CI)** setup for quality assurance

## Repository Structure


STL/
└── Circular-list/
    ├── include/        # Header files
    ├── src/           # Implementation files
    ├── tests/         # Test cases
    ├── examples/      # Usage examples
    ├── CMakeLists.txt # Build configuration
    └── .github/       # CI workflows


## Requirements

- C++17 or later
- CMake 3.10+
- A C++ compiler with good standard library support (GCC, Clang, MSVC)

## Installation

git clone https://github.com/slamaniabdelhafid/STL.git --branch Circular-list
cd STL/Circular-list
mkdir build && cd build
cmake 
make

## Basic Usage

#include "circular_list.hpp"

int main() {
     Create a circular list
    stl::circular_list clist = {1, 2, 3, 4, 5};
    
  ### Iterate through the list
    for (auto it = clist.begin(); it != clist.end(); ++it) {
        std::cout << *it << " ";
    }
    
  ### Range-based for loop
    for (const auto& elem : clist) {
        std::cout << elem << " ";
    }
    
  ###  Add elements
    clist.push_back(6);
    clist.push_front(0);
    
  ###  Remove elements
    clist.pop_back();
    clist.pop_front();
    
    return 0;
    }
## Testing

To run the test suite:

cd build
ctest --output-on-failure

## Contributing

Contributions are welcome! Please follow these guidelines:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request with a clear description

## License

This project is licensed under the [MIT License](LICENSE).

## CI Status

[![CI](https://github.com/slamaniabdelhafid/STL/actions/workflows/ci.yml/badge.svg?branch=Circular-list)](https://github.com/slamaniabdelhafid/STL/actions/workflows/ci.yml)

## Documentation

For detailed documentation, see the header files in the `include/` directory or generate documentation using Doxygen.
