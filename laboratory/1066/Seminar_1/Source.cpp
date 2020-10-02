
#include <stdio.h> 

void main() {

	char aCharToPlayWith = 'a';

	printf("\n Hello World !");

	printf("\n The char value is %c", aCharToPlayWith);
	printf("\n The char value is %d", aCharToPlayWith);
	printf("\n The char value is %x", aCharToPlayWith);

	// aCharToPlayWith = 'b';

	aCharToPlayWith += 1;
	printf("\n The char value is %c", aCharToPlayWith);

	aCharToPlayWith -= 32;
	printf("\n The char value is %c", aCharToPlayWith);


	//int justAValue = 10;
	int justAValue = 0xA;	//in hexadecimal

	const int NO_ELEMENTS = 10;
	int numbers[NO_ELEMENTS];

	printf("\n The numbers are :");
	for (int i = 0; i < NO_ELEMENTS; i++) {
		printf(" %d", numbers[i]);
	}


}
