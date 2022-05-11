# About: This implementation uses doubly linked list to simulate memory given 4 different memory management algorithms

## (1) List * readFile(char * fileName);

- reads contents from file and returns a datastructure with all data
  - @param the name of the file to be read
  - @return a pointer to a list with parsed data
========================

## (2) Node * parseLine(char * fileLine);

- parses line by line and returns a node representing a process
  - @param char pointer a string that holds process number and memory size associated with it
  - @return returns a pointer to a node process
========================

## (3) List * createList();

- Creates an empty list and returns a pointer to it
  - @returns a pointer of type List back
========================

## (4) Node * createProcess(int pID, int size, int swap, int timeS);

- Creates a process with the passed parameters and returns a pointer to a new process Node
  - @param int pID: an integer that represents the process id
  - @param int size: an integer that represents the process size to occupy in memory
  - @param int swap: an integer that represents number of swaps of a process, by default = 0
  - @param int timeS: an integer that represents the time stamp of a process
  - @return Node *: returns a pointer of struct node
========================

## (5) void insertBack(List * queue, Node * process);

- inserts a process at the back of the queue
  - @param List * queue: a pointer to a list that a process will be addedd to
  - @param Node * process: a pointer to a Node of a process to be added to a queue
========================

## (6) void splitMem(List * queue, int pID, int newPid, int sizeLeftover, int swap);

- Creates and adds a process to a queue
  - @param List * queue: a pointer to a List to which a process will be added to
  - @param int pID: an integer that represents after what node a new node to be added
  - @param int newPid: an integer that represents the pid of the new node to be added
  - @param int sizeLeftOver: integer that represents the size of the new node
  - @param int swap: integer represents the number of swappes of a process
========================

## (7) Node * removeNode(List *queue, Node * toBeRemoved);

- removes a node from a queue and returns its address
  - @param List * queue: a pointer to a List to which a node to be removed from
  - @param Node * toBeRemoved: a pointer to a Node to which is to be removed
  - @return Node *: returns a pointer to the removed node from List queue
========================

## (8) void freeMem(List * memory, List * processQ, int * memCap);

- Frees a memory queue from process
  - @param List * memory: a pointer to memory queue to be freed
  - @param List * processQ: a pointer to a process queue to be populated after memory is freed
  - @param int * memCap: a integer pointer to a memory capacity to be updated as memory is freed
========================

## (9) void combineHoles(List * memory);

- combines empty contiguious holes together
  - @param List * memory: a pointer to a memory queue to combine its holes
========================

## (10)void printList(List * queue);

- print a list struct, used for debugging and testing
  - @param List * queue: a pointer to a list to be printed back in stdout
========================

## (11)void timeCounter(List * memory);

- updates time stamps on process in memory queue
  - @param List * memory: a pointer to list memory queue for its processes to be updated
========================

## (12)int processCount(List * memory);

- counts processes in the memory queue and returns it back as an int
  - @param List * memory: a pointer to a list memory queue to count its processes
  - @return int: returns number of process in memory queue
========================

## (13)float memCount(List * memory);

- counts total usedup memory
  - @param List * memory: a pointer to a list memory queue to count memory usage by its processes
  - @return float: returns a single float value representing current memory usage
========================

## (14)Node * findOldest(List * memory);

- finds the oldest process in a memory queue
  - @param List * memory: a pointer to a memory queue
  - @return Node *: address of the oldest process node in a memory queue
========================

## (15)int holeCount(List * queue);

- counts number of holes in a memory queue
  - @param List * queue: a pointer to a memory queue
  - @return int: returns an integer representing number of holes in a queue
========================

## (16)void first(List * processQ);

- method to simulate first fit memory management algorithm
  - @param List * processQ: a pointer to list to be simulated
========================

## (17)void best(List * processQ);

- method to simulate best fit memory management algorithm
  - @param List * processQ: a pointer to list to be simulated
========================

## (18)void next(List * processQ);

- method to simulate nest fit memory management algorithm
  - @param List * processQ: a pointer to list to be simulated
========================

## (19)void worst(List * processQ);

- method to simulate worst fit memory management algorithm
  - @param List * processQ: a pointer to list to be simulated
========================

## (20)void bestFits(List * memory, Node * toBeAdded);

- Method to mark memory block that best fits process to be added
  - @param List * memory: a pointer to list memory queue to be analyzed
  - @param Node * toBeAdded: a pointer to Node process to be added to the memory queue
========================

## (21)void worstFits(List * memory, Node * toBeAdded);

- Method to mark memory block that worst fits process to be added
  - @param List * memory: a pointer to list memory queue to be analyzed
  - @param Node * toBeAdded: a pointer to Node process to be added to the memory queue
========================

## (22)int fits(List * memory, Node * toBeAdded);

- function used to verify if a process fits anywhere in a memory queue
  - @param List * memory: a pointer to list memory queue to be analyzed
  - @param Node * toBeAdded: a pointer to Node process to be added to the memory queue
  - @return int: returns 1 if processs toBeAdded fits in memory and 0 otherwise
========================# MemoryManagement
