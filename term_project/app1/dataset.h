/*
 * File: dataset.h
 * 
 * Author: Alexandre Lopes
 *     
 * Date: 13 March 2022
 *       
 * Description: Declarations of the public functions used in college.c
 * Data structures are also declared here.
 *          
 * Complexity: Functions have O(n) or O(1) 
 */


# ifndef DATASET_H
# define DATASET_H

typedef struct set SET;

typedef struct list LIST;

typedef struct node NODE;

SET *createDataSet();

void destroyDataSet(SET *sp);

void insertion(SET *sp, int uniqID, int newAge);

void deletion(SET *sp, int delAge);

int searchAge(SET *sp, int findAge);

int maxAgeGap(SET *sp);
# endif /* SET_H */

