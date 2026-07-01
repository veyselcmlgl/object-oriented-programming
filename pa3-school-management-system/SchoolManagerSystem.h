#ifndef SCHOOLMANAGERSYSTEM_H
#define SCHOOLMANAGERSYSTEM_H

#include <iostream>
#include <string>
#include "Student.h"
#include "Course.h"

using namespace std;

namespace PA3
{
    class SchoolManagementSystem // SchoolManagementSystem class declaration
    {
    public:
        // Constructor declaration
        SchoolManagementSystem();
        SchoolManagementSystem(const SchoolManagementSystem& other); // Copy constructor
        SchoolManagementSystem& operator=(const SchoolManagementSystem& other); // Assignment operator
        void mainMenu(); // Member function to display main menu
        void addStudent(string studentName, string studentID); // Member function to add a student
        void addCourse(string courseCode, string courseName); // Member function to add a course
        void splitForStudent(string& line, string& studentName, string& studentID); // Member function to split input line for student data
        void splitForCourse(string& line, string& courseCode, string& courseName); // Member function to split input line for course data
    private:
        Student** allStudents; // Pointer to array of Student pointers
        Course** allCourses; // Pointer to array of Course pointers
        int numberOfStudent; // Total number of students
        int studentSize; // Maximum size of students array
        int numberOfCourse; // Total number of courses
        int courseSize; // Maximum size of courses array
    };
}

#endif
