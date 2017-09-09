/*

ECE 209 Section 051

This program implements a calculator
application that allows a user to
compute binary operations (multiplication,
addition, subtraction, division, exponentiation),
manipulate or output input memory and
compute square roots.

Author: Sam Messick
Last Modified: June 9, 2017

*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#define SQRT_PRECISION .0001 /* Zeroes correspond to accurate positions in squareRoot()
                                return value */

void swapNums(double *first, double *second);   // Swaps memory location of first and second
void printNums(double first, double second);    // Prints first and second
double squareRoot(double input);                /* Returns the square root of
                                                   input */

int main()
{
  double earlier = 0.0;    // Earlier of two input operands
  double later = 0.0;      // Later of two input operands
  double tempLater;        // Storage for updating earlier memory operand
  double input;            // Double input storage
  char operator;           // Character input storage
  int status;              // Status variable of double scanf() [0, -1 or 1]

    while(operator != 'q' /* Quit status */) {

    status = scanf("%lf", &input);  // Check for double operand

    if(status == 1 /* Double input */) {
      tempLater = later;
      later = input;                // Update input memory values
      earlier = tempLater;
    } else {
      scanf("%c", &operator);       // Check for character operator

      if(operator == 0xA || operator == 0x2B || operator == 0x2D) {
        printf("Operator not supported.\n");  // Check for +,-,. misnomers
        continue;
      if(EOF == scanf("%c", &operator)) continue;   // Check for EOF in CodeLab
      }
        /* Verify Operator */
        switch(operator) {
          // Multiply operands
          case 'x': later *= earlier;
                    printf("= %.3lf\n", later); break;

          // Divide operands
          case 'd': if(earlier == 0) {
                      printf("Divide by zero error\n");
                      break;
                    } else {
                      later /= earlier;
                      printf("= %.3lf\n", later); break;
                    }

          // Add operands
          case 'a': later += earlier;
                    printf("= %.3lf\n", later); break;

          // Subtract operands
          case 's': later -= earlier;
                    printf("= %.3lf\n", later); break;

          // Exponentiate later operand
          case '^': later = pow(later, earlier);
                    printf("= %.3lf\n", later); break;

          // Square root of later operand
          case 'r': if(later < 0) {
                      printf("Complex root\n"); break;
                    }
                    later = squareRoot(later);
                    printf("= %.3lf\n", later); break;

          // Swap operands
          case 'w': swapNums(&later, &earlier); break;

          // Clear operands
          case 'c': earlier = 0;
                    later = 0; break;

          // Print operands
          case 'p': printNums(earlier, later); break;

          // Print help document
          case 'h': printf("\n///////////////////////////////////////////////////////////////////////////\n");
                    printf("Welcome to the ECE 209 calculator!\n");
                    printf("This calculator accepts double operands.\n");
                    printf("Support includes: x (multiply), d (divide), a (add), s (subtract), r (root)\n");
                    printf("Escape sequences include w (swap), p (print), c (clear), q (quit)\n\n");
                    printf("This program holds memory for the penultimate and last input double\n");
                    printf("numbers by the user, originally set to 0.\n");
                    printf("///////////////////////////////////////////////////////////////////////////\n\n");

                    printf("Operations: \n");
                    printf("-=-=-=-=-=-\n");
                    printf("_________________________________________________________\n");
                    printf("\'a\': Adds penultimate input to last input.               |\n");
                    printf("     Sum is stored in 'last' input variable.             |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'s\': Subtracts penultimate input from last input.        |\n");
                    printf("     Difference is stored in 'last' input variable.      |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'x\': Multiplies penultimate input by last input.         |\n");
                    printf("     Product is stored in 'last' input variable.         |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'d\': Divides last input by penultimate input.            |\n");
                    printf("     Quotient is stored in 'last' input variable.        |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'^\': Raises last input to penultimate input power.       |\n");
                    printf("     Result is stored in 'last' input variable.          |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'r\': Approximates the square root of last input.         |\n");
                    printf("     Result is stored in 'last' input variable.          |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'w\': Swap penultimate and last input. The memory         |\n");
                    printf("     locations of the inputs are swapped.                |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'c\': Clear penultimate and last input variables to 0.    |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'p\': Print penultimate input followed by last input.     |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'h\': Print help documentation                            |\n");
                    printf("---------------------------------------------------------|\n");
                    printf("\'q\': Print penultimate input followed by last input,     |\n");
                    printf("     and quit program.                                   |\n");
                    printf("_________________________________________________________|\n\n");
                    printf("Example inputs: <double>[ENTER]<double>[ENTER]<operator>[ENTER]\n");
                    printf("                <double>[ENTER]<operator>[ENTER]\n");
                    printf("                <operator>[ENTER]\n\n");
                    break;

          // Quit program; while condition is invalid
          case 'q': break;

          // Invalid input
          default: printf("The operator %c is not supported.\n", operator); break;
        }
    }
  }
  /* Quit procedure */

  printNums(earlier, later);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Function Definitions:
////////////////////////////////////////////////////////////////////////////////

void swapNums(double *first, double *second) {
  double temp = *second;                          // Storage for updating earlier memory operand
  *second = *first;                               // Swap input memory values
  *first = temp;
}

void printNums(double first, double second) {
  printf("%.3lf\n", first);
  printf("%.3lf\n", second);
}

/* The algorithm subtracts and adds decreasing */
/* offsets to obtain an accurate square root to*/
/* 3 decimal points.                           */
double squareRoot(double input) {
  double offset = 1e127;                          // Initial difference value
  double comparison = input;                      // Saves original value for comparison
  input /= 2;                                     // Divide input by two
  if((input * input) == comparison) {             // Check if valid root
    return input; // Check if valid root
  }
  while(offset > SQRT_PRECISION) {                // Repeat until all bits are precise
    offset /= 2;
    if(input - offset > 0) input -= offset;
    offset /= 5;
    while((input * input) > comparison) {         // Case: input > root
      if(input - offset < 0) break;
      input -= offset;
      if((input * input) == comparison) {         // Check if valid root
        return input;
      }
    }
    while((input * input) < comparison) {         // Case: input < root
      input += offset;
      if((input * input) == comparison) {         // Check if valid root
        return input;
      }
    }
  }
  return input; /* Worst case scenario; Theta(n);
                   Asymptotic runtime is roughly
                   proportional to ciel(n/1e127) */
}
