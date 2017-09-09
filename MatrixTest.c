#include "matrixOps.h"

int main() {
  int a[20][3] = {{15, 6, 3},
                  {15, 6, 0},
                  {15, 6, 3},
                  {15, 6, 3},
                  {15, 6, 3},
                  {66, 6, 3},
                  {15, 6, 9},
                  {15, 5, 3},
                  {15, 6, 3},
                  {15, 6, 3},
                  {15, 6, 3},
                  {15, 1, 7},
                  {15, 6, 3},
                  {15, 6, 3},
                  {15, 9, 3},
                  {15, 0, 3},
                  {15, 6, 1},
                  {15, 6, 3},
                  {15, 4, 3},
                  {15, 6, 2}};
  int b[3][7] = {{6, 4, 3, 2, 1, 2, 7},
                 {3, 7, 5, 7, 6, 3, 4},
                 {3, 7, 5, 7, 6, 9, 2}};
  matrixMult(20, 3, 3, 7, a, b);
}

void matrixMult(int x_a, int y_a, int x_b, int y_b, int a[x_a][y_a], int b[x_b][y_b]) {
    if(y_a != x_b) printf("Invalid operation");
    int overflow_check = y_b; //y_b
    int temp = 0;
    int c[x_a][y_b];
    for(int i = 0; i < x_a ; i++) { //x_a
      for(int j = 0; j < y_b; j++) { //y_a
        for(int k = 0; k < y_a; k++) { //y_a
          temp += a[i][k] * b[k][j % overflow_check];
          //printf("%d += a[%d][%d] * b[%d][%d]\n\n", temp, i, k, k, j);
        }
        c[i][j] = temp;
         temp = 0;
      }
    }
    for(int i = 0; i < x_a; i++) {
      printf("[");
      for(int j = 0; j < y_b; j++) {
        printf("%4d ", c[i][j]);
      }
      printf("]\n");
    }
