# PA5 — Generic Catalog System (STL, Exception Handling)

CSE241 Object-Oriented Programming — Assignment 5 (Double Weight)

The original problem statement is included as [`assignment.pdf`](./assignment.pdf). Sample data files are in [`data_samples/`](./data_samples/).

## Overview

A generic catalog reader and query engine in C++. The program reads a data file whose first line describes a flexible schema (field names, types, and cardinality), parses all entries according to that schema, then executes `search` and `sort` commands from a commands section in the same file. All output is written to `output.txt`. The system handles malformed data gracefully using C++ exception handling.

## Design

### `Field` struct

Holds a typed value using three `vector` members — `strArray`, `intArray`, `doubleArray` — and a `type` tag, so that a single `Field` can represent a `string:single`, `string:multi`, `integer:single`, `double:multi`, etc., without templates.

### `CatalogEntry`

An `unordered_map<string, Field>` mapping field names to their parsed values. This lets the same `Catalog` class handle any schema without knowing field names at compile time.

### `Catalog`

- `vector<CatalogEntry> entries` — all unique, valid entries.
- `vector<string> fieldNames` — preserves declaration order for output formatting.
- Parses the schema line, then reads entries one by one; throws `runtime_error` for missing fields and duplicate first-field values.
- Executes `search` (partial match across single or multi values) and `sort` (ascending by any field) commands; throws `runtime_error` for unrecognized field names or malformed command syntax.
- All exceptions are caught and logged to `output.txt` inline with the operation that caused them.

## Exception Handling

| Situation | Log entry |
|-----------|-----------|
| Entry has fewer fields than schema | `Exception: missing field` |
| First field of entry matches an existing entry | `Exception: duplicate entry` |
| Command references unknown field or has wrong syntax | `Exception: command is wrong` |

## Input Format

Both data and commands live in the same file, separated by a blank line and `commands:`:

```
field1:type:single|field2:type:multi|...
value1|value2_a:value2_b|...
...

commands:
search "value" in "field_name"
sort "field_name"
```

## Build & Run

```bash
make              # compiles → main.out
./main.out data_samples/data1.txt   # runs on a sample file → writes output.txt
make clean        # removes .o, .d, main.out
```

## Sample Data

Three sample files are included in [`data_samples/`](./data_samples/):

- **`data1.txt`** — movie catalog (title, director, year, genre, artist); exercises duplicate detection and missing field.
- **`data2.txt`** — book catalog (title, author, year, tag); exercises multi-value search and sort on multiple fields.
- **`data3.txt`** — generic schema (a–e with mixed types including `double:multi`); exercises malformed commands.
