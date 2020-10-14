#include <iostream>
using namespace std;

int main() {

	int aIntValue = 0;
	char aCharVariable = 48;	//is '0'

	const int NO_VALUES = 5;

	//1. all values  = 0xCCCC..CC
	//int values[NO_VALUES];

	//2. set partial values - the rest are 0
	//int values[NO_VALUES] = { 1,2 };

	//3. set all values
	//int values[NO_VALUES] = { 1,2,3,4,5 };

	//4. generate values
	int values[NO_VALUES];
	for (int i = 0; i < NO_VALUES; i++) {
		values[i] = i * 2;
	}


	cout << endl << "The array is :";
	for (int i = 0; i < NO_VALUES; i += 1 ) {
		cout << " " << values[i];
	}


	int* pointer2Int;
	char* pointer2Char;

	//init the pointer with variables addresses
	//pointer2Int = (int*)aIntValue;	//get the value of aIntValue 
	pointer2Int = &aIntValue;
	pointer2Char = &aCharVariable;

	cout << endl << "The pointer value (an addr) is " << pointer2Int;
	cout << endl << "The pointer value (an addr) is " << pointer2Char;

	//change a variable value
	aIntValue = 100;
	// using the pointer
	*(&aIntValue) = 200;
	*pointer2Int = 400;

	cout << endl << "The int value is " << aIntValue;
	cout << endl << "The int value is " << *pointer2Int;



	//int *noProducts  = 0;
	//int *noProducts  = NULL;
	int *noProducts  = nullptr;

	//init the pointer with the addr of a new int in HEAP
	noProducts = new int;		//create one value = without []

	cout << endl << "Give me the no of products ";
	cin >> *noProducts;

	//create an array with noProducts elements
	//float prices[noProducts];		//NEVER on stack - you can't

	float *prices = new float[*noProducts];

	//you can't for dynamic arrays
	//prices = { 0 };

	for (int i = 0; i < *noProducts; i++) {
		prices[i] = 0;
	}

	cout << endl << "The prices array is ";
	for (int i = 0; i < *noProducts; i++) {
		cout << " " << prices[i];
	}

}