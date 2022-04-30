#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "holes.h"

int main(int argc, char *argv[]){
	/*
	 * Error checking 
	 */
	if(argc < 3){
		printf("Error: Invalid input!\n");
		printf("Proper usage: ./holes \"filename\" <first|best|next|worst>\n");
		exit(0);
	}

	//create a list from info in passed file
	List * processQ = readFile(argv[1]);

	//case switch to determine fit algorithm
	if(strcmp(argv[2], "first") == 0){
		first(processQ);
	
	}else if(strcmp(argv[2], "best") == 0){
		best(processQ);
	
	}else if(strcmp(argv[2], "worst") == 0){
		worst(processQ);
	
	}else if(strcmp(argv[2], "next") == 0){
		next(processQ);
	
	}else {
		printf("Proper usage: ./holes \"filename\" <first|best|next|worst>\n");
	}
	return 0;
}
