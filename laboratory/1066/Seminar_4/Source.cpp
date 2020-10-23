#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Product {
	// you get the private: by default
private:
	unsigned int id = 0;
	float price = 0;
public:
	bool isFragile = false;
	char description[50] = "Nothing";
private:
	int* monthlySales = nullptr;
	int noMonths = 0;


public:
	//class public interface
	//accessor methods - give read and/or write access to private attributes
	unsigned int getId() {
		//the method always gets the address of the object that will call it
		//the address is stored in the this pointer
		//Product * this
		return this->id;
	}

	float getPrice() {
		return this->price;
	}

	//it's not quite ok
	int* getMonthlySales() {
		return this->monthlySales;
	}

	int getNoMonths() {
		return this->noMonths;
	}

	//accessor methods for allowing write access
	void setPrice(float price) {
		if (price > 0 && price < 1000) {
			this->price = price;
		}
		else
		{
			throw "The value is no ok";
		}
	}

	//a function to prin the product data
	void printInfo() {
		cout << endl << "---------------------------------";
		cout << endl << this->id << " - " << this->description;
		cout << endl << "Is fragile: " << (this->isFragile ? "yes" : "no");;
		cout << endl << "Price: " << this->price;
		cout << endl << "Monthly sales: " << this->noMonths;
		cout << endl << "Values: ";
		for (int i = 0; i < this->noMonths; i++) {
			cout << " " << this->monthlySales[i];
		}
	}

};

int main(int argc, char* argv[]) {

	//creating an object - create an instance of the class (is story)
	Product product;

	//product.price = -23;

	//product.price = 23;
	product.isFragile = true;

	product.description[10] = '\0';
	strcpy(product.description, "Pepsi");

	cout << endl << "The product is fragile: "
		<< (product.isFragile ? "yes" : "no");
	cout << endl << "The product description is " << product.description;

	product.getId();

	Product* pProd = &product;
	pProd->getId();
	(*pProd).getId();

	//product.setPrice(-23);

	cout << endl << "The price is " << product.getPrice();
	product.setPrice(3.25);
	cout << endl << "The price is " << product.getPrice();

	product.printInfo();

	Product product2;
	product2.printInfo();

}