# PA6 — Media Catalog with Observer Pattern

CSE241 Object-Oriented Programming — Assignment 6

A full written report is included as [`report.pdf`](./report.pdf), and a UML class diagram is included as [`uml.diagram.png`](./uml.diagram.png).

## Overview

A Java-based media catalog system that applies the **Observer design pattern**. A `Dataset` acts as the subject holding a collection of media entries (`Audio`, `Video`, `Image`, `Text`); `Player` and `Viewer` are concrete observers that receive notifications when entries are added or removed, and each maintains its own filtered view of the catalog.

## Design

### Class Hierarchy

```
Entry  (base)
├── Visual  (interface — has visual output)
│   ├── Image
│   └── Video
└── Non_visual
    ├── Playable  (interface — can be played)
    │   ├── Audio
    │   └── Video
    └── Non_playable
        ├── Image
        └── Text
```

### Observer Pattern

```
Dataset  (subject)
├── notifies → Player   (extends Observer)
└── notifies → Viewer   (extends Observer)
```

`Observer` is an abstract class defining:
- `addMessage(ArrayList<Entry>)` — called when a new entry is added to `Dataset`
- `removeMessage(ArrayList<Entry>)` — called when an entry is removed
- `show_list()` — displays the observer's current filtered list
- `next(String type)` / `previous(String type)` — navigate to next/previous entry of a given type

`Player` filters entries by `Playable` (Audio, Video); `Viewer` filters by `Visual` (Image, Video). Both receive the full updated list on every add/remove notification and rebuild their filtered view accordingly.

### `Dataset`

Holds the master `ArrayList<Entry>`, registers observers, and on every mutation (add/remove) calls `addMessage`/`removeMessage` on all registered observers.

## Build & Run

```bash
make        # compiles Test.java (and all dependencies) → runs Test
```

Or manually:
```bash
javac Test.java
java Test
```
