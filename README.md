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
[Enhanced Artifact: User Functionality](https://github.com/AnthonyBaratti/EnhancementOne/tree/main/BinarySearchTreeEnhancementOne)

