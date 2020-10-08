#include <iostream>
using namespace std;

void aFunction();

int main() {

	//pointers
	char aCharVariable = 'a';
	short int aShortInt = 100;
	char aShorterInt = 15;
	int aIntVariable = 60;
	char local1;
	short int local2;
	int values[3];

	//defining a pointer
	//a pointer is a variable that stores numbers which are always addresses
	void * justAPOinter;
	justAPOinter = (void*)100;	//does not make any sense - only for hackers

	//copy the pointer value into a int - 100
	aIntVariable = (int)justAPOinter;	
	//copy the int value which is in RAM at address 100
	aIntVariable = *((int*)justAPOinter); 

	cout << endl << "The value of aIntVariable is " << aIntVariable;

	//copy the int value from memory from the justAPOinter address
	//aIntVariable = *((int*)justAPOinter);
	//aCharVariable = *((char*)justAPOinter);


	short int *pointerLocal2;
	char *pointerLocal1;

	pointerLocal2 = &local2;
	pointerLocal1 = &local1;

	//local2 = 99;
	//using the pointer
	*pointerLocal2 = 99;

	cout << endl << "The value of local2 is " << local2;
	cout << endl << "The value of local2 is " << *(&local2);
	cout << endl << "The value of local2 is " << *(pointerLocal2);


	//init local 1 by using the address of local 2
	//we know the difference in terms of addresses if F bytes
	//pointerLocal2 += 15; jumps 30 bytes because 15*short int size

	char* thePointer = (char*)pointerLocal2;
	thePointer += 15;
	*thePointer = 'X';

	cout << endl << "The value of local1 is " << local1;

	aFunction();

	std::cout << "The END";

	//return 0;
}


void aFunction() {
	int local1;
	int local2;

}