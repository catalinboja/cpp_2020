
#include <iostream>
#include <stdio.h>
//it's optional
using namespace std;

int main() {

	//use the mixed Camel Case
	// noOfStudents
	char aCharVariable = 'a';	//in memory "a" is "a\0"

	std::cout << std::endl << "The char value is " << aCharVariable;
	printf("\n The char value is %d", aCharVariable);
	printf("\n The char value is %x", aCharVariable);

	//change it to 'b'
	aCharVariable += 1;
	cout << endl << "The char value is " << aCharVariable;
	//change it to 'B'
	aCharVariable -= 32;
	cout << endl << "The char value is " << aCharVariable;

	//arrays
	const int NO_VALUES = 10;
	int someValues[NO_VALUES];

	//init them with 0
	for (int i = 0; i < NO_VALUES; i++) {
		someValues[i] = 0;
	}

	cout << endl << "The array is: ";
	for (int i = 0; i < NO_VALUES; i++) {
		cout << " " << someValues[i];
	}

	//IT'S NOT CORRECT - because the array is static
	//add a new value to the array
	someValues[NO_VALUES] = 90;
	someValues[NO_VALUES+1] = 100;
	//NO_VALUES += 1;
	int newNoValues = NO_VALUES + 2;

	cout << endl << "The array is: ";
	for (int i = 0; i < newNoValues; i++) {
		cout << " " << someValues[i];
	}
}