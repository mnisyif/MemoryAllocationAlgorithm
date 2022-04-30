#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "holes.h"

// memory management operations
void first(List * processQ){
	List * memory = createList();
	Node * tmpCur, * tmpMem;
	
	//calculation necessary values
	int memCap = 1024, totalLoad = 0, holes, enough = 0, memRef;
	float avgPro, avgHoles, memPer, cumMem = 0.0, totalHoles = 0.0, totalProcess = 0.0; 
	
	//initialize a memory block in memory
	tmpMem = createProcess(0, memCap, 0, 0);
	insertBack(memory, tmpMem);
	memory->length = 0;
	tmpMem = memory->head;
	tmpCur = processQ->head;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(processQ->length > 0){
		tmpCur = processQ->head;
		tmpMem = memory->head;	

		if((tmpCur->size <= memCap) && fits(memory, tmpCur)){
			while(tmpMem != NULL){

				if((tmpMem->size >= tmpCur->size) && (tmpMem->pid == 0)){
					tmpCur = removeNode(processQ, tmpCur);
					
					tmpMem->pid = -1;
					memRef = tmpMem->size - tmpCur->size;
					splitMem(memory, -1, tmpCur->pid, tmpCur->size, tmpCur->swapped);
					removeNode(memory, tmpMem);
					memCap = memCap - tmpCur->size;

					if(memRef > 0){
						splitMem(memory, tmpCur->pid, 0, memRef, 0);
					}
					/*
						Update traceable variables for utilization calculations
					*/
					memPer = memCount(memory);
					cumMem = cumMem + memPer;
					totalLoad++;
					holes = holeCount(memory);
					totalProcess = totalProcess + processCount(memory);
					totalHoles = totalHoles + holes;
					
					/*
						Print stats for process loaded onto memory
					*/
					printf("pid loaded, #processes %d, holes = %d, %%memusage = %d, cumulative %%mem = %d\n",
						processCount(memory), holes, (int)memPer, (int)(cumMem/(float)totalLoad));
					break;
				}
				 
				tmpMem = tmpMem->next;	
			}

		}else{
			while(enough == 0){
				if(fits(memory, tmpCur) == 1){
					enough = 1;

				}else{
					freeMem(memory, processQ, &memCap);
				}
			}
			enough = 0;
		}
		timeCounter(memory);
	}

	printf("Total loads = %d, average process = %.1f, average #holes = %.1f, cumulative %%mem = %d\n",
		totalLoad, totalProcess / ((float)totalLoad), totalHoles/(float)totalLoad, (int)(cumMem/(float)totalLoad));
}

void best(List * processQ){
	List * memory = createList();
	Node * tmpCur, * tmpMem;
	
	//calculation necessary values
	int memCap = 1024, totalLoad = 0, holes, enough = 0, memRef;
	float avgPro, avgHoles, memPer, cumMem = 0.0, totalHoles = 0.0, totalProcess = 0.0; 
	
	//initialize a memory block in memory
	tmpMem = createProcess(0, memCap, 0, 0);
	insertBack(memory, tmpMem);
	memory->length = 0;
	tmpMem = memory->head;
	tmpCur = processQ->head;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(processQ->length > 0){
		tmpCur = processQ->head;
		tmpMem = memory->head;
		int minSize = 0;
		if((tmpCur->size <= memCap) && fits(memory, tmpCur)){
			
			bestFits(memory, tmpCur);
			while(tmpMem != NULL){
				if(tmpMem->pid == -1){
					break;
				}
				tmpMem = tmpMem->next;
			}

			tmpCur = removeNode(processQ, tmpCur);

			memRef = tmpMem->size - tmpCur->size;
			splitMem(memory, -1, tmpCur->pid, tmpCur->size, tmpCur->swapped);
			removeNode(memory, tmpMem);
			memCap = memCap - tmpCur->size;

			if(memRef > 0){
				splitMem(memory, tmpCur->pid, 0, memRef, 0);
			}

			/*
				Update traceable variables for utilization calculations
			*/
			memPer = memCount(memory);
			cumMem = cumMem + memPer;
			totalLoad++;
			holes = holeCount(memory);
			totalProcess = totalProcess + processCount(memory);
			totalHoles = totalHoles + holes;
			
			/*
				Print stats for process loaded onto memory
			*/
			printf("pid loaded, #processes %d, holes = %d, %%memusage = %d, cumulative %%mem = %d\n",
				processCount(memory), holes, (int)memPer, (int)(cumMem/(float)totalLoad));

		}else{
			while(enough == 0){
				if(fits(memory, tmpCur) == 1){
					enough = 1;

				}else{
					freeMem(memory, processQ, &memCap);
				}
			}
			enough = 0;
		}
		timeCounter(memory);
	}

	printf("Total loads = %d, average process = %.1f, average #holes = %.1f, cumulative %%mem = %d\n",
		totalLoad, totalProcess / ((float)totalLoad), totalHoles/(float)totalLoad, (int)(cumMem/(float)totalLoad));
}

void worst(List * processQ){
	List * memory = createList();
	Node * tmpCur, * tmpMem;
	
	//calculation necessary values
	int memCap = 1024, totalLoad = 0, holes, enough = 0, memRef;
	float avgPro, avgHoles, memPer, cumMem = 0.0, totalHoles = 0.0, totalProcess = 0.0; 
	
	//initialize a memory block in memory
	tmpMem = createProcess(0, memCap, 0, 0);
	insertBack(memory, tmpMem);
	memory->length = 0;
	tmpMem = memory->head;
	tmpCur = processQ->head;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(processQ->length > 0){
		tmpCur = processQ->head;
		tmpMem = memory->head;
		if((tmpCur->size <= memCap) && fits(memory, tmpCur)){
			
			worstFits(memory, tmpCur);
			while(tmpMem != NULL){
				if(tmpMem->pid == -1){
					break;
				}
				tmpMem = tmpMem->next;
			}

			tmpCur = removeNode(processQ, tmpCur);

			memRef = tmpMem->size - tmpCur->size;
			splitMem(memory, -1, tmpCur->pid, tmpCur->size, tmpCur->swapped);
			removeNode(memory, tmpMem);
			memCap = memCap - tmpCur->size;

			if(memRef > 0){
				splitMem(memory, tmpCur->pid, 0, memRef, 0);
			}

			/*
				Update traceable variables for utilization calculations
			*/
			memPer = memCount(memory);
			cumMem = cumMem + memPer;
			totalLoad++;
			holes = holeCount(memory);
			totalProcess = totalProcess + processCount(memory);
			totalHoles = totalHoles + holes;
			
			/*
				Print stats for process loaded onto memory
			*/
			printf("pid loaded, #processes %d, holes = %d, %%memusage = %d, cumulative %%mem = %d\n",
				processCount(memory), holes, (int)memPer, (int)(cumMem/(float)totalLoad));

		}else{
			while(enough == 0){
				if(fits(memory, tmpCur) == 1){
					enough = 1;

				}else{
					freeMem(memory, processQ, &memCap);
				}
			}
			enough = 0;
		}
		timeCounter(memory);
	}

	printf("Total loads = %d, average process = %.1f, average #holes = %.1f, cumulative %%mem = %d\n",
		totalLoad, totalProcess / ((float)totalLoad), (totalHoles/(float)totalLoad), (int)(cumMem/(float)totalLoad));
}

void next(List * processQ){
	List * memory = createList();
	Node * tmpCur, * tmpMem;
	
	//calculation necessary values
	int memCap = 1024, totalLoad = 0, holes, enough = 0, memRef;
	float avgPro, avgHoles, memPer, cumMem = 0.0, totalHoles = 0.0, totalProcess = 0.0; 
	
	//initialize a memory block in memory
	tmpMem = createProcess(0, memCap, 0, 0);
	insertBack(memory, tmpMem);
	memory->length = 0;
	tmpMem = memory->head;
	tmpCur = processQ->head;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(processQ->length > 0){
		tmpCur = processQ->head;
		tmpMem = memory->head;	

		if((tmpCur->size <= memCap) && fits(memory, tmpCur)){
			while(tmpMem != NULL){

				if((tmpMem->size >= tmpCur->size) && (tmpMem->pid == 0)){
					tmpCur = removeNode(processQ, tmpCur);
					
					tmpMem->pid = -1;
					memRef = tmpMem->size - tmpCur->size;
					splitMem(memory, -1, tmpCur->pid, tmpCur->size, tmpCur->swapped);
					removeNode(memory, tmpMem);
					memCap = memCap - tmpCur->size;

					if(memRef > 0){
						splitMem(memory, tmpCur->pid, 0, memRef, 0);
					}
					/*
						Update traceable variables for utilization calculations
					*/
					memPer = memCount(memory);
					cumMem = cumMem + memPer;
					totalLoad++;
					holes = holeCount(memory);
					totalProcess = totalProcess + processCount(memory);
					totalHoles = totalHoles + holes;
					
					/*
						Print stats for process loaded onto memory
					*/
					printf("pid loaded, #processes %d, holes = %d, %%memusage = %d, cumulative %%mem = %d\n",
						processCount(memory), holes, (int)memPer, (int)(cumMem/(float)totalLoad));
					break;
				}
				 
				tmpMem = tmpMem->next;	
			}

		}else{
			while(enough == 0){
				if(fits(memory, tmpCur) == 1){
					enough = 1;

				}else{
					freeMem(memory, processQ, &memCap);
				}
			}
			enough = 0;
		}
		timeCounter(memory);
	}

	printf("Total loads = %d, average process = %.1f, average #holes = %.1f, cumulative %%mem = %d\n",
		totalLoad, totalProcess / ((float)totalLoad), totalHoles/(float)totalLoad, (int)(cumMem/(float)totalLoad));
}

// information operations
List * readFile(char * fileName){
	char * line = malloc(sizeof(char ) * BUFFER_SIZE);

	FILE * fp = fopen(fileName, "r");
	Node * process;
	List * queue = createList();

	if(fp == NULL){
		printf("Error: Inaccessible file\n");
		exit(0);
	}

	while(fgets(line, BUFFER_SIZE, fp) != NULL){
		process = parseLine(line);
		insertBack(queue, process);
	}

	return queue;
}

Node * parseLine(char * fileLine){
	char * token = malloc(sizeof(char) * 10);
	int tempPid, tempSize;

	token = strtok(fileLine, " ");
	tempPid = atoi(token);
	token = strtok(NULL, " ");
	tempSize = atoi(token);

	return createProcess(tempPid, tempSize, 0, 0);
}

//list operations
List * createList(){
	List * newQueue = malloc(sizeof(List));

	newQueue->head = NULL;
	newQueue->tail = NULL;
	newQueue->length = 0;

	return newQueue;
}

Node * createProcess(int pID, int size, int swap, int timeS){
	Node * newProcess = (Node *)malloc(sizeof(Node));

	newProcess->pid = pID;
	newProcess->size = size;
	newProcess->swapped = swap;
	newProcess->timeStamp = timeS;
	newProcess->next = NULL;
	newProcess->prev = NULL;

	return newProcess;
}

void insertBack(List * queue, Node *process){
	if (queue == NULL || process == NULL){
		return;
	}

	if (queue->length == 0){
		queue->head = process;
		queue->tail = process;

	} else{
		queue->tail->next = process;
		process->prev = queue->tail;
		queue->tail = process;
	}

	(queue->length)++;
}

void splitMem(List * queue, int pID, int newPid, int sizeLeftover, int swap){
	Node * tmpCur = queue->head;

	//check if queue is empty
	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	//navigate through queue to find desired node
	while((tmpCur->pid) != pID){
		//printf("at pid %d looking for %d\n", tmpCur->pid, pID);
		if(tmpCur->next == NULL){
			printf("Error: Key not found!\n");
			exit(0);
		
		}else{
			tmpCur = tmpCur->next;
		}
	}

	//create new node after tmpCur
	Node * newNode = createProcess(newPid, sizeLeftover, swap, 0);

	if(tmpCur == queue->tail){
		newNode->next = NULL;
		queue->tail = newNode;
	
	} else{
		newNode->next = tmpCur->next;
		tmpCur->next->prev = newNode;
	}
		newNode->prev = tmpCur;
		tmpCur->next = newNode;

	if(pID > 0){
		(queue->length)++;
	}
}

Node * removeNode(List *queue, Node * toBeRemoved){
	Node * tmpCur = queue->head;
	Node * tmpPrev = NULL;


	if (tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}
	
	while( tmpCur != NULL && ((tmpCur->pid) != toBeRemoved->pid)){
		//printf("at pid %d looking for %d\n", tmpCur->pid, pID);
		if(tmpCur->pid == toBeRemoved->pid){
			break;
		}
		tmpPrev = tmpCur;
		tmpCur = tmpCur->next;

	}
	//printf("Node to be removed %d\n", tmpCur->pid);
	if(tmpCur == queue->head){
		queue->head = queue->head->next;

	}else{
		tmpCur->prev->next = tmpCur->next;
	}

	if(tmpCur == queue->tail){
		queue->tail = queue->tail->prev;
	
	}else{
		tmpCur->next->prev = tmpCur->prev;
	}

	Node * resNode = createProcess(tmpCur->pid, tmpCur->size, tmpCur->swapped, 0);
	
	free(tmpCur);
	(queue->length)--;
	
	return resNode;
}

void freeMem(List * memory, List * processQ, int * memCap){
	Node * tmpMem = findOldest(memory);
	
	*memCap = *memCap + (tmpMem->size);
	(tmpMem->swapped)++;
	
	splitMem(memory, tmpMem->pid, 0, tmpMem->size, 0);
	Node * res = removeNode(memory, tmpMem);
	combineHoles(memory);

	if (res->swapped < 3){
		insertBack(processQ, res);	
	} 
	else{
		free(res);
	}
}

void worstFits(List * memory, Node * toBeAdded){
	int maxSizeRef = 0, maxSize = 0, tmpMax = 0;
	Node * tmpMem = memory->head;

	//find the best block to fit the process toBeAdded
	while(tmpMem != NULL){
		if((tmpMem->size >= toBeAdded->size) && (tmpMem->pid == 0)){
			
			// assign ref node to the fist hole
			// one time setup
			if(maxSizeRef == 0){
				maxSizeRef = tmpMem->size;
				maxSize = (tmpMem->size) - (toBeAdded->size);
			}

			// updates tmp min value
			tmpMax = (tmpMem->size) - (toBeAdded->size);

			if(tmpMax >= maxSize){
				maxSize = tmpMax;
				maxSizeRef = tmpMem->size;
			}
		}
		tmpMem = tmpMem->next;
	}

	//Place a marker on the best memory block to add ToBeAdded
	tmpMem = memory->head;

	while(tmpMem != NULL){
		if((tmpMem->size == maxSizeRef) && (tmpMem->pid == 0)){
			tmpMem->pid = -1;
			break;
		}
		tmpMem = tmpMem->next;
	}
}

void bestFits(List * memory, Node * toBeAdded){
	int minSizeRef = 0, minSize = 0, tmpMin = 0;
	Node * tmpMem = memory->head;

	//find the best block to fit the process toBeAdded
	while(tmpMem != NULL){
		if((tmpMem->size >= toBeAdded->size) && (tmpMem->pid == 0)){
			
			// assign ref node to the fist hole
			// one time setup
			if(minSizeRef == 0){
				minSizeRef = tmpMem->size;
				minSize = (tmpMem->size) - (toBeAdded->size);
			}

			// updates tmp min value
			tmpMin = (tmpMem->size) - (toBeAdded->size);

			if(tmpMin <= minSize){
				minSize = tmpMin;
				minSizeRef = tmpMem->size;
			}
		}
		tmpMem = tmpMem->next;
	}

	//Place a marker on the best memory block to add ToBeAdded
	tmpMem = memory->head;

	while(tmpMem != NULL){
		if((tmpMem->size == minSizeRef) && (tmpMem->pid == 0)){
			tmpMem->pid = -1;
			break;
		}
		tmpMem = tmpMem->next;
	}
}

int fits(List * memory, Node * toBeAdded){
	Node * tmpMem = memory->head;

	while(tmpMem != NULL){
		//printf("Size of tobeAdded %d, size of memory block %d\n", toBeAdded->size, tmpMem->size);	
		if((tmpMem->size >= toBeAdded->size) && ((tmpMem->pid == 0) || (tmpMem->pid == -1))){
			return 1;
		}
		tmpMem = tmpMem->next;
	}
	return 0;
}

void combineHoles(List * queue){
	Node * tmpCur = queue->head;
	Node * tmpPrev = NULL;
	int inHole = 0;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(tmpCur != NULL){
		if ((inHole == 0) && (tmpCur->pid == 0)){
			inHole = 1;
			tmpPrev = tmpCur;
			tmpCur = tmpCur->next;
		
		}else if((inHole == 0) && (tmpCur->pid > 0)){
			tmpCur = tmpCur->next;
		
		}else if((inHole == 1) && (tmpCur->pid == 0)){
			(tmpCur->size) = (tmpPrev->size) + (tmpCur->size);
			removeNode(queue, tmpPrev);
			tmpPrev = tmpCur;
			tmpCur = tmpCur->next;

		}else if((inHole == 1) && (tmpCur->pid > 0)){
			inHole = 0;
			tmpCur = tmpCur->next;
		}
	}
}

void timeCounter(List * queue){
	Node * tmpCur = queue->head;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(tmpCur != NULL){
		if(tmpCur->pid >= 1){
			(tmpCur->timeStamp)++;
		}

		tmpCur = tmpCur->next;
	}
}

float memCount(List * memory){
	Node * tmpCur = memory->head;
	float totalMem = 0.0;
	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(tmpCur != NULL){
		if(tmpCur->pid > 0)
			totalMem = totalMem + tmpCur->size;
		tmpCur = tmpCur->next;
	}

	return ((totalMem/1024.0)*100.0);
}

int holeCount(List * queue){
	Node * tmpCur = queue->head;
	int counter = 0;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(tmpCur != NULL){
		if(tmpCur->pid == 0){
			counter++;
		}

		tmpCur = tmpCur->next;
	}

	return counter;
}

int processCount(List * memory){
	Node * tmpCur = memory->head;
	int counter = 0;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(tmpCur != NULL){
		if(tmpCur->pid > 0){
			counter++;
		}

		tmpCur = tmpCur->next;
	}

	return counter;
}

Node * findOldest(List * memory){
	Node * tmpCur = memory->head;
	int oldest = 0;

	if(tmpCur == NULL){
		printf("Error: Invalid input!\n");
		exit(0);
	}

	while(tmpCur != NULL){
		if((tmpCur->timeStamp > oldest)){
			oldest = tmpCur->timeStamp;
			//printf("Oldest so far is %d\n", tmpCur->pid);
		}

		tmpCur = tmpCur->next;
	}

	tmpCur = memory->head;
	while(tmpCur != NULL){
		if(tmpCur->timeStamp == oldest){
			return tmpCur;
		}

		tmpCur = tmpCur->next;
	}

	return NULL;
}

void printList(List * queue){
	Node * tmpNode = queue->head;

	while(tmpNode != NULL){
		printf("Process = %d, with memsize of = %d and time stamp = %d \n", tmpNode->pid, tmpNode->size, tmpNode->timeStamp);
		tmpNode = tmpNode->next;
	}
}