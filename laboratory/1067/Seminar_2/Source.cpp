
#include <iostream>
#define ARRAY_SIZE 10

int main() {

	int aIntValue;
	char aCharValue;

	const int NO_VALUES = 10;

	//version 1 - it has the 0xCCCCCCCC default value for all elements
	//int values[NO_VALUES];

	//version 2
	//int values[NO_VALUES] = { 0 }; //all elements get 0
	
	//version 3 - pass all values
	int values[NO_VALUES] = { 1,2,3,4,5,6,7,8,9,10 };
	
	//version 4 - generate the values 
	//int values[NO_VALUES];
	//for (int i = 0; i < NO_VALUES; i++) {
	//	values[i] = i * 10;
	//}

	std::cout << std::endl << "The array is: ";
	for (int i = 0; i < NO_VALUES; i++) {
		std::cout << " " << values[i];
	}

	//init variable directly 
	aIntValue = 100;

	//manage variables by pointers
	int* pointer2Int;

	//init the pointer with a value - pointing to nowhere
	pointer2Int = 0;
	pointer2Int = NULL;
	pointer2Int = nullptr;

	//init the pointer with the addr of an existing variable
	pointer2Int = &aIntValue;

	//change the aIntValue variable 
	//by its name
	aIntValue = 99;

	//by its address
	*(&aIntValue) = 60;
	*pointer2Int = 60;

	std::cout << std::endl << "The int variable value is " << aIntValue;
	std::cout << std::endl << "The value of the pointer (the addr) " << pointer2Int;
	std::cout << std::endl << "The value at the pointer addr is " << *pointer2Int;

	//init the pointer with the address of something - in HEAP
	pointer2Int = new int; //creating an integer in HEAP

	//change the value frmo HEAP
	*pointer2Int = 200;

	std::cout << std::endl << "The value of the pointer (the addr) " << pointer2Int;
	std::cout << std::endl << "The value at the pointer addr is " << *pointer2Int;

	//release the HEAP memory
	delete pointer2Int;

	// return 0
}