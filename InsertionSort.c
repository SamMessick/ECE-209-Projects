/* Program Courtesy of Introduction to
   Computing Systems textbook, pg 448

   This program sorts a list of integers
   in order of increasing magnitude using
   insertion sort.

   Last Modified: May 5, 2017       */

#include <stdio.h>
#include "matrixOps.h"
#include <time.h>

void InsertionSort(int list[], int *counter);

int main() {
  clock_t begin = clock();
  int index;              // Iteration variable
  int numbers[MAX_NUMS];  // List of numbers to be sorted
  int arrayCounter = 0;       // Counts number of comparisons
  int low = 0;
  int high = 100000;

  /* Get Input */
    printf("__________________________________________________\n");
    printf("Enter %d numbers to be sorted with insertion sort.\n", MAX_NUMS);
    printf("__________________________________________________\n");
  for(index = 0; index < MAX_NUMS; index++) {
    //printf("\nInput number %d: ", index);
    //scanf("%d", &numbers[index]);
    numbers[index] = random_number(low, high);
  }

  InsertionSort(numbers, &arrayCounter);

  clock_t end = clock();
  double execution_time = (double) (end - begin) / CLOCKS_PER_SEC;
  /* Print sorted list */
  printf("\n__________________________________\n");
  printf("The input set, in ascending order: ");
  printf("\n__________________________________\n\n");

  printf("-------\n");
  for(index = 0; index < MAX_NUMS; index++) {
    printf("|%5d|\n", numbers[index]);
  }
  printf("-------\n\n");
  printf("%d comparisons were made.\n", arrayCounter);
  printf("Sorting time: %lf", execution_time);
}

void InsertionSort(int list[], int *counter) {

  int unsorted;         // Index for unsorted item
  int sorted;           // Index for sorted items
  int unsortedItem;     // Current item to be sorted

  /* This loop iterates from 1 thru MAX_NUMS */
  for(unsorted = 1; unsorted < MAX_NUMS; unsorted++) {
    unsortedItem = list[unsorted];

    /* This loop iterates from unsorted thru 0, unless
       we hit an element smaller than current item */
    for(sorted = unsorted -1; (sorted >=0) && (list[sorted] > unsortedItem);
        sorted--) {
        list[sorted + 1] = list[sorted];
        *counter += 1;
      }

    list[sorted + 1] = unsortedItem; // Insert item
  }
}
