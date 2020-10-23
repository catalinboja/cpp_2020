#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

class Product {
	//you get by default a private at the beggining of the class
private:
	unsigned int id = 0;	//set  0 as a default
	float price = 0;
public:
	bool isGrocery = false;
	char description[50] = "No name";
private:
	int* monthlySales = nullptr;
	int noMOnths = 0;

public:
	//accessor methods - provide read and/or write access
	//read access
	unsigned int getId() {
		//we get by default the address of the calling object object.getId()
		//the address is managed by the "this" pointer
		//Product * this;
		return this->id;
		//return (*this).id;
	}

	float getPrice() {
		return this->price;
	}

	//warning - is not quite ok
	int* getMonthlySales() {
		return this->monthlySales;
	}

	int noMonths() {
		return this->noMOnths;
	}

	//giving write access
	void setPrice(float newPrice) {
		if (newPrice > 0 && newPrice < 1000) {
			this->price = newPrice;
		}
		else
		{
			throw "The value is invalid";
		}
	}

	void printProduct() {

		cout << endl << "-------------------------------";
		cout << endl << "Name = " << this->description;
		cout << endl << "Id = " << this->id;
		cout << endl << "Price = " << this->price;
		cout << endl << "The product is grocery: "
			<< (this->isGrocery ? "yes" : "no");
		cout << endl << "No months for records history = " << this->noMOnths;
		cout << endl << "Monthly sales: ";
		for (int i = 0; i < this->noMOnths; i++) {
			cout << " " << this->monthlySales[i];
		}

	}
};


int main(int argc, char* argv[]) {

	//creating an object - an instance of the class
	Product product;
	Product product2;
	int variable;

	//product.price = -23;

	product.isGrocery = true;
	product.description[9] = '\0';
	strcpy(product.description, "Pepsi");

	cout << endl << "The product is grocery: "
		<< (product.isGrocery ? "yes" : "no");
	cout << endl << "The product description is " <<
		product.description;

	product.getId();
	//product.setPrice(-23);
	product.setPrice(23);
	cout << endl << "The price is " << product.getPrice();

	product.printProduct();
	product2.printProduct();
}