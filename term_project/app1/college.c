/*
 * File: college.c
 * 
 * Author: Alexandre Lopes
 * 
 * Date: 13 March 2022
 * 
 * Description: Creates an empty data set then generates 1000 students
 * with age and id fields. Then, the implementation inserts these students
 * into the data set. Then it picks an age between 18-30 and deletes all the
 * ids stored within that age group. Then it calculates the max age gap before
 * destroying itself
 * 
 * Complexity: O(n)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "dataset.h"

#define MAX_SIZE 3000

int main(){
        SET *studBody;
        studBody = createDataSet(MAX_SIZE);
        srand(time(NULL));
        int curID = 0;
        int i;
        for (i=0; i<1000; i++){
                int newAge = (rand()%13)+18;
                int newID = (rand()%2)+1;
                curID += newID;
                insertion(studBody, curID, newAge);
        }
        int delAge = (rand()%13)+18;
        deletion(studBody, delAge);
	maxAgeGap(studBody);
        destroyDataSet(studBody);
}

