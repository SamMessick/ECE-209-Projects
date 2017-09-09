/* This is a test to learn how to
   manipulate files in c. A random
   number generator is also linked
   to my math header file         */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrixOps.h"
#define LIMIT 10000

void writeRandomFile(int word_count, int min_num, int max_num);
void scanIn(FILE *file, int readingOutput[]);
//extern void InsertionSort(int list[]);

/*int main() {
  int low_num = 0;
  int high_num = 100;
  int word_count = MAX_NUMS;
  int storage[MAX_NUMS];
  int index;
  FILE *file;
  file = fopen("C:\\users\\shmes\\Desktop\\Escritorio Personal\\Escuela\\ECE\\209\\file.txt", "w");

  writeRandomFile(word_count, low_num, high_num);
  scanIn(file, storage);

  //InsertionSort(storage);

  printf("\n__________________________________\n");
  printf("The input set, in ascending order: ");
  printf("\n__________________________________\n\n");
  for(index = 0; index < MAX_NUMS; index++) {
    printf("%d\n", storage[index]);
  }

}*/

int random_number(int min_num, int max_num) {
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }
    result = (rand() % (hi_num - low_num + 1)) + low_num;
    return result;
}

void writeRandomFile(int word_count, int min_num, int max_num) {
  FILE *file;
  file = fopen("C:\\users\\shmes\\Desktop\\Escritorio Personal\\Escuela\\ECE\\209\\file.txt", "w");
  if(&file == NULL) {
    printf("Invalid file input!\n");
    return;
  }

  int index; // Index for reading in random numbers to string
  srand(time(NULL));
  int x[word_count];

  for(index= 0; index < word_count; index++) {
    x[index] = random_number(0, 100);
  }

  fwrite(x, sizeof(x[0]), sizeof(x)/sizeof(x[0]), file);
  fclose(file);

}

void scanIn(FILE *file, int readingOutput[]) {
  int index;
  int i = 0;
  int j = 0;
  int numbers[LIMIT];

  while((fscanf(file, "%d", &numbers[i]) != EOF) && i < LIMIT) {
    if(numbers[i] != ' ') {
      readingOutput[j] = numbers[i];
      j++;
    }
  }
}
