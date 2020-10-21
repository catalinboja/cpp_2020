#include <iostream>
using namespace std;

void printArray(int n, int* array);

int* createAndInitArray(int size, int initialValue) {
	int* newArray = new int[size];
	for (int i = 0; i < size; i++) {
		newArray[i] = initialValue;
	}
	return newArray;
}

void addNewElement(int* & array, int & n, int newValue) {
	int* newArray = new int[n + 1];
	for (int i = 0; i < n; i += 1) {
		newArray[i] = array[i];
	}
	n += 1;
	newArray[n - 1] = newValue;

	//delete previous array - avoid memory leak
	delete[] array;

	array = newArray;
}

//int main(int argc, char** argv) 
int main(int argc, char* argv[]) {

	cout << endl << "The app name is " << argv[0];

	int noElements = 0;
	//int* elements = 0;
	//int* elements = NULL;
	int* elements = nullptr;

	//check if we got the arguments to create the array
	if (argc == 3) {
		int receivedSize = atoi(argv[1]);
		int receivedInitialValue = atoi(argv[2]);

		cout << endl << "Initial size = " << receivedSize;
		cout << endl << "Initial value = " << receivedInitialValue;
		elements = createAndInitArray(receivedSize, receivedInitialValue);
		noElements = receivedSize;

	}
	else {
		cout << endl << "Missing arguments [initial size] [initial value]";
	}


	printArray(noElements, elements);

	for (int i = 0; i < 10; i++) {
		addNewElement(elements, noElements, 100);
	}

	printArray(noElements, elements);


}

void printArray(int n, int* array) {

	if (array == nullptr) {
		cout << endl << "The array is empty";
	}
	else {
		cout << endl << "The array is: ";
		for (int i = 0; i < n; i++) {
			cout << " " << array[i];
		}
	}
}