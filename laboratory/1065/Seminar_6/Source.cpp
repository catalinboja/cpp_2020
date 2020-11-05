#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Product {

	const static int MIN_STRING_LENGTH = 3;
	//no this way
	//static int counter = 0;							//used to count how many objects we created
	static int counter;

	unsigned int id = 0;
	string name = "";
	char* description = nullptr;




public:
	Product() {
		Product::counter += 1;

		char* desc = new char[] {"Nothing"};

		this->description = new char[strlen(desc) + 1];
		strcpy(this->description, desc);
	}

	Product(int id) {
		this->id = id;
		this->name = "No name";
		this->setDescription("No description");

		Product::counter += 1;
	}

	//define the constructor with all arguments and test in main



	int getCounter() {
		return Product::counter;
	}

	void printProduct() {
		cout << endl << "--------------------------";
		cout << endl << "Id " << this->id;
		cout << endl << "Description " << this->description;
		cout << endl << "Name " << this->name;
	}

	void setDescription(const char* description) {
		if (this->description != nullptr) {
			delete[] this->description;
		}
		this->description = new char[strlen(description) + 1];
		strcpy(this->description, description);
	}

	~Product() {
		cout << endl << "The class destructor";
		if (this->description) {
			delete[] this->description;
		}

		Product::counter -= 1;
	}

};

int Product::counter = 0;

int main() {
	cout << endl << "We just started";
	Product p1;
	Product* pointerProduct = new Product();

	cout << endl << "Total number of objects is " << p1.getCounter();
	p1.setDescription("Not for kids less than 3 years old");
	p1.printProduct();
	p1.setDescription("For all");
	p1.printProduct();

	pointerProduct->setDescription("Lenovo laptop");
	pointerProduct->printProduct();

	Product p2(2);
	p2.printProduct();

	Product* pProduct2 = new Product(3);
	pProduct2->printProduct();

	cout << endl << "Total number of objects is " << p1.getCounter();


	//remove the Heap Object
	delete pointerProduct;

	cout << endl << "Total number of objects is " << p1.getCounter();
}

