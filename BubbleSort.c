/* This Program is an implementation
  of the bubble sort algorithm. It
  searches a list of integers of
  specified size by comparing each object
  to its neighbor until the entire list
   is sorted in order of increasing magnitude.

   Author: Sam Messick
   Last Modified: May 24, 2017                */

#include <stdio.h>
#include "matrixOps.h"
#include <time.h>

void bubbleSort(int list[], int *counter);

int main()
{
  clock_t begin = clock();
  int index;        // Index in "for" statements
  int sortingStack[MAX_NUMS];
  int arrayCounter = 0;
  int low = 0;
  int high = 100000;

  printf("_______________________________________________\n");
  printf("Enter %d numbers to be sorted with bubble sort.\n", MAX_NUMS);
  printf("_______________________________________________\n");

  /* Recieve input numbers to be sorted */
  for(index = 0; index < MAX_NUMS; index++) {
    //printf("Number %d: \n", index + 1);
    //scanf("%d", &sortingStack[index]);
    sortingStack[index] = random_number(low, high);
  }

  /* Verifies that bubble sort is necessary and complete */
  for(index = 0; index < MAX_NUMS -1; index++) {
      bubbleSort(sortingStack, &arrayCounter);
  }

  clock_t end = clock();
  double execution_time = (double) (end - begin) / CLOCKS_PER_SEC;

  /* Print sorted list */
  printf("\n__________________________________\n");
  printf("The input set, in ascending order: ");
  printf("\n__________________________________\n\n");
  printf("-------\n");

  for(index = 0; index < MAX_NUMS; index++) {
    printf("|%5d|\n", sortingStack[index]);
  }
  printf("-------\n\n");
  printf("%d comparisons were made.\n", arrayCounter);
  printf("Sorting time: %lf", execution_time);
}

void bubbleSort(int list[], int *counter)
{
  int temp;         // Storage for the first compared value
  int comparison;   // Counter for loop

  for(comparison = 0; comparison < MAX_NUMS - 1; comparison++) {
    temp = list[comparison];
    *counter += 1;
    if(list[comparison] > list[comparison + 1]) {
      list[comparison] = list[comparison + 1];
      list[comparison + 1] = temp;
    } else continue;
  }
}
