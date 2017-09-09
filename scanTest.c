#include <stdio.h>

int main()
{
  int input;
  int earlier = 0;
  int later = 0;
  int tempLater;
  int status;
  int earlierFlag = 1;
  while(1) {
  status = scanf("%d", &input);
    if(status == 1) {
      if(earlierFlag) {
        later = input;
        earlierFlag -= 1;
        printf("*earlier is: %d; later is: %d\n", earlier, later);
        printf("%d\n", earlier);
      } else {
        tempLater = later;
        later = input;
        earlier = tempLater;
        printf("earlier is: %d; later is: %d\n", earlier, later);
      }
    } else {
        scanf("%c", &input);
        printf("Your input was: %c\n", input);
    }
  }
}
