#include <iostream>
#include <string>
#include "Course.h"

using namespace std;

namespace PA3
{
    // Default constructor implementation
    Course::Course() {
        students = new Student*[10]; // Allocate memory for students array
        name = "Non"; // Set default name
        code = "Non"; // Set default code
        studentSize = 0; // Initialize student size to 0
        numOfStudents = 10; // Set maximum number of students, capacity
    }

    // Constructor with parameters implementation
    Course::Course(string courseName, string courseCode) {
        students = new Student*[10]; // Allocate memory for students array
        name = courseName; // Set name to provided value
        code = courseCode; // Set code to provided value
        studentSize = 0; // Initialize student size to 0
        numOfStudents = 10; // Set maximum number of students, capacity
    }

    // Copy constructor implementation
    Course::Course(const Course& other) {
        numOfStudents = other.numOfStudents; // Copy number of students
        studentSize = other.studentSize; // Copy student size
        students = new Student*[numOfStudents]; // Allocate memory for students array

        // Copy each student pointer
        for(int i=0; i<numOfStudents; i++)
            students[i] = other.students[i];
    }

    // Assignment operator implementation
    Course& Course::operator=(const Course& other) {
        if(this == &other) // Check for self-assignment
            return *this;
        else {
            numOfStudents = other.numOfStudents; // Copy number of students
            studentSize = other.studentSize; // Copy student size
            delete[] students; // Deallocate memory for existing students
            students = new Student*[numOfStudents]; // Allocate memory for students array

            // Copy each student pointer
            for(int i=0; i<numOfStudents; i++)
                students[i] = other.students[i];

            return *this; // Return reference to this object
        }
    }

    // Member function to retrieve course name
    string Course::getCourseName() const {
        return name;
    }

    // Member function to retrieve course code
    string Course::getCourseCode() const {
        return code;
    }

    // Member function to set course name
    void Course::setCourseName(string courseName) {
        name = courseName;
    }

    // Member function to set course code
    void Course::setCourseCode(string courseCode) {
        code = courseCode;
    }

    // Member function to get total students
    int Course::getStudentSize() const {
        return studentSize;
    }

    // Member function to add a student
    void Course::addStudent(string studentName, string studentID) {
        Student* temp = new Student(studentName, studentID); // Create new Student object
        if(studentSize >= numOfStudents) { // Check if students array needs resizing
            Student** temparr = new Student*[numOfStudents + 10]; // Create temporary array with increased size

            // Copy existing students to temporary array
            for(int i=0; i<numOfStudents; i++)
                temparr[i] = students[i];

            numOfStudents += 10; // Update maximum number of students
            delete[] students; // Deallocate memory for existing students
            students = temparr; // Point students to temporary array
        }
        students[studentSize] = temp; // Add new student to students array
        studentSize++; // Increment student size
    }

    // Member function to delete a student
    void Course::deleteStudent(string studentName, string studentID) {
        int location;

        // Find location of student to delete
        for(int i=0; i<studentSize; i++) {
            if((students[i]->getName() == studentName) && (students[i]->getID() == studentID)){
                location = i;
                break;
            }
        }

        // Shift students to remove deleted student
        for(int i=location; i<studentSize-1; i++)
            students[i] = students[i+1];

        studentSize--; // Decrement student size
    }

    // Destructor implementation
    Course::~Course() {
        // Deallocate memory for each student
        for(int i=0; i<numOfStudents; i++)
            delete [] students[i];
        
        delete [] students; // Deallocate memory for students array
    }

}
