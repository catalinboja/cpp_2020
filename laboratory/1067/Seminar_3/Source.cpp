#include <iostream>
using namespace std;


void printArray(int* array, int n);

int* createAndInitArray(int noValues, int initialValue) {
	int* newArray = new int[noValues];
	for (int i = 0; i < noValues; i += 1) {
		newArray[i] = initialValue;
	}
	return newArray;
}

void addNewValue(int* & array, int & noElements, int newValue) {
	int* newArray = new int[noElements + 1];
	for (int i = 0; i < noElements; i++) {
		newArray[i] = array[i];
	}
	newArray[noElements] = newValue;
	noElements += 1;

	delete[] array;	//prevent a memory leak on previous array
	array = newArray;
}

void addNewValue2(int** array, int* noElements, int newValue) {
	int* newArray = new int[*noElements + 1];
	for (int i = 0; i < *noElements; i++) {
		newArray[i] = (*array)[i];
	}
	newArray[*noElements] = newValue;
	(*noElements) += 1;

	delete[] array;	//prevent a memory leak on previous array
	(*array) = newArray;
}

//int main(int argc, char** argv)
int main(int argc, char* argv[]) {

	//int* values = 0;
	//int* values = NULL;
	int* values = nullptr;
	int noValues = 0; ;


	if (argc == 3) {
		//argv[0] is by default the exe full path
		cout << endl << "The app is " << argv[0];
		cout << endl << "The received no of elements: " << argv[1];
		cout << endl << "The received initial value: " << argv[2];

		int initNoValues = atoi(argv[1]);
		int initValue = atoi(argv[2]);

		values = createAndInitArray(initNoValues, initValue);
		noValues = initNoValues;

	}
	else {
		cout << endl << "Missing arguments: [no elements] [initial value]";
	}

	printArray(values, noValues);

	addNewValue(values, noValues, 100);

	printArray(values, noValues);

}

void printArray(int* array, int n) {

	if (array == nullptr) {
		cout << endl << "The array is empty";
	}
	else {

		cout << endl << "The array is :";
		for (int i = 0; i < n; i++) {
			cout << " " << array[i];
		}
	}
}