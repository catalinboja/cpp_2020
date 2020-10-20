#include <iostream>
using namespace std;

void printArray(int array[], int noElements);

int* createAndInitArray(int noElements, int initialValue) {
	int* newArray = new int[noElements];
	for (int i = 0; i < noElements; i += 1) {
		newArray[i] = initialValue;
	}
	return newArray;
}

void addValueToArray(int* & array, int & noElements, int newValue) {
	//IT'S WRONG
	//noElements += 1;
	//array[noElements - 1] = newValue;

	int* newArray = new int[noElements + 1];
	for (int i = 0; i < noElements; i++) {
		newArray[i] = array[i];
	}

	newArray[noElements] = newValue;
	noElements += 1;

	//avoid the memory leak
	delete[] array;
	array = newArray;
}

void addValueToArray2(int** array, int* noElements, int newValue) {
	//IT'S WRONG
	//noElements += 1;
	//array[noElements - 1] = newValue;

	int* newArray = new int[*noElements + 1];
	for (int i = 0; i < *noElements; i++) {
		newArray[i] = (*array)[i];
	}

	newArray[*noElements] = newValue;
	noElements += 1;

	//avoid the memory leak
	delete[] array;
	*array = newArray;
}

//int main(int argc, char** argv)
int main(int argc, char* argv[]) {

	cout << endl << "The app is " << argv[0];

	//the app data
	//int* values = 0;
	//int* values = NULL;
	int* values = nullptr;
	int noValues = 0;

	if (argc == 3) {
		cout << endl << "Received value for no elements = " << argv[1];
		cout << endl << "Received value for initial value = " << argv[2];

		int noElements = atoi(argv[1]);
		int initialValue = atoi(argv[2]);

		values = createAndInitArray(noElements, initialValue); //noElements from create = noElements
		noValues = noElements;

	}
	else
	{
		cout << endl << "You need to give us [no elements] [initial value]";
	}


	printArray(values, noValues);

	addValueToArray(values, noValues, 100);

	printArray(values, noValues);
}

void printArray(int array[], int noElements) {

	if (array == nullptr) {
		cout << endl << "The array is empty";
	}
	else {
		cout << endl << "The array is:";
		for (int i = 0; i < noElements; i++) {
			cout << " " << array[i];
		}
	}
}