#pragma once

#include <iostream>
#include <string>
using namespace std;

void printMessage(std::string msg) {
	cout << endl << msg;
}

class Product {
	unsigned int id = 0;
	string name = "";
	float* monthlySales = nullptr;
	int noMonths = 0;

	const static int MIN_SALES_VALUE_FILTER = 1000;
	static int objectCounter;
public:
	int getObjCounter() {
		//return this->objectCounter;
		//return objectCounter;
		return Product::objectCounter;
	}

	Product() {
		cout << endl << "Calling default ctor";
		Product::objectCounter += 1;
	}

	Product(int id) {
		cout << endl << "Calling ctor with id";
		this->id = id;
	}

	~Product() {
		cout << endl << "Calling destructor";
	}

	void setMonthlySales(float* records, int noRecords) {
		//shallow - copy
		//this->monthlySales = records;

		//avoid memory leak
		if (this->monthlySales != nullptr) {
			delete[] this->monthlySales;
		}

		this->noMonths = noRecords;
		this->monthlySales = new float[noRecords];
		for (int i = 0; i < noRecords; i++) {
			this->monthlySales[i] = records[i];
		}
	}
};

int Product::objectCounter = 0;


