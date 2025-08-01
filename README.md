# Binary Search Tree Enhancement One
CS-499 Capstone Artifact Enhancement One (Binary Search Tree)
<br>
## Original Artifact
[Original Artifact](https://github.com/AnthonyBaratti/EnhancementOne/tree/main/BinarySearchTree)<br><br>
The binary search tree program was created in CS-300 Data Structures & Algorithms in June of 2024  
It implements a user menu for the user to choose to load a .csv file (either with a command line prompt, or default to the file included)  
Then the Parser Class parses the file row by row, collecting the data into course object and inserts each course object into the binary search tree which is organized by course.Id.
The menu also allows for searching by course ID and printing the list of courses in order. The data structure works by implementing a node structure, which essentially builds a node to be inserted with a course. The node differs from the course because rather than holding course attributes, it holds the next node branches (left node or right node). When a node is inserted, it is compared (greater than or less than) to the current node in question (starting at the root), then traverses left if the ID is smaller, or right if the ID is larger. It uses recursive algorithms to re-pass the checked node as the new argument, allowing it to traverse down a tree until a node is NOT found (nullptr), at which point, the node is placed in the nullptr spot.

## Artifact Enhancement: User Functionality
[Enhanced Artifact: User Functionality](https://github.com/AnthonyBaratti/EnhancementOne/tree/main/BinarySearchTreeEnhancementOne)<br><br>
The enhancements performed on the Binary Search Tree are to create user functionality for adding a custom class and deleting a custom class. This enhancement resolves Category 1 of CS-499: Software Engineering & Design<br><br>
First, a menu option was added in main for each function (add and delete). The add option allows a user to input a course name, a course ID, and up to two prequisites. The delete option removes a course by ID, however it will throw a warning and deny any deletes if the course is a dependency for another course (i.e., the course to be deleted is a prerequisite of another course. The higher course must first be deleted). When a course is created, it takes the user input and builds a course object using the existing insert course functionality (traverses the tree to find the appropriate spot to put the course). The delete course option does a couple of things. First, it performs the dependency check, which searches every node's prerequisites. If the course is a dependency, deletion is denied. If the course can be deleted, it uses a successor algorithm that reconnects the leaves of the tree to the parent of the node to be deleted, so the tree remains intact after removing a node (case 1 - no children, case 2 - one child, case 3 - two children). Both of these functions are wrapped in a method that is called from the main DeleteCourseWithDependencyCheck, which allows the program to keep most of the functionality private, while only exposing the wrapper function.<br>
# Features
- Organizes Binary Search Tree by course ID (in order)
- User functionality to:
  - Upload csv file
  - Print Course List
  - Find & Print Course by ID
  - Add Custom Course
  - Delete Course with Dependency Check
- Bounds checking for data input (course objects)
- Successor algorithm to reconnect tree after node removal

