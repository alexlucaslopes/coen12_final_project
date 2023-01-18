/*
 * File: dataset.c
 *
 * Author: Alexandre Lopes
 * 
 * Date: 13 March 2022
 * 
 * Description: Implementation for the dataset. Lists all the main functions
 * and data structures. It also defines how they will operate.
 *
 * Complexity: Functions have O(n) 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "dataset.h"

#define EMPTY 0	
#define FILLED 1
#define DELETED 2

struct node{
	int id;
	int age;
};

struct set{
        int count;
        int length;
        NODE **students;
	char *flags;
}; 

static int search(SET *sp, int x, bool *found); 

/*
 * Function: createDataSet
 *
 * Description: creates a data set with count, length,
 * students (which have an age and id component), and flags
 */
SET *createDataSet(int maxElts){	
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->students = malloc(sizeof(NODE*)*maxElts);
	assert(sp->students != NULL);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags != NULL);
	int i;
	for(i=0; i<sp->length; i++){
		sp->students[i] = malloc(sizeof(NODE));
		assert(sp->students[i] != NULL);
		sp->flags[i] = EMPTY;
	}
	return sp;
}

/*
 * Function: destroyDataSet
 * 
 * Description: frees all the data located in the
 * data set
 */
void destroyDataSet(SET *sp){
        assert(sp != NULL);
        int i;
	for (i=0; i < sp->length; i++){
		if(sp->students[i] == NULL){
			free(sp->students[i]);
		}
	}
	free(sp->students);
	free(sp->flags);
        free(sp);
}

/*
 * Function: insertion
 *
 * Description: inserts a new node (age and id) into the
 * hash table based on whether it already exists or not
 * and where the hash function assigns it
 */
void insertion(SET *sp, int uniqID, int findAge){    
        assert (sp != NULL);
	bool found;	     
        int locn = search(sp, uniqID, &found);
        if (!found){
                assert(sp->count < sp->length);
                sp->students[locn]->id = uniqID;
		sp->students[locn]->age = findAge;  
                sp->flags[locn] = FILLED;       
                sp->count++;    
        }
        return;
}

/*
 * Function: deletion
 *
 * Description: deletes a node from the hash table
 * based on its id
 */
void deletion(SET *sp, int uniqID){	
        assert (sp != NULL);     
        int locn = searchID(sp, uniqID);
	if(locn > 0){
                sp->flags[locn] = DELETED;
                sp->count--;
		printf("The value has been successfully deleted.\n");
                return;
        }
	else{
        	printf("Could not find the value to be deleted.\n");
		return;
	}
}

/*
 * Function: searchID
 *
 * Description: determines whether a node is present in the
 * hash table or not by searching for its id
 */
int searchID(SET *sp, int uniqID){  
        assert(sp != NULL);	
        bool found;     
        int locn = search(sp, uniqID, &found);
	printf("ID being searched for: %d\n", uniqID);
        if (found){     
                printf("The ID was found.\n");
		printf("Student's age with ID: %d, %d\n", sp->students[locn]->age, sp->students[locn]->id);
		return sp->students[locn]->id;  
        }
       	else{
		printf("Could not find the ID you are looking for.\n");
        	return 0;
	}   
}

/*
 * Function: search
 *
 * Description: Searches for and assigns a position in the hash table
 * based on an id passed as an argument
 *
 * Handles collisions with linear probing and takes note of empty,
 * filled, and deleted spots
 *
 * Big-O: O(n)
 */
static int search(SET *sp, int uniqID, bool *found){
        assert(sp != NULL);
        int hashval = uniqID % 1009; 
        int i, j;
	int temp = -1;  
        *found = false; 
        for(i=0; i<sp->length; i++){
                j = (hashval + i) % 1009;
		if(sp->flags[j] == FILLED){
                        if(uniqID == sp->students[j]->id){
                                *found = true;
                                return j;
                        }
                }
		else if(sp->flags[j] == DELETED){
			if(temp == -1){
				temp = j;
			}
		}
		else if (sp->flags[j] == EMPTY){
			return j;
		}
	}
	return temp;
}

