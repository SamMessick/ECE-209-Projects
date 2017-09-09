#include <stdio.h>

int main() {
	int n;
	int ka = 1;
	printf("Please enter an odd, positive integer: ");
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i; j++) {
			printf("*");
		} printf("\n");
	} printf("\n\n");

	//MORE interesting loop with vertical symmetry :)

	for(int i = (n/2); i >=0 ; i--) { //number of rows
		for(int j = 0; j < i; j++) {
			printf(" "); 
		}
		for(int k = 0; k < ka; k++) {
			printf("*");
		}
		ka += 2;
		for(int j = 0; j < i; j++) {
			printf(" ");
			if(j == (i - 1)) printf("\n");
		}
	}
	for(;;) {
		printf("|:)|");
	}	
	return 0;
}
