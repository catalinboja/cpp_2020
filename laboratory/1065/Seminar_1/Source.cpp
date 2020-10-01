#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

void main() {

	char aLetter = 'a';
	printf("\n The letter is %c",aLetter);
	printf("\n The letter is %d",aLetter);
	printf("\n The letter is %x",aLetter);
	//aLetter = 'b';
	aLetter += 1;
	printf("\n The letter is %c", aLetter);
	aLetter -= 32;
	printf("\n The letter is %c", aLetter);
	printf("\n Give me another symbol: ");
	scanf("%c", &aLetter);
	printf("\n The letter is %c", aLetter);

	//C++
	std::cout << std::endl << "\n The value is " << aLetter;
	std::cout << std::endl << "Give me another value: ";
	std::cin >> aLetter;
	cout << endl << "\n The value is " << aLetter;

	//Arrays 
	// static aproach
	const int NO_ELEMENTS = 10;
	int numbers[NO_ELEMENTS];	//works only with consts variables

	//init the array
	for (int i = 0; i < NO_ELEMENTS; i++) {
		numbers[i] = i + 1;
	}


	cout << endl << "The array is: ";
	for (int i = 0; i < NO_ELEMENTS; i++) {
		cout << " " << numbers[i];
	}

}