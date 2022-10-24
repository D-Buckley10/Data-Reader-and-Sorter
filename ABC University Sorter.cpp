//============================================================================
// Name        : ABC University Course Sorter
// Author      : Douglas Buckley
// Date        : October 23, 2022
// Version     : 1.0
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

char choice = '0';

// Define structure course
struct Course {
    //declare variables
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

//Function to split string based on splits
vector<string> tokenize(string s, string split = ",") {

    vector<string> stringArray;
    int begin = 0;
    int end = s.find(split);

    while (end != -1) {
        stringArray.push_back(s.substr(begin, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(end) - begin));
        begin = end + split.size();
        end = s.find(split, begin);
    }

    stringArray.push_back(s.substr(begin, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(end) - begin));

    return stringArray;
}

// Function to load file and store the details into list of courses
vector<Course> InputData() {
    // use fstream to open .txt file
    fstream inputFile("Courses.txt");
    vector<Course> courses;
    string line;

    //while loop to iterate through data
    while (getline(inputFile, line)) {
        // course object to store course data
        Course course;
        // tokenize information to separate with commas
        vector<string> info = tokenize(line, ",");

        if (info.size() > 1) {
            // importing info to course struct
            course.courseNumber = info[0];
            course.name = info[1];

            // import prerequisites to course struct
            for (int i = 2; i < info.size(); i++) {
                course.prerequisites.push_back(info[i]);
            }

            // add course to list of courses
            courses.push_back(course);
        }
    }
    //close ifstream to save memory
    inputFile.close();

    cout << "Courses Loaded into Data Structure!" << endl;


    //return course list
    return courses;
}

// function to print a course
void printCourse(Course course) {
    //declare and initialize variables
    string courseNumber = course.courseNumber;
    string name = course.name;
    vector<string> prerequisites = course.prerequisites;
    //print course details
    cout << endl;
    cout << "Course Number: " << courseNumber << endl;
    cout << "Course Name: " << name << endl;
    cout << "Prerequisites: ";
    cout << endl;
    //check for prerequisites
    for (int i = 0; i < prerequisites.size(); i++) {
        cout << prerequisites[i] << " ";
    }
    cout << endl;
}

// function to print the list of all courses
void PrintFullCourseList(vector<Course> courses)
{
    int tempSize = courses.size();

    // sorting the courses according the course number
    for (int i = 0; i < tempSize - 1; i++) {
        for (int j = 0; j < tempSize - i - 1; j++) {
            if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                swap(courses[j + 1], courses[j]);
            }
        }
    }

    // printing the list of all courses
    cout << "Course List: " << endl;
    for (int i = 0; i < tempSize; i++) {
        cout << courses[i].courseNumber << ", " << courses[i].name << endl;
    }
}

// function to find a course with a course number
void searchCourse(vector<Course> courses) {
    int tempSize = courses.size();
    string courseNumber;
    int temp = 0;

    cout << "What course would you like more information on?";
    cin >> courseNumber;

    std::transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    //show course details if available
    cout << "Course Details: " << endl;
    for (int i = 0; i < tempSize; i++) {
        //fixme find solution for strcmp for case
        if (strcmp(courses[i].courseNumber.c_str(), courseNumber.c_str()) == 0) {
            temp = 1;
            printCourse(courses[i]);
            break;
        }
    }
    //course not found
    if (temp == 0) {
        cout << "Course not found" << endl;
    }
}

//function to show schedule following prereq requirements
void printCourseSchedule(vector<Course> courses) {
    int tempSize = courses.size();

    // sorting the courses according the course number
    for (int i = 0; i < tempSize - 1; i++) {
        for (int j = 0; j < tempSize - i - 1; j++) {
            if (courses[j].courseNumber > courses[j + 1].courseNumber) { // sort courses originally
                swap(courses[j + 1], courses[j]);
                if (courses[j].courseNumber[4] > courses[j + 1].courseNumber[4]) { // compare the fourth element of the strings, this moves math 201 between cs200 and cs300
                    swap(courses[j + 1], courses[j]);
                }
            }
        }
    }

    // printing the list of all courses
    cout << "Course List: " << endl;
    for (int i = 0; i < tempSize; i++) {
        cout << courses[i].courseNumber << ", " << courses[i].name << endl;
    }
}


int main(int argc, char** argv) {
    //vector
    vector<Course> courses;

    //display menu
    cout << "Welcome to the Course Planner." << endl; // Display welcome message

    do {
        cout << endl;
        cout << "=======================" << endl;
        cout << "=======================" << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course Information." << endl;
        cout << "4. Print Course Schedule." << endl;
        cout << "9. Exit Program." << endl;
        cout << "=======================" << endl;
        cout << "=======================" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        //call function based on input
        switch (choice) {
        case '1':
            courses = InputData();
            break;
        case '2':
            PrintFullCourseList(courses);
            break;
        case '3':
            searchCourse(courses);
            break;
        case '4':
            printCourseSchedule(courses);
            break;
        case '9':
            cout << "Thank you for using the course planner!\nGoodbye!" << endl;
            break;
        default:
            cout << "\n" << choice << " is not a valid option!" << endl;
            cout << "Please make a selection from the provided menu." << endl;
        }
    } while (choice != '9');
    return 0;
}

