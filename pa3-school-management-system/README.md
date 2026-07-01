# PA3 — School Management System with Dynamic Memory

CSE241 Object-Oriented Programming — Assignment 3

The original problem statement is included as [`assignment.pdf`](./assignment.pdf).

## Overview

An interactive console-based school management system implemented in C++ under the `PA3` namespace. Students and courses are managed through a nested menu system. All objects are allocated dynamically with `new`/`delete` — STL vectors, variable-length arrays, and global arrays are explicitly forbidden by the assignment.

## Design

### Classes (all under `namespace PA3`)

**`Student`**
- Members: `name` (string), `ID` (string), and a **dynamic array of `Course*`** pointers representing enrolled courses.
- Constructors: default; takes name + ID.
- Destructor: releases dynamic course-reference array.
- get/set for all members; methods to add/drop course references.

**`Course`**
- Members: `name` (string), `code` (string), and a **dynamic array of `Student*`** pointers representing enrolled students.
- Same pattern as `Student` — constructors, destructor, get/set, add/drop student references.

**`SchoolManagementSystem`**
- Members: `Student** allStudents` and `Course** allCourses` — dynamically grown pointer arrays (no STL).
- Owns all `Student` and `Course` objects; responsible for `new` and `delete` of every instance.
- Menu loop: main menu → student submenu / course submenu; selection state tracks the currently selected student or course.

### Memory Model

```
SchoolManagementSystem
├── Student** allStudents  →  [ Student*, Student*, ... ]
│                                   ↓
│                               Student { name, id, Course** courses → [...] }
└── Course** allCourses   →  [ Course*, Course*, ... ]
                                    ↓
                                Course { code, name, Student** students → [...] }
```

Cross-references (student → course and course → student) are pointer references, not copies — a student and the course it is enrolled in both point to the same single object.

## Menu Structure

```
Main_menu
  0 exit
  1 student
      0 up
      1 add_student
      2 select_student
          0 up
          1 delete_student
          3 add_selected_student_to_a_course
          4 drop_selected_student_from_a_course
  2 course
      0 up
      1 add_course
      2 select_course
          0 up
          1 delete_course
          2 list_students_registered_to_the_selected_course
  3 list_all_students
  4 list_all_courses
```

## Build & Run

```bash
make        # compiles all .cpp files → main.out
./main.out  # starts the interactive menu
make clean  # removes .o, .d, and main.out
```
