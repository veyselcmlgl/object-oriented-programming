# PA4 — Robot Battle Simulation (Inheritance & Polymorphism)

CSE241 Object-Oriented Programming — Assignment 4

The original problem statement is included as [`assignment.pdf`](./assignment.pdf).

## Overview

A grid-based robot battle simulation in C++ that demonstrates **inheritance, virtual functions, and late binding (runtime polymorphism)**. Five types of robots are placed randomly on a 10×10 grid and fight until only one survives. Each robot type overrides `getDamage()` to compute its own combat rules.

## Inheritance Hierarchy

```
Robot  (abstract base — getDamage() = 0, getType() = 0)
├── humanic  (adds 10% chance of +50 tactical nuke)
│   ├── optimusprime  (adds 15% chance of double damage)
│   └── robocop
├── roomba   (attacks twice per turn)
├── bulldozer
└── kamikaze (damage = hitpoints; dies after attacking)
```

`getDamage()` uses **chained virtual dispatch**: calling `getDamage()` on an `optimusprime` invokes `Robot::getDamage()` (base damage) → `humanic::getDamage()` (nuke chance) → `optimusprime::getDamage()` (double chance), accumulating damage at each level.

## Robot Stats

| Type | Strength | Hitpoints | Special Rule |
|------|----------|-----------|-------------|
| optimusprime | 100 | 100 | 15% chance to double damage; humanic nuke |
| robocop | 30 | 40 | humanic 10% nuke |
| roomba | 3 | 10 | attacks twice per turn |
| bulldozer | 50 | 200 | none |
| kamikaze | 10 | 10 | damage = own hitpoints; dies after attack |

## Simulation

- 5 robots of each type (25 total) placed randomly on a 10×10 `Grid`.
- Each simulation step: visit every cell; if a robot is present, it tries to move (up/down/left/right).
  - If the target cell is occupied → fight loop until one robot dies.
  - If empty → robot moves there.
- Each robot has a `moved` flag reset every step to ensure one action per robot per round.
- Simulation ends when only one robot remains.

## Build & Run

```bash
make        # compiles all .cpp files → main.out
./main.out  # runs the simulation
make clean  # removes .o, .d, and main.out
```

Requires GCC with C++11 support (`-std=c++11`).
