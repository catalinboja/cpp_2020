#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


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
	Product() {
		cout << endl << "Calling default constructor";
	}

	//constructor with all arguments
	Product(unsigned int id, float price, const char* name,
		const char* description, string producer) {
		this->id = id;
		this->price = price;
		this->setName(name);
		this->setDescription(description);
		this->setProducerDetails(producer);
	}

	//public interface
	unsigned int getId() {
		return id;
		//return this->id;
	}

	void printInfo() {
		cout << endl << "-----------------------------";
		cout << endl << "Id " << this->id;
		cout << endl << "Price " << this->price;
		if (this->name != nullptr) {
			cout << endl << "Name " << this->name;
		}
		cout << endl << "Description " << this->description;
		cout << endl << "Producer details " << this->producerDetails;
	}

	void setProducerDetails(string producerDetails) {
		//shadowing
		//producerDetails = producerDetails;

		if (producerDetails.size() >= MIN_STRING_LENGTH) {
			this->producerDetails = producerDetails;
		}
		else {
			StringLengthException exception;
			throw exception;
			//throw StringLengthException();
		}
	}

	void setDescription(const char* newDescription) {
		if (strlen(newDescription) >= MIN_STRING_LENGTH) {
			//never use = to copy char array
			//this->description = newDescription;

			strcpy(this->description, newDescription);
		}
		else {
			throw StringLengthException();
		}
	}

	void setName(const char* newName) {
		if (strlen(newName) >= MIN_STRING_LENGTH) {

			//avoid the memory leak
			if (this->name != nullptr) {
				delete[] this->name;
			}

			//1 create space
			this->name = new char[strlen(newName) + 1];
			//2 copy the value
			strcpy(this->name, newName);
		}
		else {
			throw StringLengthException();
		}
	}
};

int main(int argc, char* argv[]) {
	Product product1;		//calling the default constructor
	Product product2;		//calling the default constructor

	Product product3(3, 23.5, "Lunch", "Vegan", "Eco");

	product1.setProducerDetails("Bucharest");
	//product1.setProducerDetails("Bu");  //you get an exception
	product1.setDescription("General use product");
	product1.setName("Coca Cola");
	product1.setName("Pepsi");

	//cout << endl << product1.getId();
	product1.printInfo();
	product2.printInfo();
	product3.printInfo();


}