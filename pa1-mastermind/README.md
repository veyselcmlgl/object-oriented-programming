# PA1 — Mastermind Game

CSE241 Object-Oriented Programming — Assignment 1

The original problem statement is included as [`assignment.pdf`](./assignment.pdf).

## Overview

A command-line implementation of the Mastermind number-guessing game in C++. The program holds a secret number and the user proposes guesses; after each guess the program reports how many digits are in the exact position (`Cexact`) and how many exist in the secret number but are misplaced (`Cmisplaced`). The game ends when the user guesses correctly or exhausts 100 attempts.

## Rules

- Valid digits: `{0,1,2,3,4,5,6,7,8,9,a,b,c,d,e}` (base-15 with letters).
- A valid number has up to 16 digits, no leading zero, and all digits are unique.
- `Cexact` = digits in the correct position.
- `Cmisplaced` = digits that exist in the secret but are out of place.

## Usage

```bash
make                        # compile
./mastermind -r <N>         # random secret number with N digits (1–15)
./mastermind -u <number>    # use the given number as the secret
make clean                  # remove binary
```

Example session:
```
./mastermind -r 6           # program picks a random 6-digit secret
12345a
3 1
13245a
5 0
130456
FOUND 3
```

## Error Codes

| Code | Meaning |
|------|---------|
| `E0` | Invalid program call (wrong/missing arguments) |
| `E1` | User input has wrong number of digits |
| `E2` | User input is not a valid number (invalid chars, non-unique digits, leading zero) |
| `FAILED` | User did not guess within 100 turns |

## Implementation Notes

- `random_generator()` builds a unique-digit number by sampling without replacement from the 15-character digit set.
- `isValidInput()` validates both the secret (when using `-u`) and every user guess.
- `checkArg()` validates the digit-count argument for `-r` mode (must be 1–15).
- A custom `myAtoi()` converts the digit-count string to integer without using standard `atoi`.
