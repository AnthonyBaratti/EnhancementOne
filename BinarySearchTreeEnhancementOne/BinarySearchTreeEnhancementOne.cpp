//=================================================
//  Name: CS-499 Capstone Project Artifact 1
//  Author: Anthony Baratti
//  Version: 1.0
//  Date: 7/20/2025
//  Description: Enhancement to previous CS-300 DSA
//  Binary Search Tree Algorithm. Adds user functionality
//  To add custom courses and delete courses from tree.
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
	bool courseDependencyCheck(Node* node, string& courseId); //Enhancement for dependency check
	Node* deleteNode(Node* node, string& courseId); //Enhancement to remove node with balancing

public:

	BinarySearchTree();
	~BinarySearchTree();
	void InOrder();
	void DisplayNode(Node* node);
	void InsertCourse(Course course);
	Course Search(string courseId);
	bool DeleteCourseWithDependencyCheck(string courseId); //Enhancement called from main to delete course.

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

/*
 *  courseDependencyCheck()
 *  This function serves as a dependency check. We don't want to delete lower level
 *  courses if they are required for higher level courses (a prerequisite to a higher course)
 *  so we must check to ensure that the course TO BE deleted is not a prerequisite for
 *  an existing course.
 *  **NOTE: This is part of the deleteCourse function, called from menu option 5.
 *          It has O(n) time complexity as it must check every node to see if
 *          there is a dependency for the course to be deleted.
 *  @param Node*, string courseId
 *  @return bool
 */
bool BinarySearchTree::courseDependencyCheck(Node* node, string& courseId) {
	if (node == nullptr) {
		return false;
	}

	//Check prerequisites of current node
	if ((node->course.preReq1 == courseId) || (node->course.preReq2 == courseId)) {
		return true;
	}

	//Recursively check tree for dependencies, traversing from left to right.
	return courseDependencyCheck(node->left, courseId) || courseDependencyCheck(node->right, courseId);
}

/*
 *  deleteNode()
 *  This function is designed to remove the node then will use a balancing algorithm
 *  to rebalance the AVL tree once the node is removed. To find the node to delete,
 *  the function will be recursively called passing the last node checked as the current
 *  node to check, traversing according to the courseId down the tree using comparisons.
 *  This function is called from DeleteNodeWithDependencyCheck() to ensure that it has
 *  no dependencies (it is not a prerequisite for another course).
 *  @params Node* node, string& courseId
 *  return node
 */
Node* BinarySearchTree::deleteNode(Node* node, string& courseId) {

	if (node == nullptr) { //If node is empty
		return nullptr; //node not found
	}

	//Traverse left if courseID is smaller
	if (courseId < node->course.courseId) {
		node->left = deleteNode(node->left, courseId);
	}

	//Traverse right if courseId is larger
	else if (courseId > node->course.courseId) {
		node->right = deleteNode(node->right, courseId);
	}

	/*
	 *  This else statement shows the node has been found.
	 *  To supplement the algorithm for user functionality
	 *  implementing a successor change is required here
	 *  but this will later be replaced when the AVL
	 *  self balancing design is built, which will rotate the
	 *  tree to keep it balanced. Currently, this algorithm
	 *  will overtime unbalance the tree, but allow user delete
	 *  functionality
	 *  ##TODO implement balancing algorithm to replace successor algorithm.
	 */
	else { //node to delete is found

		//Case 1, no children
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			return nullptr;
		}

		//Case 2, one child
		else if (node->left == nullptr) { //right child exists
			Node* tempNode = node->right; //Grab the right child
			delete node; //remove right's parent node
			return tempNode; //replace deleted node with right node
		}
		else if (node->right == nullptr) { //left child exists
			Node* tempNode = node->left; //Grab left child
			delete node; //remove left's parent node
			return tempNode; //replace delted node with left node
		}

		/*
		 * Case 3, two children
		 * This is a more complicated tree. A BST tree
		 * uses branches, so if we have a parent node, a left is less than
		 * a right is greater than, but we need the IMMEDIATE successor
		 * (nearest higher value) to the parent node to replace it. To do this,
		 * we find the smallest value of the right subtree. So, traverse right,
		 * then traverse left until left is null pointer. This ensures we
		 * have the immediate next value from the parent node, then we replace
		 * that original parent node with the object from the smallest value of the
		 * right subtree.
		 */
		else {
			Node* successor = node->right; //branch into right subtree
			while (successor->left != nullptr) { //traverses left from that node until nullptr
				successor = successor->left; //keep moving left to find true successor
			}

			//Replaces the node found to delete with the successor course object
			node->course = successor->course;

			/*
			 * Since successor was copied to the node to delete, we must
			 * delete the node so there are no duplicates. To do this, we recall
			 * deleteNode on the node above the successor, and pass the successors id
			 */
			node->right = deleteNode(node->right, successor->course.courseId); //finds and deletes successor
		}
	}
	return node;
}

/*
 * DeleteCourseWithDependencyCheck()
 * This is the function that is called from main (option 5).
 * It is a wrapper class for isCourseDependency() (which checks to ensure
 * that the course to be deleted is not a prerquisite to another active
 * course in the tree) and deleteNode() which will recursively delete the node
 * if it exists in the tree and is safe to delete (not a dependency).
 * @param string courseId
 * @return boolean
 */
bool BinarySearchTree::DeleteCourseWithDependencyCheck(string courseId) {
	Course userCourseToDelete = Search(courseId); //Find the course to delete

	//if course to delete not found
	if (userCourseToDelete.courseId.empty()) {
		cout << "Error: " << courseId << " doesn't exist." << endl;
		return false;
	}

	//if course to delete is a dependency
	if (courseDependencyCheck(root, courseId)) {
		cout << "Error: Can not delete " << courseId
			<< ". It is a prerequisite to another course." << endl;
		return false;
	}

	// delete node if found and if not a dependency
	root = deleteNode(root, courseId);
	cout << courseId << " has been successfully deleted." << endl;
	return true;

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
	string searchId; //Variable for user search string (also used for delete)
	int choice; //Variable for user menu option

	//Set of variables to construct a user course to add to tree
	string addCourseName;
	string addCourseID;
	string addPreReq1 = "";
	string addPreReq2 = "";

	switch (argc) { //Command prompt arg
	case 2:
		fileName = argv[1]; //Gets file as first argument
		break;
	default:
		fileName = "ABCU_Advising_Program_Input.csv"; //hard coded file name as default

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
		// Added enhancement 4 & 5 for Add and Delete course
		cout << "  4: Add Course." << endl;
		cout << "  5: Delete Course by ID." << endl;
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


		case 4: { //Add course
			//Flushes any previous cin call
			// Such as if a different case was used before this.
			cin.ignore(10000, '\n');

			//Get user added course name
			cout << "Enter course name: ";
			getline(cin, addCourseName);

			//Get user added course ID
			cout << "Enter course ID: ";
			getline(cin, addCourseID);

			//Convert addCourseID entry to uppercase
			for (int i = 0; i < addCourseID.length(); ++i) {
				addCourseID[i] = toupper(addCourseID[i]);
			}

			//Get user added prerequisite 1
			cout << "Enter prerequisite 1 ID or leave blank if none: ";
			getline(cin, addPreReq1);

			//Uppercase the addPreReq1 Entry
			if (!addPreReq1.empty()) {
				for (int i = 0; i < addPreReq1.length(); ++i) {
					addPreReq1[i] = toupper(addPreReq1[i]);
				}

				//Check to ensure that the prerequisite ID exists in the tree
				//If the prerequisite does not exist as a full course object
				//the prerequisite should be denied until the course is added first.
				if (bst->Search(addPreReq1).courseId.empty()) {
					cout << "Error: Prerequisite 1 ID does not exist: " << endl;
					cout << "In order to add this course, prerequisite 2 must exist in the tree." << endl;
					cout << "Please add the prerequisite as a course first before continuing" << endl;
					break;
				}
			}

			//Get user added prerequisite 2
			cout << "Enter prerequisite 2 ID or leave blank if none: ";
			getline(cin, addPreReq2);

			//Uppercase the addPreReq2 entry
			if (!addPreReq2.empty()) {
				for (int i = 0; i < addPreReq2.length(); ++i) {
					addPreReq2[i] = toupper(addPreReq2[i]);
				}

				//Check to ensure Prerequisite ID exists in the tree.
				if (bst->Search(addPreReq2).courseId.empty()) {
					cout << "Error: Prerequisite 2 ID does not exist: " << endl;
					cout << "In order to add this course, prerequisite 2 must exist in the tree." << endl;
					cout << "Please add the prerequisite as a course first before continuing" << endl;
					break;
				}
			}

			//Construct the course object using the parameters received.
			Course aCourse;
			aCourse.courseName = addCourseName;
			aCourse.courseId = addCourseID;
			aCourse.preReq1 = addPreReq1;
			aCourse.preReq2 = addPreReq2;

			//add course to the tree
			bst->InsertCourse(aCourse);
			cout << addCourseID << " successfully added." << endl;
			break;
		}


		case 5: { //Delete Course by ID
			//Variables for deleting by course id
			string deleteCourseID;

			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //flush stream

			cout << "Enter course ID to remove: ";
			cin >> deleteCourseID;
			cout << endl;

			//Uppercase the ID
			if (!deleteCourseID.empty()) {
				for (int i = 0; i < deleteCourseID.size(); ++i) {
					deleteCourseID[i] = toupper(deleteCourseID[i]);
				}
			}

			/*
			 * ##FIXME: Unfortunately, if we want to check the prerequisites to make sure
			 *  we are not deleting a course that is a prequisite to another course, another
			 *  structure must be designed called a reverse index, which maps prerequisites
			 *  to higher courses (as their dependencies). This structure can help prevent
			 *  deletion of courses that are required to be taken before other courses that
			 *  will STILL exists in the tree. The problem here is that comparing the
			 *  deleteCourseID to every single preReq1 and preReq2 of every single node
			 *  reduces the time complexity of the delete function to O(log n + n) = O(n)
			 *  This doesnt strictly defeat the purpose of creating an AVL tree, but it
			 *  increases the time complexity making it less efficient with a delete function
			 *  that checks to ensure the course being deleted is not a dependency of a course
			 *  that still exists. I'm finding it difficult to design this dependency check
			 *  using a reverse index, as the structure is unclear to me in my research.
			 *
			 *  ##FOR NOW: I am going to implement the O(n) dependency check method
			 *  to prevent dependency deletion until I can find a better way to implement this.
			 *
			 *  ##FUTURE REFERENCE: Inverse/reverse indexing will provide a time complexity for
			 *  Deletion to be O(log n + k) where k is ONLY the number of dependencies, not the
			 *  entire tree. (for example, CS101 is the prerequisite for CS201 and CS245 which will
			 *  be portrayed as: [CS101] | {CS201, CS245} which shows 101 must exist if 201 and 245 exist).
			 *
			 */

			bst->DeleteCourseWithDependencyCheck(deleteCourseID);
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