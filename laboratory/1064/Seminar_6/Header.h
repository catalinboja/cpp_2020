#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <string>
using namespace std;

void printMsg(string msg) {
	cout << endl << "Message: " << msg;
}

class StringLengthException {

};

class Product {
	unsigned int id = 0;
	float price = 0;
	char* name = nullptr;
	char description[100] = "No description";
	string producerDetails = "";

	const static int MIN_STRING_LENGTH = 3;

public:
	//default constructor
	Product() {
		cout << endl << "Calling default ctor";
	}

	void setProducer(string producer) {

		//using the C approach
		int size = strlen(producer.c_str());
		 
		if (producer.length() >= MIN_STRING_LENGTH) {
			this->producerDetails = producer;
		}
		else
		{
			StringLengthException ex;
			throw ex;
			//throw StringLengthException();
		}
	}

	void setDescription(const char* newDiscription) {
		if (strlen(newDiscription) >= MIN_STRING_LENGTH) {
			strcpy(this->description, newDiscription);
		}
		else
		{
			throw StringLengthException();
		}
	}

	void setName(const char* newName) {
		if (strlen(newName) >= MIN_STRING_LENGTH) {

			//avoid the memory leak
			if (this->name != nullptr) {
				delete[] this->name;
			}

			//1 create space for it
			this->name = new char[strlen(newName) + 1];
			//2 copy the value
			strcpy(this->name, newName);
		}
		else
		{
			throw StringLengthException();
		}
	}

	void printInfo() {

		//Ctrl + D  - duplicates current line	
		cout << endl << "-------------------------------";
		cout << endl << "Id: " << this->id;
		cout << endl << "Price: " << this->price;
		if (this->name != nullptr) {
			cout << endl << "Name: " << this->name;
		}
		else {
			cout << endl << "No name";
		}
		cout << endl << "Description: " << this->description;
		cout << endl << "Producer: " << this->producerDetails;
	}
};
