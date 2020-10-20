#include <iostream>
using namespace std;


int increment(int theInteger);
void increment2(int* theInteger);
void increment3(int& theInteger);

int main() {
	//remember the variables are stored on the function Stack
	const int constValue = 100;
	char aChar = 'a';
	int aInt = 23;
	int array[] = { 10,20,30,40,50 };


	cout << endl << "The 3rd value in array is " << array[2];

	//the challenge
	//get the address of aChar
	char* pointer = &aChar;

	//using cast to (void*) because char* is always seen as a string
	cout << endl << "The address of aChar in memory " << (void*)&aChar;
	cout << endl << "The address of aInt in memory " << &aInt;
	//the bname of the array variable is always the pointer to the 1st element
	// array <-> &array[0]
	cout << endl << "The address of array in memory " << array;

	//0058FA77 aChar
	//0058FA68 aInt
	//0058FA4C array

	int* firstElementAdr = array;
	//int* firstElementAdr = &(array[0]);
	
	//move to the beggining of 3rd
	//addr = addr + n*sizeof(type)
	
	//firstElementAdr+=8	//firstElementAdr = firstElementAdr + 8 * sizeof(int)

	int* thirdElemAddr = firstElementAdr + 2;

	//change its value
	*thirdElemAddr = 100;


	cout << endl << "The 3rd value in array is " << array[2];

	//change it again to 200 using the address of aChar
	//we determined that the aInt variable is at 15 bytes before aChar
	int* pointer2Int = (int*)(pointer - 15);

	//change the int
	*pointer2Int = 999;

	cout << endl << "The int variable value is " << aInt;


	thirdElemAddr = (int*)(pointer - 43 + 8);
	*thirdElemAddr = 555;
	
	cout << endl << "The 3rd value in array is " << array[2];

	//trying to change a constant variable
	const int* pointer2Constant = &constValue;

	//constValue = 33;
	//*pointer2Constant = 33;

	cout << endl << "The addr of the constant variable is " << pointer2Constant;
	cout << endl << "The value of the constant variable is " << constValue;

	int* newPointer = (int*)(pointer + 6);
	//*newPointer = 33;		//run time exception - Windows is protecting the const

	cout << endl << "The value of the constant variable is " << constValue;


	//use increment
	cout << endl << "The value of the int variable is " << aInt;

	aInt = increment(aInt);

	cout << endl << "The value of the int variable is " << aInt;

	increment2(&aInt);

	cout << endl << "The value of the int variable is " << aInt;

	increment3(aInt);

	cout << endl << "The value of the int variable is " << aInt;
}

//a function that changes the value of the 3rd element in the array
void change3rdValue(int* array, int n, int newValue) {
	if (n < 3) {
		cout << endl << "The 3rd does not exist";
	}
	else {
		array[2] = newValue;
	}
}

//a function that increments the value of a given integer
int increment(int theInteger) {
	theInteger += 1;
	return theInteger;
}

void increment2(int* theInteger) {
	(*theInteger) += 1;
}

void increment3(int & theInteger) {
	theInteger += 1;
}