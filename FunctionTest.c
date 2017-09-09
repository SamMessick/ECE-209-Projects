#include <stdio.h>

void PrintBanner();
void factorial(int n);
/*int[][] matrixMult(int a[int x_a][int y_a], int b[int x_b][int y_b]);
void displayMatrix(int x, int y, int a[x][y]);*/

int main() {
  PrintBanner();
  int number;

  printf("Input a number");
  scanf("%d", &number);

  factorial(number);
  int overflow_check = 5; //y_b
  int temp = 0;

  int a[5][7] = {{15, 6, 3, 2, 6, 2, 1},
                 {15, 6, 3, 2, 6, 4, 2},
                 {15, 6, 3, 2, 3, 2, 6},
                 {15, 6, 3, 2, 3, 2, 6},
                 {15, 6, 3, 2, 3, 2, 6}};
  int b[7][5] = {{6, 4, 3, 2, 1},
                 {3, 7, 5, 7, 6},
                 {3, 7, 5, 7, 6},
                 {3, 7, 5, 7, 6},
                 {3, 7, 5, 7, 6},
                 {3, 7, 5, 7, 6},
                 {3, 7, 5, 7, 6}};
  int c[5][5]; //final dimensions
  for(int i = 0; i < 5 ; i++) { //x_a
    for(int j = 0; j < 5; j++) { //y_a
      for(int k = 0; k < 7; k++) { //y_a
        temp += a[i][k] * b[k][j % overflow_check];
        //printf("%d += a[%d][%d] * b[%d][%d]\n\n", temp, i, k, k, j);
      }
      c[i][j] = temp;
      temp = 0;
    }
  }
  for(int i = 0; i < 5; i++) {  //x
    printf("[");
    for(int j = 0; j < 5; j++) {  //y
      printf("%8d  ", c[i][j]);
    }
    printf("]\n");
  }
}

void PrintBanner() {
  printf("So yeah.");
}

void factorial(int n) {
  int result = 1;

  for(int i = 1; i <= n; i++) {
    result = result * i;
    printf("\n%d", result);
  }
  printf("\n\nThe factorial is %d\n", result);
}

/*int[][] matrixMult(int x_a, int y_a, int x_b, int y_b, int a[x_a][y_a], int b[x_b][y_b]) {
  int c[1][1];
  int overflow_check = y_b + 1;
  int temp;
  c[0][0] = 0;
  if(y_a != x_b) return c;
  else {
      for(int i = 0; i < x_a ; i++) {
        for(int j = 0; j < y_a; j++) {
          for(int k = 0; k < y_a; k++) {
            temp += a[i][k] * b[k][i % overflow_check];
          }
          a[i][j] = temp;
        }
      }
  }
  return a;
}

void displayMatrix(int x, int y, int a[x][y]) {

  for(int i = 0; i < x; i++) {
    printf("[");
    for(int j = 0; j < y; j++) {
      printf("%3d", a[i][j]);
    }
    printf("]");
  }
}*/
