#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

namespace PA3
{
    // Default constructor implementation
    Student::Student() {
        courses = new Course*[10]; // Allocate memory for courses array
        name = "Non"; // Set default name
        id = "Non"; // Set default ID
        courseSize = 0; // Initialize course size to 0
        numOfCourses = 10; // Set maximum number of courses, capacity
    }

    // Constructor with parameters implementation
    Student::Student(string StdName, string StdID) {
        courses = new Course*[10]; // Allocate memory for courses array
        name = StdName; // Set name to provided value
        id = StdID; // Set ID to provided value
        courseSize = 0; // Initialize course size to 0
        numOfCourses = 10; // Set maximum number of courses, capacity
    }

    // Copy constructor implementation
    Student::Student(const Student& other) {
        numOfCourses = other.numOfCourses; // Copy number of courses
        courseSize = other.courseSize; // Copy course size
        courses = new Course*[numOfCourses]; // Allocate memory for courses array

        // Copy each course pointer
        for(int i=0; i<numOfCourses; i++)
            courses[i] = other.courses[i];
    }

    // Assignment operator implementation
    Student& Student::operator=(const Student& other) {
        if(this == &other) // Check for self-assignment
            return *this;
        else {
            numOfCourses = other.numOfCourses; // Copy number of courses
            courseSize = other.courseSize; // Copy course size
            delete[] courses; // Deallocate memory for existing courses
            courses = new Course*[numOfCourses]; // Allocate memory for courses array

            // Copy each course pointer
            for(int i=0; i<numOfCourses; i++)
                courses[i] = other.courses[i];

            return *this; // Return reference to this object
        }
    }

    // Member function to retrieve student name
    string Student::getName() const {
        return name;
    }

    // Member function to retrieve student ID
    string Student::getID() const {
        return id;
    }

    // Member function to set student name
    void Student::setName(string StdName) {
        name = StdName;
    }

    // Member function to set student ID
    void Student::setID(string StdID) {
        id = StdID;
    }

    // Member function to get total courses
    int Student::getCourseSize() const {
        return courseSize;
    }

    // Member function to add a course
    void Student::addCourse(string courseCode, string courseName) {
        Course* temp = new Course(courseName, courseCode); // Create new Course object
        if(courseSize >= numOfCourses) { // Check if courses array needs resizing
            Course** temparr = new Course*[numOfCourses + 10]; // Create temporary array with increased size

            // Copy existing courses to temporary array
            for(int i=0; i<numOfCourses; i++)
                temparr[i] = courses[i];

            numOfCourses += 10; // Update maximum number of courses
            delete[] courses; // Deallocate memory for existing courses
            courses = temparr; // Point courses to temporary array
        }
        courses[courseSize] = temp; // Add new course to courses array
        courseSize++; // Increment course size
    }

    // Member function to delete a course
    void Student::deleteCourse(string courseCode, string courseName) {
        int location;

        // Find location of course to delete
        for(int i=0; i<courseSize; i++) {
            if((courses[i]->getCourseCode() == courseCode) && (courses[i]->getCourseName() == courseName)) {
                location = i;
                break;
            }
        }

        // Shift courses to remove deleted course
        for(int i=location; i<courseSize-1; i++)
            courses[i] = courses[i+1];

        courseSize--; // Decrement course size
    }

    // Destructor implementation
    Student::~Student() {
        // Deallocate memory for each course
        for(int i=0; i<numOfCourses; i++)
            delete[] courses[i];
        
        delete[] courses; // Deallocate memory for courses array
    }

}
