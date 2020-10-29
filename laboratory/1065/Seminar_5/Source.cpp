#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class ExceptionName {

};

class ExceptionDescription {

};

class Product {
	unsigned int id = 0;
	string description = "";
	float price = 0;
	char* name = nullptr;

	const static int MIN_DESCR_SIZE = 5;

public:

	//default ctor
	Product() {
		cout << endl << "The default ctor";
	}

	//constructors with arguments
	Product(unsigned int id) {
		this->id = id;
	}

	Product(unsigned int id, string description) {
		this->id = id;
		this->setDescription(description);
	}

	//the constructor that receives values for all attributes
	

	unsigned int getId() {
		//return this->id;
		return id;
	}

	string getDescription() {
		return this->description;
	}

	void printDetails() {
		cout << endl << " ------------------------------ ";
		cout << endl << "Id: " << this->id;
		cout << endl << "Price: " << this->price;
		if (this->name != nullptr) {
			cout << endl << "Name: " << this->name;
		}
		else
		{
			cout << endl << "No name";
		}
		cout << endl << "Description: " << this->description;
	}

	void setName(const char* name) {
		//shadowing 
		//name = name;

		//DON't use = to copy 2 char arrays
		//this->name = name;

		//strcpy(this->name, name);

		//DON'T USE == to compare 2 char* because you check addresses
		//if(name == '\0')

		//check if name is empty string ""
		if (strlen(name) == 0) {
			throw ExceptionName();
		}


		//avoid the memory leak
		if (this->name != nullptr) {
			delete[] this->name;
		}

		//1 create space in heap for the new name
		this->name = new char[strlen(name) + 1];
		//2 copy the value
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	void setDescription(string description) {
		//we accept at least 5 characters for the description
		if (description.size() >= MIN_DESCR_SIZE) {
			this->description = description;
		}
		else {
			throw ExceptionDescription();
		}
	}
};

int main(int argc, char* argv[]) {

	const char* defaultName = "Nothing";
	char* newName = new char[6] {"Pepsi"};

	Product product;
	product.setName(newName);
	product.setDescription("A new flavour");
	product.printDetails();


	product.setName("Coca Cola");
	//product.setName("");		//should not be accepted
	product.printDetails();

	Product product2(1);
	product2.printDetails();

	Product product3(2, "Onother product");
	product3.printDetails();
}
