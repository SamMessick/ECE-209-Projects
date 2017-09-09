/***********************************************************
  Last Edited: 5/11/2017
  Author: Sam Messick

  This program receives an unsigned integer input and
  calculates two sequential values of the Fibonacci Sequence
  using its closed form. It then calculates an estimation of
  the golden ratio using the two values
 ***********************************************************/

#include <stdio.h>
#include <math.h>

int recursiveForm(int n);

int main() {
  int input; //input value used in calculation

  /*Prompt the user for an integer input:
    input determines term position
    in the Fibonacci Sequence*/
  printf("\n///////////////////////////////////////\nWelcome to the golden ratio calculator\n///////////////////////////////////////\n\nPlease enter an integer greater than 0 that you\nwould like to use in your calculation: ");
  scanf("%d", &input);

  int n = input;

  double closed_numerator = (double) (sqrt(5)/5)*(pow((1+sqrt(5))/2, n) - pow((1-sqrt(5))/2, n));
  double closed_denominator = (double) (sqrt(5)/5)*(pow((1+sqrt(5))/2, n-1) - pow((1-sqrt(5))/2, n-1));
  double phi = (double) closed_numerator/closed_denominator;

  printf("\n\n%1.16f", phi);

  int recursive_numerator = recursiveForm(n);
  int recursive_denominator = recursiveForm(n-1);
  double phi_recursive = (double) recursive_numerator/recursive_denominator;

  printf("\n\n%1.16f\n\n", phi_recursive);
}

int recursiveForm(int n) {
  if(n == 1 || n == 2) return 1;
  return (recursiveForm(n-1) + recursiveForm(n-2));
}
