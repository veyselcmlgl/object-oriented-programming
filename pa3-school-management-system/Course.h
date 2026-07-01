#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

namespace PA3
{
    class Student; // Forward declaration of Student class

    class Course // Course class declaration
    {
    public:
        // Constructor declarations
        Course(); // Default constructor
        Course(string courseName, string courseCode); // Constructor with parameters
        Course(const Course& other); // Copy constructor
        Course& operator=(const Course& other); // Assignment operator
        string getCourseName() const; // Member function to retrieve course name
        string getCourseCode() const; // Member function to retrieve course code
        void setCourseName(string courseName); // Member function to set course name
        void setCourseCode(string courseCode); // Member function to set course code
        int getStudentSize() const; // Member function to get total students
        void addStudent(string StdName, string StdID); // Member function to add a student
        void deleteStudent(string StdName, string StdID); // Member function to delete a student
        ~Course(); // Destructor
        Student** students; // Pointer to array of Student pointers
    private:
        string name; // Course name
        string code; // Course code
        int studentSize; // Current number of students
        int numOfStudents; // Maximum size of students array
    };
}

#endif
