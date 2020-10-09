
#include <iostream>


int main() {

	int aIntValue = 0;
	char aCharValue;

	std::cout << std::endl << "The value of the integer variable is " << aIntValue;

	const int NO_VALUES = 10;

	//initializing static arrays
	//1  - each element get the default 0xCC....
	// int values[NO_VALUES];

	//2 - set a default value only for the first, the rest are 0
	// int values[NO_VALUES] = { 10 };

	//3 - set each value to a specific one
	//int values[NO_VALUES] = { 1,2,3,4,5,6,7,8,9,10 };

	//4 - generate the values
	int values[NO_VALUES];
	for (int i = 0; i < NO_VALUES; i++) {
		values[i] = i * 10;
	}

	std::cout << std::endl << "The array is: ";
	for (int i = 0; i < NO_VALUES; i++) {
		std::cout << " " << values[i];
	}


	for (auto value : values) {
		std::cout << std::endl << " value =  " << value;
	}


	//changing values of variables by their name
	aCharValue = 'A';
	aIntValue = 200;

	//change values of variables by their address
	void *genericPointer;	//it gets the default 0xcccccccc
	genericPointer = 0;
	genericPointer = NULL;
	genericPointer = nullptr;

	int* pointer2Int = NULL;
	char* pointer2Char;

	//init the pointer with the address of a variable
	pointer2Int = &aIntValue;
	//change the variable using the pointer
	*pointer2Int = 400;

	std::cout << std::endl << "The pointer value (the addr) is " << pointer2Int;
	std::cout << std::endl << "The value at the addr given by the pointer " << *pointer2Int;
	std::cout << std::endl << "The value of the integer variable is " << aIntValue;

	//init a pointer with an address from HEAP
	pointer2Int = new int;		//ask for a single integer
								//in HEAP you get the default 0xCD for each byte

	std::cout << std::endl << "The pointer value (the addr) is " << pointer2Int;
	std::cout << std::endl << "The value at the addr given by the pointer " << *pointer2Int;

	// return 0
}