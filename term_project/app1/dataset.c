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
 * Complexity: Functions have O(n) or O(1) 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "dataset.h"

typedef struct set{
        int count;
        int length;
       	LIST **lists;
}SET; 

struct list{
        int count;
        struct node *head;
};

struct node{
        int age;
        int id;
        struct node *next;
        struct node *prev;
};

static LIST *createList();

static void destroyList(LIST *lp);

static void addLast(LIST *lp, int uniqID, int newAge);

static void removeItems(LIST *lp);

/* 
 * Function: createDataSet
 *
 * Description: createSet creates a dataSet with 
 * count, length, and 13 empty linked lists
 */

SET *createDataSet(int maxElts){
	int i;
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->lists = malloc(sizeof(LIST*)*13);
	assert(sp->lists != NULL);
	for(i=0; i<13; i++){
		sp->lists[i] = createList();	
	}
	return sp;
}

/*
 * Function: destroyDataSet
 *
 * Description: destroys the data set
 * passed as an argument by freeing all
 * memory associated with it.
 */
void destroyDataSet(SET *sp){
        assert(sp != NULL);
        int i;
	for(i=0; i<13; i++){
		destroyList(sp->lists[i]);
	}
	free(sp);
}

/*
 * Function: insertion
 *
 * Description: a new "student" is added to one of 13 lists
 * based on their age, their id is assigned into the list as well
 * 
 * They are added to the end of their respective linked list.
 */
void insertion(SET *sp, int uniqID, int newAge){
        assert (sp != NULL && sp->count < sp->length);
	int i = newAge - 18;
	addLast(sp->lists[i], uniqID, newAge);
	sp->count++;    
        return;
}

/*
 * Function: deletion
 *
 * Description: Depending on the number, or "age", passed
 * the function will delete the data inside the linked list 
 * associated with that number.
 */
void deletion(SET *sp, int delAge){
        assert (sp != NULL);
	printf("The age group to be deleted: %d\n", delAge);
        if(searchAge(sp, delAge) == 1){
		int i = delAge - 18;
		int counter = 0;
		NODE *printNode = sp->lists[i]->head->next;
		printf("The IDs to be deleted from this age group are:\n");
		while(counter != sp->lists[i]->count){
			printf("%d\n",printNode->id);
			printNode = printNode->next;
			counter++;
		}
        	removeItems(sp->lists[i]);
		sp->lists[i]->count = 0;
		sp->lists[i]->head->next = sp->lists[i]->head;
		sp->lists[i]->head->prev = sp->lists[i]->head;
	}
}       	    

/*
 * Function: searchAge
 *
 * Description: returns whether the linked list associated
 * with the number passed as an argument is empty or has
 * data within it. 
 */
int searchAge(SET *sp, int findAge){
        assert(sp != NULL);
        int i  = findAge - 18;
        printf("The age list you are searching in: %d\n", findAge);
	if(sp->lists[i]->count > 0){
		return 1;
	}
	return 0;
}

/*
 * Function: maxAgeGap
 *
 * Description: returns the maximum age gap
 * between filled lists. 
 */

int maxAgeGap(SET *sp){
	assert(sp != NULL);
	int i; 
	int lo = 0;
	int hi = 12;
	while(sp->lists[lo]->count == 0){
			lo++;
	}
	while(sp->lists[hi]->count == 0){
			hi--;
	}
	int gap = hi - lo;
	printf("The Maximum Age Gap is: %d\n", gap);
	return gap;
}

//Private List Functions

/*
 * Function: createList
 *
 * Description: creates a linked list with a count, length
 * and head pointer(with links to next and prev)
 *
 * Big-O: O(1)
 */
static LIST *createList(){
        struct list *lp;
        lp = malloc(sizeof(struct list));
        assert(lp != NULL);
        lp->count = 0;
        lp->head = malloc(sizeof(struct node));
        assert(lp->head != NULL);
        lp->head->next = lp->head;
        lp->head->prev = lp->head;
        return lp;
}

/*
 * Function: destroyList
 *
 * Description: destroys a linked list, freeing data
 * in the process
 *
 * Big-O: O(n)
 */ 
static void destroyList(LIST *lp){
        assert(lp != NULL);
        NODE *pPrev;
        NODE *pDel = lp->head->prev;
        while(pDel != lp->head){
                pPrev = pDel->prev;
                free(pDel);
                pDel = pPrev;
        }
        free(pDel);
        free(lp);
}

/*
 * Function: addLast
 *
 * Description: assigns a new node an id and age
 * passed as an argument before inserting to the end
 * of the linked list
 *
 * Big-O: O(1)
 */
static void addLast(LIST *lp, int uniqID, int newAge){
        assert (lp != NULL);
        assert (lp->head != NULL);
        NODE *pLast;
        pLast = malloc(sizeof(struct node));
	assert(pLast != NULL);
        pLast->id = uniqID;
	pLast->age = newAge;
        pLast->prev = lp->head->prev;
        lp->head->prev->next = pLast;
        pLast->next = lp->head;
        lp->head->prev = pLast;
        lp->count++;
        return;

}

/*
 * Function: removeItems
 *
 * Description: frees all the data in linked list
 *
 * Big-O: O(n)
 */
static void removeItems(LIST *lp){
        assert (lp != NULL);
        assert (lp->head != NULL);
        NODE *pDel;
        pDel = lp->head->next;
        while(pDel != lp->head){
		lp->head->next = pDel->next;
                free(pDel);
                pDel = pDel->next;
		lp->count--;
        }
}

