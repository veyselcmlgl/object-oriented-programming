#include <iostream>
#include <string>
#include "SchoolManagerSystem.h"

using namespace std;

namespace PA3 // Begin PA3 namespace
{
    // Default constructor implementation
    SchoolManagementSystem::SchoolManagementSystem() {
        numberOfStudent = 0; // Initialize number of students to 0
        numberOfCourse = 0; // Initialize number of courses to 0
        allStudents = new Student*[10]; // Allocate memory for students array
        allCourses = new Course*[10]; // Allocate memory for courses array
        studentSize = 10; // Set maximum size of students array
        courseSize = 10; // Set maximum size of courses array
        mainMenu(); // Display main menu
    }

    // Copy constructor implementation
    SchoolManagementSystem::SchoolManagementSystem(const SchoolManagementSystem& other) {
        numberOfCourse = other.numberOfCourse; // Copy number of courses
        numberOfStudent = other.numberOfStudent; // Copy number of students
        studentSize = other.studentSize; // Copy maximum size of students array
        courseSize = other.courseSize; // Copy maximum size of courses array
        allStudents = new Student*[studentSize]; // Allocate memory for students array
        allCourses = new Course*[courseSize]; // Allocate memory for courses array
        
        // Copy each student pointer
        for(int i=0; i<studentSize; i++)
            allStudents[i] = other.allStudents[i];
        
        // Copy each course pointer
        for(int i=0; i<courseSize; i++)
            allCourses[i] = other.allCourses[i];
    }

    // Assignment operator implementation
    SchoolManagementSystem& SchoolManagementSystem::operator =(const SchoolManagementSystem& other) {
        if(this == &other) // Check for self-assignment
            return *this;
        else{
            numberOfCourse = other.numberOfCourse; // Copy number of courses
            numberOfStudent = other.numberOfStudent; // Copy number of students
            studentSize = other.studentSize; // Copy maximum size of students array
            courseSize = other.courseSize; // Copy maximum size of courses array
            delete[] allStudents; // Deallocate memory for existing students array
            delete[] allCourses; // Deallocate memory for existing courses array
            allStudents = new Student*[studentSize]; // Allocate memory for students array
            allCourses = new Course*[courseSize]; // Allocate memory for courses array

            // Copy each student pointer
            for(int i=0; i<studentSize; i++)
                allStudents[i] = other.allStudents[i];

            // Copy each course pointer
            for(int i=0; i<courseSize; i++)
                allCourses[i] = other.allCourses[i];

            return *this; // Return reference to this object
        }
    }

    // Member function to split input line for student data
    void SchoolManagementSystem::splitForStudent(string& line, string& studentName, string& studentID) {
        studentName.clear(); // Clear student name string
        studentID.clear(); // Clear student ID string
        int count = 0;

        // Count the number of spaces in the input line
        for(int i=0; i<line.size(); i++) {
            if(line[i] == ' ')
                count++;
        }

        int i=0, k=0;
        // Extract student name until the first space
        while(i < count) {
            if(line[k] == ' ')
                i++;
            studentName.push_back(line[k]);
            k++;
        }
        studentName.pop_back(); // Remove the last space

        // Extract student ID from the remaining part of the input line
        i = 0;
        while(line[k] != '\0'){
            studentID.push_back(line[k]);
            i++;
            k++;
        }
    }

    // Member function to split input line for course data
    void SchoolManagementSystem::splitForCourse(string& line, string& courseCode, string& courseName) {
        courseCode.clear(); // Clear course code string
        courseName.clear(); // Clear course name string

        int k=0;
        // Extract course code until the first space
        while(line[k] != ' '){
            courseCode.push_back(line[k]);
            k++;
        }

        k++;
        // Extract course name from the remaining part of the input line
        while(line[k] != '\0'){
            courseName.push_back(line[k]);
            k++;
        }
    }

    void SchoolManagementSystem::mainMenu() {
        int option; // Menu option chosen by the user
        string studentName, studentID, courseName, courseCode, line; // Variables for student and course information

        // Main menu loop
        while(1){
            // Display main menu options
            cout << "Main_menu\n0 exit\n1 student\n2 course\n3 list_all_students\n4 list_all_courses\n>> ";
            cin >> option;

            // Exit if option is 0
            if(option == 0)
                break;
            // Operations related to students
            else if(option == 1){
                // Student submenu loop
                while(1){
                    // Display student submenu options
                    cout << "0 up\n1 add_student\n2 select_student\n>> ";
                    cin >> option;
                    // Exit student submenu if option is 0
                    if(option == 0)
                        break;
                    // Add a new student
                    else if(option == 1){
                        cout << ">> ";
                        getchar();
                        getline(cin, line);
                        splitForStudent(line, studentName, studentID);
                        addStudent(studentName, studentID);
                    }
                    // Select a student
                    else if(option == 2){
                        int flag = 0, index;
                        cout << ">> ";
                        getchar();
                        getline(cin, line);
                        splitForStudent(line, studentName, studentID);
                        // Search for the selected student
                        for(int i=0; i<numberOfStudent; i++){
                            if((allStudents[i]->getName() == studentName) && (allStudents[i]->getID() == studentID)){
                                index = i;
                                flag = 1;
                                break;
                            }
                        }
                        // If selected student found, proceed with student operations
                        if(flag == 1){
                            while(1){
                                // Display student operations menu
                                cout << "0 up\n1 delete_student\n3 add_selected_student_to_a_course\n4 drop_selected_student_from_a_course\n>> ";
                                cin >> option;
                                if(option == 0)
                                    break;
                                // Delete selected student
                                else if(option == 1){
                                    for(int i=index; i<numberOfStudent-1; i++)
                                        allStudents[i] = allStudents[i+1];
                                    numberOfStudent--;
                                    for(int i=0; i<numberOfCourse; i++)
                                    allCourses[i]->deleteStudent(studentName, studentID);
                                    break;
                                }
                                // Add selected student to a course
                                else if(option == 3){
                                    while(1){
                                        int flag, count = 1, size = 10;
                                        string* codes = new string[10];
                                        string* names = new string[10];
                                        cout << "0 up";
                                        // Display available courses not registered by the student
                                        for(int i=0; i<numberOfCourse; i++){
                                            flag = 0;
                                            for(int j=0; j<allStudents[index]->getCourseSize(); j++){
                                                if((allCourses[i]->getCourseCode() == allStudents[index]->courses[j]->getCourseCode()) 
                                                        && (allCourses[i]->getCourseName() == allStudents[index]->courses[j]->getCourseName())){
                                                    flag = 1;
                                                }
                                            }
                                            if(flag == 0){
                                                if(count-1 >= size){
                                                    string* temp1 = new string[size+10];
                                                    string* temp2 = new string[size+10];
                                                    for(int k=0; k<size; k++){
                                                        temp1[k] = codes[k];
                                                        temp2[k] = names[k];
                                                    }
                                                    size += 10;
                                                    delete [] codes;
                                                    delete [] names;
                                                    codes = temp1;
                                                    names = temp2;
                                                }
                                                codes[count-1] = allCourses[i]->getCourseCode();
                                                names[count-1] = allCourses[i]->getCourseName();

                                                cout << "\n" << count << " " << allCourses[i]->getCourseCode() << " " << allCourses[i]->getCourseName();
                                                count++;
                                            }
                                        }
                                        cout << "\n>> ";
                                        cin >> option;
                                        if(option == 0)
                                            break;
                                        // Add selected student to the selected course
                                        else if((option > 0) && (option <= count)){
                                            allStudents[index]->addCourse(codes[option-1], names[option-1]);
                                            for(int i=0; i<numberOfCourse; i++){
                                                if((allCourses[i]->getCourseCode() == codes[option-1]) && (allCourses[i]->getCourseName() == names[option-1])){
                                                    allCourses[i]->addStudent(studentName, studentID);
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                                // Drop selected student from a course
                                else if(option == 4){
                                    while(1){
                                        int flag, count = 1, size = 10;
                                        string* codes = new string[10];
                                        string* names = new string[10];
                                        cout << "0 up";
                                        // Display courses registered by the student
                                        for(int i=0; i<numberOfCourse; i++){
                                            flag = 0;
                                            for(int j=0; j<allStudents[index]->getCourseSize(); j++){
                                                if((allCourses[i]->getCourseCode() == allStudents[index]->courses[j]->getCourseCode())
                                                        && (allCourses[i]->getCourseName() == allStudents[index]->courses[j]->getCourseName())){
                                                    flag = 1;
                                                }
                                            }
                                            if(flag == 1){
                                                if(count-1 >= size){
                                                    string* temp1 = new string[size+10];
                                                    string* temp2 = new string[size+10];
                                                    for(int k=0; k<size; k++){
                                                        temp1[k] = codes[k];
                                                        temp2[k] = names[k];
                                                    }
                                                    size += 10;
                                                    delete [] codes;
                                                    delete [] names;
                                                    codes = temp1;
                                                    names = temp2;
                                                }
                                                codes[count-1] = allCourses[i]->getCourseCode();
                                                names[count-1] = allCourses[i]->getCourseName();

                                                cout << "\n" << count << " " << allCourses[i]->getCourseCode() << " " << allCourses[i]->getCourseName();
                                                count++;
                                            }
                                        }
                                        cout << "\n>> ";
                                        cin >> option;
                                        if(option == 0)
                                            break;
                                        else if((option > 0) && (option <= count)){
                                            allStudents[index]->deleteCourse(codes[option-1], names[option-1]);
                                            for(int i=0; i<numberOfCourse; i++){
                                                if((allCourses[i]->getCourseCode() == codes[option-1]) && (allCourses[i]->getCourseName() == names[option-1])){
                                                    allCourses[i]->deleteStudent(studentName, studentID);
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // Operations related to courses
            else if(option == 2){
                // Course submenu loop
                while(1){
                    // Display course submenu options
                    cout << "0 up\n1 add_course\n2 select_course\n>> ";
                    cin >> option;
                    // Exit course submenu if option is 0
                    if(option == 0)
                        break;
                    // Add a new course
                    else if(option == 1){
                        cout << ">> ";
                        getchar();
                        getline(cin, line);
                        splitForCourse(line, courseCode, courseName);
                        addCourse(courseCode, courseName);
                    }
                    // Select a course
                    else if(option == 2){
                        int flag = 0, index;
                        cout << ">> ";
                        getchar();
                        getline(cin, line);
                        splitForCourse(line, courseCode, courseName);
                        // Search for the selected course
                        for(int i=0; i<numberOfCourse; i++){
                            if((allCourses[i]->getCourseCode() == courseCode) && (allCourses[i]->getCourseName() == courseName)){
                                index = i;
                                flag = 1;
                                break;
                            }
                        }
                        // If selected course found, proceed with course operations
                        if(flag == 1){
                            while(1){
                                // Display course operations menu
                                cout << "0 up\n1 delete_course\n2 list_students_registered_to_the_selected_course\n>> ";
                                cin >> option;
                                if(option == 0)
                                    break;
                                // Delete selected course
                                else if(option == 1){
                                    for(int i=index; i<numberOfCourse-1; i++)
                                        allCourses[i] = allCourses[i+1];
                                    numberOfCourse--;
                                    for(int i=0; i<numberOfStudent; i++)
                                        allStudents[i]->deleteCourse(courseCode, courseName);
                                    break;
                                }
                                // List students registered to the selected course
                                else if(option == 2){
                                    for(int i=0; i<allCourses[index]->getStudentSize(); i++)
                                        cout << i+1  << " " << allCourses[index]->students[i]->getName() << " " << allCourses[index]->students[i]->getID() << "\n";
                                }
                            }
                        }
                    }
                }
            }
            // List all students
            else if(option == 3){
                for(int i=0; i<numberOfStudent; i++)
                    cout << i+1 << " " << allStudents[i]->getName() << " " << allStudents[i]->getID() << "\n";
            }
            // List all courses
            else if(option == 4){
                for(int i=0; i<numberOfCourse; i++)
                    cout << i+1 << " " << allCourses[i]->getCourseCode() << " " << allCourses[i]->getCourseName() << "\n";
            }
        }
    }

    void SchoolManagementSystem::addStudent(string studentName, string studentID) {
        int flag = 0; // Flag to indicate if student already exists
        // Check if the student already exists
        for(int i=0; i<numberOfStudent; i++) {
            if((allStudents[i]->getName() == studentName) && (allStudents[i]->getID() == studentID)) {
                flag = 1; // Student exists
                break;
            }
        }
        // If student does not exist, add them
        if(flag == 0) {
            Student* temp = new Student(studentName, studentID); // Create new Student object
            if(numberOfStudent >= studentSize) { // Check if students array needs resizing
                Student** temparr = new Student*[studentSize + 10]; // Create temporary array with increased size
                // Copy existing students to temporary array
                for(int i=0; i<studentSize; i++)
                    temparr[i] = allStudents[i];
                studentSize += 10; // Update maximum size of students array
                delete[] allStudents; // Deallocate memory for existing students array
                allStudents = temparr; // Point students to temporary array
            }
            allStudents[numberOfStudent] = temp; // Add new student to students array
            numberOfStudent++; // Increment number of students
        }
    }

    void SchoolManagementSystem::addCourse(string courseCode, string courseName) {
        int flag = 0; // Flag to indicate if course already exists
        // Check if the course already exists
        for(int i=0; i<numberOfCourse; i++) {
            if((allCourses[i]->getCourseCode() == courseCode) && (allCourses[i]->getCourseName() == courseName)) {
                flag = 1; // Course exists
                break;
            }
        }
        // If course does not exist, add it
        if(flag == 0) {
            Course* temp = new Course(courseName, courseCode); // Create new Course object
            if(numberOfCourse >= courseSize) { // Check if courses array needs resizing
                Course** temparr = new Course*[courseSize + 10]; // Create temporary array with increased size
                // Copy existing courses to temporary array
                for(int i=0; i<courseSize; i++)
                    temparr[i] = allCourses[i];
                courseSize += 10; // Update maximum size of courses array
                delete [] allCourses; // Deallocate memory for existing courses array
                allCourses = temparr; // Point courses to temporary array
            }
            allCourses[numberOfCourse] = temp; // Add new course to courses array
            numberOfCourse++; // Increment number of courses
        }
    }
}