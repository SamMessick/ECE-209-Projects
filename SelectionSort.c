#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int items[], int size);

int main() {
  int i;
  int list[5000];
  srand(time(NULL));
  for(i = 0; i < 5000; i++) {
    list[i] = rand() % 10000;
  }
  selectionSort(list, 5000);
  for(i = 0; i < 5000; i++) {
    printf("%d\n", list[i]);
  }
}

void selectionSort(int items[], int size) {
  int i;
  int j;
  int *min;
  int temp;
  for(i = 0; i < size - 1; i++) {
    min = &items[i];
    for(j = i + 1; j < size; j++)
      if(*min > items[j])
        min = &items[j];
      temp = items[i];
      items[i] = *min;
      *min = temp;
  }
}
