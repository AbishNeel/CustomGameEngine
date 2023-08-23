# Custom C++ Containers Library: SList, Vector, HashMap

This C++ library provides three custom container classes: `SList`, `Vector`, and `HashMap`, inspired by the standard library containers `std::forward_list`, `std::vector`, and `std::unordered_map`. These custom containers aim to provide similar functionality with some additional features and optimizations.

## Table of Contents

- [SList](#slist)
- [Vector](#vector)
- [HashMap](#hashmap)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## SList

`SList` is a singly linked list implementation that provides constant time insertion and deletion at the beginning of the list. It supports various operations like `push_front`, `pop_front`, `empty`, `size`, and more.

### Features

- Constant time insertion and deletion at the front.
- Memory-efficient due to singly linked structure.
- Iterators for traversing the list.
- ...

## Vector

`Vector` is a dynamic array implementation that provides amortized constant time insertion and deletion at the end of the array. It supports various operations like `push_back`, `pop_back`, `at`, `empty`, `size`, and more.

### Features

- Amortized constant time insertion and deletion at the end.
- Dynamically resizing array for automatic capacity management.
- Random access to elements using the `at` method or operator `[]`.
- Iterators for traversing the vector.
- ...

## HashMap

`HashMap` is a hash table implementation that provides fast average time complexity for insertion, deletion, and retrieval of key-value pairs. It supports operations like `insert`, `erase`, `find`, `empty`, `size`, and more.

### Features

- Fast average time complexity for insertion, deletion, and retrieval.
- Hashing for efficient key-value storage and retrieval.
- Dynamic resizing for automatic capacity management.
- Iterators for traversing the map's key-value pairs.
- ...

## Usage

1. Clone the repository:
git clone https://github.com/your-username/custom-containers.git


2. Include the desired container header in your C++ code:

```cpp
#include "SList.h"
#include "Vector.h"
#include "HashMap.h"
