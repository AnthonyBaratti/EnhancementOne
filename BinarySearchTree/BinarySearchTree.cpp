//=================================================
//  Name: Project II ACBU Advising Program
//  Author: Anthony Baratti
//  Version: 1.0
//  Date: 6/17/2024
//  Description: File parser to Binary Search Tree Structure
//=================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

//Structure declarations to hold course information
struct Course {
	string courseId;
	string courseName;
	string preReq1 = "";
	string preReq2 = "";
};

//Structure declaration for tree node
struct Node {
	Course course;
	Node* left;
	Node* right;

	//default constructor
	Node() {
		//child leaves start empty
		left = nullptr;
		right = nullptr;
	}

	//course node constructor
	Node(Course aCourse) : Node() {
		course = aCourse;
	}
};


class BinarySearchTree {
private:
	Node* root;

	void addNode(Node* node, Course course);
	void inOrder(Node* node);

public:

	BinarySearchTree();
	~BinarySearchTree();
	void InOrder();
	void DisplayNode(Node* node);
	void InsertCourse(Course course);
	Course Search(string courseId);
};

//default constructor
BinarySearchTree::BinarySearchTree() {
	//Set to empty
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {

}

/*
 * InsertCourse() function is called from Parser::Parser() to take a
 * Node constructed from an input file read
 *
 * @param Course course (node structure)
 */
void BinarySearchTree::InsertCourse(Course course) {

	if (root == nullptr) { //if tree is empty
		root = new Node(course); //starts tree
	}
	else { //tree not empty
		this->addNode(root, course);
	}
}

/*
 * Recursive addNode() function that will build the BST
 * using nodes and the courseId as the ordering factor
 *
 * @param Node node, Course course
 */
void BinarySearchTree::addNode(Node* node, Course course) {

	if (node->course.courseId.compare(course.courseId) > 0) { //course ID is less than current Node
		if (node->left == nullptr) { //Left leaf empty
			node->left = new Node(course); //Assign to empty left
		}
		else { //Left leaf not empty
			this->addNode(node->left, course); //Recurse down the left leaf
		}
	}
	else { //Course ID is greater than current Node
		if (node->right == nullptr) { //Right leaf empty
			node->right = new Node(course); //Assign to empty right
		}
		else { //Right leaf not empty
			this->addNode(node->right, course); //Recurse down right leaf
		}
	}
}

/*
 * InOrder() function designed to recursively travel down a tree
 * Called once from main print option
 * calls inOrder() function, passing the current root as node
 */

void BinarySearchTree::InOrder() {
	this->inOrder(root);
}

/*
 * Recursive inOrder() function that traveses down
 * the left side of the tree, printing from left to right
 * With DisplayNode() function call, and moving up
 * a node with each traversal
 * Called once from main as option 2
 *
 * @param Node node
 */

void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr) { //If node not empty
		inOrder(node->left); //check left
		DisplayNode(node); //print current
		inOrder(node->right); //check right
	}
}


/*
 * DisplayNode() function called from inOrder() function
 * Purpose is to display courseId and courseName
 *
 * @param Node node
 */
void BinarySearchTree::DisplayNode(Node* node) {
	cout << node->course.courseId << ", " << node->course.courseName << endl;
	return;
}

/*
 * Search() function designed to take user input of courseId
 * called from menu option 3. Compares tree nodes for < or > value
 * And returns found node, or returns empty node if not found
 *
 * @param string courseId
 * @return Course course
*/
Course BinarySearchTree::Search(string courseId) {
	Node* currNode = root;

	while (currNode != nullptr) { //Loop until end of tree

		//If match found, return match
		if (currNode->course.courseId.compare(courseId) == 0) {
			return currNode->course;
		}
		if (currNode->course.courseId.compare(courseId) > 0) { //search ID smaller than currnode ID
			currNode = currNode->left; //traverse left
		}
		else { //search ID larger than currnode ID
			currNode = currNode->right;//traverse right
		}
	}
	//If not found, return empty course.
	Course course;
	return course;
}

class Parser {
public:
	Parser();
	Parser(string fileName, BinarySearchTree* bst);
	~Parser();


};

Parser::Parser() {

}

Parser::~Parser() {

}
/*
* ParseLine used to parse a passed getline() from file reader
*
* @param newLine //from file
* @return newLineTokens //newLine broken into vector
*
* REFERENCE:
* https://stackoverflow.com/questions/5757721/use-getline-and-while-loop-to-split-a-string
*
*/
vector<string> ParseLine(string newLine) {
	char delim = ','; //Sets delimiter to check for
	istringstream split(newLine); //allows split function to seperate newLine
	vector<string> newLineTokens; //Vector stores each split element

	//For loop that splits elements off after delim, attaches them to variable "each"
	//and pushes them to back of vector
	for (string each; getline(split, each, delim); newLineTokens.push_back(each));

	return newLineTokens; //returns created vector
}


/*
 * Parser() function that will read csv file line by line
 * and make function call to ParseLine() function, passing the line from
 * the file as argument to be split into a vector. The vector will be returned
 * and parted out into the Node STRUCT and then inserted into the BST
 *
 *@param String fileName, BinarySearchTree bst
 *
*/
Parser::Parser(string fileName, BinarySearchTree* bst) {
	int count = 0;
	string line;                 //used to store string from getline
	vector<string> lineToTokens; //used to parse a line into tokens
	ifstream inputFile;          //file to be read
	Course aCourse;              //declare structure object


	inputFile.open(fileName);

	if (inputFile.is_open()) { //only do while file is open

		while (getline(inputFile, line)) { //reads each line until EOF, better solution than !.eof()
			//REFERENCE: https://stackoverflow.com/questions/26071275/c-while-loop-and-getline-issue

			//Sends the line to ParseLine() and returns a vector of separated strings to lineToTokens
			lineToTokens = ParseLine(line);

			if (lineToTokens.size() < 2) { //Error format for vector too small (< 2)
				cout << "Wrong format" << endl;
			}
			else {
				aCourse.courseId = lineToTokens.at(0); //attaches first element to courseId
				aCourse.courseName = lineToTokens.at(1); //attaches second elemnt to courseName
				if (lineToTokens.size() > 2) { //if 3 elements exist in line
					aCourse.preReq1 = lineToTokens.at(2); //attach 3rd element to preReq1
					if (lineToTokens.size() > 3) { //if 4 elements exist in line
						aCourse.preReq2 = lineToTokens.at(3); // attach 4th element to preReq2
					}
					else {
						aCourse.preReq2 = ""; //Sets preReq2 to empty if doesn't exist
					}
				}
				else {
					//sets both preReq to empty if neither exist
					aCourse.preReq1 = "";
					aCourse.preReq2 = "";
				}
			}
			bst->InsertCourse(aCourse); //insert each node into BST
			++count; //Increment count for display menu message
		}
		cout << endl << count << " courses added to course list." << endl << endl; //display menu message
	}
	else { //Output file not open error message
		cout << fileName + " is not open." << endl;
	}
	inputFile.close();
}


int main(int argc, char* argv[]) {
	string fileName;
	string searchId; //Variable for user search string
	int choice; //Variable for user menu option

	switch (argc) { //Command prompt arg
	case 2:
		fileName = argv[1]; //Gets file as first argument
		break;
	default:
		string fileName = "CS 300 ABCU_Advising_Program_Input.csv"; //hard coded file name as default

	}

	BinarySearchTree* bst = new BinarySearchTree(); //Construct BST
	Course course;


	choice = 0;

	//Quick welcome message
	cout << "Welcome to ABC University Course Finder Program" << endl;
	cout << "Please choose an option from the menu below." << endl << endl;

	while (choice != 9) { //Until 9 is chosen

		//display menu
		cout << "Menu: " << endl;
		cout << "  1: Load Courses File." << endl;
		cout << "  2: Print Course List." << endl;
		cout << "  3: Find & Print Course." << endl;
		cout << "  9: Exit Program" << endl << endl;
		cout << "Enter Choice: ";
		cin >> choice; //captures users menu choice

		switch (choice) {
		case 1: { //"Load Courses File"
			Parser file = Parser(fileName, bst); //Reads file and loads tree
			break;
		}
		case 2: //"Print Course List."
			cout << endl << "------ Current Course List ------" << endl << endl; //Visual list header
			bst->InOrder(); //Prints BST in alphabetical order
			cout << endl;
			break;

		case 3: { //"Find & Print Course."
			cout << "Enter course to find: ";
			cin >> searchId; //Captures user course to search BST for

			//For loop that converts all alpha to uppercase for match
			for (int i = 0; i < searchId.length(); ++i) {
				searchId[i] = toupper(searchId[i]);
			}

			//captures a match if found.
			course = bst->Search(searchId);


			if (!course.courseId.empty()) { //ID found
				cout << endl << course.courseId << ", " << course.courseName << endl; //Displays ID and Name
				if (!course.preReq1.empty()) { //If preReq1 exists
					cout << "Prerequisites: " << course.preReq1; //Prints prerequisites
					if (!course.preReq2.empty()) { //If preReq2 exists
						cout << ", " << course.preReq2; //Adds to print prerequisites
					}
					cout << endl;
				}
				else { //If no prerequisites in course info
					cout << "Prerequisites: None" << endl;
				}
				cout << endl;
			}
			else { //ID not found
				cout << endl << searchId << " not found." << endl << endl;
			}
			break;
		}
		case 9: //"Exit Program."
			cout << "Thank you for using ABC University Course Finder Program." << endl;
			break;

		default: //Handles input validation as default
			cout << endl << "Please enter a valid menu option." << endl << endl;
			if (!(cin >> choice)) {
				//clears input line to prevent infinite loop from character entry (up to 10K characters)
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}

	}
	return 0;
	//END main
}