//Name: Trenton Matthews
//Project for CS300


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Define the Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Define the Node structure for the Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// BST Class
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        }
        else if (course.courseNumber < node->course.courseNumber) {
            addNode(node->left, course);
        }
        else {
            addNode(node->right, course);
        }
    }

    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;
            inOrderTraversal(node->right);
        }
    }

    Node* searchNode(Node* node, string courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }
        else if (courseNumber < node->course.courseNumber) {
            return searchNode(node->left, courseNumber);
        }
        else {
            return searchNode(node->right, courseNumber);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(Course course) {
        addNode(root, course);
    }

    void printInOrder() {
        inOrderTraversal(root);
    }

    Course* search(string courseNumber) {
        Node* foundNode = searchNode(root, courseNumber);
        return foundNode ? &foundNode->course : nullptr;
    }
};

// Function to load course data from a file
void loadCourseData(BinarySearchTree& bst) {
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;

    ifstream file(fileName);
    if (!file) {
        cout << "Error: Cannot open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Course course;
        size_t pos = 0;

        // Parse course number
        pos = line.find(',');
        course.courseNumber = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse course title
        pos = line.find(',');
        course.courseTitle = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse prerequisites
        while ((pos = line.find(',')) != string::npos) {
            course.prerequisites.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        course.prerequisites.push_back(line); // Add the last prerequisite

        bst.insert(course);
    }
    file.close();
    cout << "Course data loaded successfully!" << endl;
}

// Function to print a course's detailed information
void printCourseInfo(BinarySearchTree& bst) {
    string courseNumber;
    cout << "Enter course number: ";
    cin >> courseNumber;

    Course* course = bst.search(courseNumber);
    if (course) {
        cout << "Course Number: " << course->courseNumber << endl;
        cout << "Course Title: " << course->courseTitle << endl;
        cout << "Prerequisites: ";
        for (const string& prereq : course->prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}

// Main menu function
void displayMenu() {
    cout << "\nMenu Options:" << endl;
    cout << "1. Load Course Data" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "9. Exit" << endl;
}

int main() {
    BinarySearchTree bst;
    int choice;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadCourseData(bst);
            break;
        case 2:
            bst.printInOrder();
            break;
        case 3:
            printCourseInfo(bst);
            break;
        case 9:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}
