#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "Course.h"

using namespace std;

namespace PA3 // Begin PA3 namespace
{
    class Course; // Forward declaration of Course class

    class Student // Student class declaration
    {
    public:
        // Constructor declaration
        Student();
        Student(string StdName, string StdID); // Constructor with parameters
        Student(const Student& other); // Copy constructor
        Student& operator=(const Student& other); // Assignment operator
        string getName() const; // Member function to retrieve student name
        string getID() const; // Member function to retrieve student ID
        void setName(string StdName); // Member function to set student name
        void setID(string StdID); // Member function to set student ID
        int getCourseSize() const; // Member function to get total courses
        void addCourse(string courseCode, string courseName); // Member function to add a course
        void deleteCourse(string courseCode, string courseName); // Member function to delete a course
        ~Student(); // Destructor
        Course** courses; // Pointer to array of Course pointers
    private:
        string name; // Student name
        string id;   // Student ID
        int courseSize; // Current number of courses
        int numOfCourses; // Maximum size of courses array
    };
}

#endif
