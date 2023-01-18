/*
 * File: dataset.h
 * 
 * Author: Alexandre Lopes
 * 
 * Date: 13 March 2022
 * 
 * Description: Declaration of public functions and
 * data structures to be used in college.c
 * 
 * Complexity: Functions have O(n) 
 */

# ifndef DATASET_H
# define DATASET_H

typedef struct node NODE;

typedef struct set SET;

SET *createDataSet(int maxElts);

void destroyDataSet(SET *sp);

void insertion(SET *sp, int uniqID, int findAge);

void deletion(SET *sp, int uniqID);

int searchID(SET *sp, int uniqID);

# endif /* DATASET_H */
