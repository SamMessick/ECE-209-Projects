/***********************************************************
  Last Edited: 5/11/2017
  Author: Sam Messick

  This program outputs a simple product table with
  all combinations of two input values from 1-12
 **********************************************************/

#include <stdio.h>

int main() {
  int tableOfProducts[12][12];
  printf("\n");                     //add filler line

  for(int i = 0; i < 12; i++) {
    for(int j = 0; j < 12; j++) {
      mult[i][j] = (i+1)*(j+1);     //calculate multiple of incremented indices
      printf("%4.0d", mult[i][j]);  //print calculated member
    }
    printf("\n");                   //begin new row
  }
}
