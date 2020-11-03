#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class WrongGivenValueException {

};

class Product {
	unsigned int id = 0;
	float price = 0;
	char name[50] = "Nothing";
	char* description = nullptr;
	string otherInfo = "";

	static const int MIN_INFO_SIZE = 5;

public:
	void printInfo() {
		cout << endl << "-----------------------";
		cout << endl << "Id " << this->id;
		cout << endl << "Price " << this->price;
		cout << endl << "Name " << this->name;
		if (this->description != nullptr) {
			cout << endl << "Description " << this->description;
		}
		else {
			cout << endl << "No description";
		}
		cout << endl << "Other info " << this->otherInfo;
	}

	void setOtherInfo(string otherInfo) {
		//shadowing 
		//otherInfo = otherInfo;

		//no less than 5 chars
		if (otherInfo.size() >= MIN_INFO_SIZE) {
			this->otherInfo = otherInfo;
		}
		else
		{
			throw WrongGivenValueException();
		}
	}

	void setName(const char* name) {
		//validate the received name size
		//sizeof(static array) = the total size of the array in bytes
		//int values[50] -> sizeof(values) - > 200

		if (strlen(name) < sizeof(this->name)) {
			strcpy(this->name, name);
		}
		else {
			throw WrongGivenValueException();
		}
	}

	void setDescription(const char* newDescription) {

		//avoid the memory leak
		if (this->description != nullptr) {
			delete[] this->description;
		}

		//1 create space for the description
		this->description = new char[strlen(newDescription) + 1];
		//2 copy the values
		strcpy(this->description, newDescription);
	}

	//constructor default
	Product() {
		cout << endl << "The Product default constructor";
	}

	Product(unsigned int id) {
		this->id = id;
	}
	Product(unsigned int id, const char* description, const char* name, string info) {
		this->id = id;
		this->setDescription(description);
		this->setName(name);
		this->setOtherInfo(info);
	}
};

int main(int argc, char* argv[]) {
	Product product1;
	Product product2;
	Product product3(3);
	Product product4(4, "Soda", "Coca Cola", "Not for kids");

	string name = "John";
	name = name + " Bush";

	const char* newName = "Pepsi";
	//char* newName = new char[] {"Pepsi"};

	product1.setOtherInfo("Not for kids");
	product1.setName(newName);
	product1.setDescription("To cool off during summer");
	product1.setDescription("None");
	//product2.setOtherInfo("...");

	product1.printInfo();
	product2.printInfo();

	Product* p = new Product();
	delete p;

	product4.printInfo();
}