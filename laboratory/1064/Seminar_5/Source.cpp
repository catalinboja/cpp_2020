#include <iostream>
using namespace std;

class Product {
private:			//you get it by default
	unsigned int id = 0;
	float price = 0;
public:
	char description[50] = "Not defined";
	bool isFragile = false;
private:
	int* monthlySales = nullptr;
	int noMonths = 0;
public:
	//the class public interface
	//allows read access
	unsigned int getId() {
		return this->id;
	}

	float getPrice() {
		return this->price;
	}

	//is wrong 
	int* getMonthlySales() {
		return this->monthlySales;
	}

	int getNoMonths() {
		return this->noMonths;
	}

	void printInfo() {
		cout << endl << "-----------------------------";
		cout << endl << "Id: " << this->id;
		cout << endl << "Description: " << this->description;
		cout << endl << "Price: " << this->price;
		cout << endl << "Is a fragile product: " <<
			(this->isFragile ? "yes" : "no");
	}

	//allow write access on private attrs
	void setPrice(float newPrice) {
		if (newPrice > 0 && newPrice < 1000) {
			this->price = newPrice;
		}
		else {
			throw "The value is wrong";
		}
	}

};

int main(int argc, char* argv[]) {
	Product product;
	Product* pProduct;

	pProduct = &product;

	product.description[15] = '\0';

	//cout << endl << "The product id is " << product.id;
	cout << endl << "The product id is " << product.getId();
	cout << endl << "The product id is " << pProduct->getId();
	cout << endl << "The product id is " << (*pProduct).getId();
	cout << endl << "The description is " << product.description;

	if (product.isFragile) {
		cout << endl << "Is a fragile product: " << " yes";
	}
	else {
		cout << endl << "Is a fragile product: " << " no";
	}

	cout << endl << "Is a fragile product: " <<
		(product.isFragile ? "yes" : "no");

	product.printInfo();
	Product product2;
	product2.printInfo();

	//product.setPrice(-23);
	product.setPrice(100);

	product.printInfo();

}

