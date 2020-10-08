#include <iostream>

int main() {

	int someValue;
	char someChar;

	const int NO_VALUES = 10;
	//int values[NO_VALUES] = { 0 };	//all values equal to 0
	int values[NO_VALUES] = { 1,2,3,4,5,6,7,8,9,10 };	//assign a value to each element

	std::cout << std::endl << "The array is :";
	for (int i = 0; i < NO_VALUES; i++) {
		std::cout << " " << values[i];
	}

	//manage variables with pointers
	char* pointer2Char;		//default to 0xCCCCCCCC because of ...
	//init a pointer
	//init it with a number - because they are numeric variables
	//pointer2Char = (char*)100;		//init with the address 100 - somewhere in RAM

	//init it with an address of a variable
	pointer2Char = &someChar;

	*pointer2Char = 'X';

	//init it with an address of a variable that we create Heap
	//in C we had: void * malloc(how_many_bytes)
	pointer2Char = new char;

	//use pointers to write values at those addresses
	*pointer2Char = 'A';

	someValue = 60;
	*(&someValue) = 60;

	//use pointers to read values from addresses

	std::cout << std::endl << "The value of the Heap char is " << *pointer2Char;


	//create an array of integers in Heap
	int* newArray = new int[NO_VALUES];
	//create a single integer in Heap
	int* newInt = new int;

	//delete space
	// everything which was created with brackets [] is deleted with brackets
	delete[] newArray;

	// everything which was created without brackets is deleted without brackets
	delete newInt;


	//manage the array
	//change the 2nd value in the array
	values[1] = 99;

	//change the 3rd value in the array
	*(values + 2) = 200;

	//get the address of someValue
	int* pointerToValue = &someValue;


	//challenge
	//try to change the 4th value in value using pointerToValue

	std::cout << std::endl << "The array is :";
	for (int i = 0; i < NO_VALUES; i++) {
		std::cout << " " << values[i];
	}


	std::cout << std::endl << "The end";
}