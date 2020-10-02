#include <stdio.h>

void main() {
	printf("\n Hello World");
	char aTestCharVariable = 'a'; 
	printf("\n The value is %c", aTestCharVariable);
	printf("\n The value is %d", aTestCharVariable);
	printf("\n The value is %x", aTestCharVariable);

	//aTestCharVariable = 'b';
	aTestCharVariable += 1;

	printf("\n The value is %c", aTestCharVariable);
	aTestCharVariable -= 32;
	printf("\n The value is %c", aTestCharVariable);

	aTestCharVariable += ('b' - 'B');
	printf("\n The value is %c", aTestCharVariable);

	const int NO_ELEMENTS = 10;
	int someNumbers[NO_ELEMENTS];
	printf("\n The array is :");
	for (int i = 0; i < NO_ELEMENTS; i++) {
		printf(" %d", someNumbers[i]);
	}

}