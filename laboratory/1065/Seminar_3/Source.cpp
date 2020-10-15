#include <iostream>
using namespace std;

void printArray(int* array, int noElements) {

	//if(noElements == 0)
	if (array == nullptr) {
		cout << endl << "The array is empty";
	}
	else {
		cout << endl << "The array is: ";
		for (int i = 0; i < noElements; i++) {
			cout << " " << array[i];
		}
	}
}

int* createAndInit(int noElements, int initialValue) {
	int* newArray = new int[noElements];
	for (int i = 0; i < noElements; i++) {
		newArray[i] = initialValue;
	}

	return newArray;
}

void addNewElement(int newValue, int* & array, int & size) {

	//int* newArray = new int[size + 1];
	//newArray[size] = newValue;

	int* newArray = createAndInit(size + 1, newValue);
	
	for (int i = 0; i < size; i++) {
		newArray[i] = array[i];
	}

	size = size + 1;
	//clear the previous array
	delete[] array;		//avoiding the memory leak
	array = newArray;
}

void addNewElement2(int newValue, int* * pArray, int* pSize) {

	//int* newArray = new int[size + 1];
	//newArray[size] = newValue;

	int* newArray = createAndInit(*pSize + 1, newValue);

	for (int i = 0; i < *pSize; i++) {
		newArray[i] = (*pArray)[i];
	}

	*pSize = *pSize + 1;
	delete[] (* pArray);

	*pArray = newArray;
}

int main(int argc, char* argv[]) {

	//Seminar_3.exe 5 10

	int noValues = 0;
	//int* values = 0;
	//int* values = NULL;
	int* values = nullptr;

	printArray(values, noValues);

	//check main arguments
	if (argc == 3) {
		//an argv[0] you get .exe path
		int size = atoi(argv[1]);
		int initialValue = atoi(argv[2]);
		values = createAndInit(size, initialValue);
		noValues = size;
	}
	else
	{
		cout << endl << "The app needs the number of elements and their value";
	}

	printArray(values, noValues);
	
	//add new values to the array
	//naive - wrong way
	//it's wrong
	//for (int i = 0; i < 5; i++) {
	//	noValues += 1;
	//	values[noValues - 1] = 100;
	//}

	printArray(values, noValues);

	addNewElement(100, values, noValues);

	printArray(values, noValues);
}
