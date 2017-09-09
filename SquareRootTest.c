#include <stdio.h>

double squareRoot(double input);

int main() {
  double fun;
  double answer;
  while(1){
  scanf("%lf", &fun);
  answer = squareRoot(fun);
  printf("%.3lf\n", answer);
  }
}

double squareRoot(double input) {
  if(input == 1 || input == 0) return input;
  if(input < 0) {
    printf("Invalid input\n"); return 0;
  }
  double offset = 1000;
  int count = 0;
  int comparison = input;
  input /= 2;
  if((input * input) == comparison) return input;
  while(offset > .00005) {
    offset /= 2;
    input += offset;
    offset /= 5;
    while((input*input) > comparison) {
      if(input - offset < 0) break;
      input -= offset;
      if((input*input) == comparison) return input;
    }
    while((input*input) < comparison) {
      input += offset;
      if((input*input) == comparison) return input;
    }
  }
  return input;
}
