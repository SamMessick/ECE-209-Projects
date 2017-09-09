#include <stdio.h>

char a, b, c; // Row 1
char d, e, f; // Row 2
char g, h, i; // Row 3

int playerCounter;
char playerType;
int playCounter;

void initializeBoard();
int playerMove(int input_position);
void printBoard();
char checkWin();

int main() {
  int position;
  char winner;
  while(1) {
    initializeBoard();
    while(playCounter < 9) {
      do{
        printf("Player %d, enter a position on the numpad: ", playerCounter%2+1);
        scanf("%d", &position);
      } while(!playerMove(position));
      printBoard();
      winner = checkWin();
      if(winner != '0') {
        for(playCounter = 0; playCounter < 10000; playCounter++)
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t||| %c Wins! |||\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", playerType);
        printf("\n\n__________________\n");
        printf("Play again? [y, n]\n");
        printf("__________________\n\n"); break;
      } else playerCounter++;
             playCounter++;
    }
    if(playCounter == 9) {
      printf("<><><><><>\n");
      printf("Catscratch\n");
      printf("<><><><><>\n\n");
      printf("__________________\n");
      printf("Play again? [y, n]\n");
      printf("__________________\n\n");
    }
    do{
      scanf(" %c", &playerType);
      playerType &= 0xFFDF;
      switch(playerType){
        case 'Y': position = 1; break;
        case 'N': position = 1; break;
        default: position = 0;
       }
    } while(!position);
    if(playerType == 'N') {
      printf("Goodbye\n\n");break;
    } else {
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nLet's go!\n\n");
    }
  }
}

void initializeBoard() {
  a = ' ',b = ' ',c = ' '; // Row 1
  d = ' ',e = ' ',f = ' '; // Row 2
  g = ' ',h = ' ',i = ' '; // Row 3
  playCounter = 0;
  playerCounter = 0;
}

int playerMove(int input_position) {
  if((playerCounter % 2) == 0) playerType = 'X';
  else playerType = 'O';

  switch(input_position) {
    case 7: if(a == ' '){
            a = playerType;
            return 1; } else return 0;
    case 8: if(b == ' ') {
            b = playerType;
            return 1; } else return 0;
    case 9: if(c == ' ') {
            c = playerType;
            return 1; } else return 0;
    case 4: if(d == ' ') {
            d = playerType;
            return 1; } else return 0;
    case 5: if(e == ' ') {
            e = playerType;
            return 1; } else return 0;
    case 6: if(f == ' ') {
            f = playerType;
            return 1; } else return 0;
    case 1: if(g == ' ') {
            g = playerType;
            return 1; } else return 0;
    case 2: if(h == ' ') {
            h = playerType;
            return 1; } else return 0;
    case 3: if(i == ' ') {
            i = playerType;
            return 1; } else return 0;
    default: printf("Invalid position\n");
            return 0;
  }
}

void printBoard() {
  printf("\n   |   |   \n");
  printf(" %c | %c | %c \n", a, b, c);
  printf("___|___|___\n");
  printf("   |   |   \n");
  printf(" %c | %c | %c \n", d, e, f);
  printf("___|___|___\n");
  printf("   |   |   \n");
  printf(" %c | %c | %c \n", g, h, i);
  printf("   |   |   \n\n");
}

char checkWin() {
  if((a == 'X' && b == 'X' && c == 'X') ||
     (a == 'X' && d == 'X' && g == 'X') ||
     (a == 'X' && e == 'X' && i == 'X') ||
     (b == 'X' && e == 'X' && h == 'X') ||
     (c == 'X' && f == 'X' && i == 'X') ||
     (c == 'X' && e == 'X' && g == 'X') ||
     (d == 'X' && e == 'X' && f == 'X') ||
     (g == 'X' && h == 'X' && i == 'X')) return 'X';
  else if((a == 'O' && b == 'O' && c == 'O') ||
          (a == 'O' && d == 'O' && g == 'O') ||
          (a == 'O' && e == 'O' && i == 'O') ||
          (b == 'O' && e == 'O' && h == 'O') ||
          (c == 'O' && f == 'O' && i == 'O') ||
          (c == 'O' && e == 'O' && g == 'O') ||
          (d == 'O' && e == 'O' && f == 'O') ||
          (g == 'O' && h == 'O' && i == 'O')) return 'O';
   else return '0';
}
