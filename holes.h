#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 20

typedef struct listNode{
	int pid, size, swapped, timeStamp;
	struct listNode * next;
	struct listNode * prev;
}Node;

typedef struct queue{
	Node * head;
	Node * tail;
	int length;
}List;

//information gathering
List * readFile(char * fileName);
Node * parseLine(char * fileLine);

//list operations
List * createList();
Node * createProcess(int pID, int size, int swap, int timeS);
void insertBack(List * queue, Node * process);
void splitMem(List * queue, int pID, int newPid, int sizeLeftover, int swap);
Node * removeNode(List *queue, Node * toBeRemoved);
void freeMem(List * memory, List * processQ, int * memCap);
void combineHoles(List * memory);
void printList(List * queue);
void timeCounter(List * memory);
int processCount(List * memory);
float memCount(List * memory);
Node * findOldest(List * memory);
int holeCount(List * queue);

//main functions
void first(List * processQ);
void best(List * processQ);
void next(List * processQ);
void worst(List * processQ);
void bestFits(List * memory, Node * toBeAdded);
void worstFits(List * memory, Node * toBeAdded);
int fits(List * memory, Node * toBeAdded);
//void printOperation()
