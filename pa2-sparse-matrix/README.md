# PA2 — Sparse Vector and Sparse Matrix

CSE241 Object-Oriented Programming — Assignment 2

The original problem statement is included as [`assignment.pdf`](./assignment.pdf).

## Overview

Implementation of `SparseVector` and `SparseMatrix` classes in C++ that store only non-zero elements while behaving like full vectors and matrices. The classes support arithmetic, assignment, negation, output streaming, dot product, transpose, and matrix multiplication through operator overloading.

## Design

### `SparseVector`

Internally stores non-zero elements as a `vector<vecdata>` where each `vecdata` struct holds an index and a value. Zero values are never stored — any operation producing a zero result drops that element.

| Member | Description |
|--------|-------------|
| `SparseVector()` | Default constructor |
| `SparseVector(int size)` | Constructor with size |
| `SparseVector(string filename)` | Reads from file (`index:value` format) |
| `operator+` | Element-wise addition |
| `operator-` (binary) | Element-wise subtraction |
| `operator-` (unary) | Negation of all elements |
| `operator=` | Assignment |
| `operator<<` | Output in `index:value` format |
| `dot(v1, v2)` | Dot product (returns `double`) |

### `SparseMatrix`

Built from rows of `SparseVector` objects, stored in a `vector<pair<int, SparseVector>>` — only non-zero rows are kept.

| Member | Description |
|--------|-------------|
| `SparseMatrix(string filename)` | Reads from file (row-major sparse format) |
| `operator+` / `operator-` | Matrix addition/subtraction |
| `operator-` (unary) | Negation |
| `operator=` | Assignment |
| `operator*` | Matrix multiplication |
| `transpose()` | Returns transposed matrix |
| `operator<<` | Output in sparse row format |

## File Format

**SparseVector** (`a1.txt`):
```
4:23.8 7:10.7 10:34 12:20
```

**SparseMatrix** (`m1.txt`):
```
3 3:24.6 4:5.5
4 1:1.15
8 5:6.4 8:34.1 9:13.1
```

## Build & Run

```bash
make        # compiles all .cpp files → main.out
./main.out  # runs operations and writes results to output.txt
make clean  # removes .o, .d, and main.out
```

The provided `main.cpp` demonstrates all operations: vector addition/subtraction, dot product, matrix addition/subtraction, negation, transpose, and matrix multiplication.
