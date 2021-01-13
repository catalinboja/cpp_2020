#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name = "";
	float price = 0;
	char* description = nullptr;
private:
	int barCode = 0;
public:
	Product(string Name, float Price): name(Name), price(Price){
		this->description = nullptr;
		cout << endl << "Product ctor with arguments";
	}

	Product() {
		cout << endl << "Product default ctor";
	}

	~Product() {
		cout << endl << "Product destructor";
		if (this->description != nullptr) {
			delete[] this->description;
		}
	}

	float getPrice() {
		return this->price;
	}

private:

	void changeBarCode(int value) {
		this->barCode = value;
	}
};

class DiscountProduct: public Product {
	float discountPercent = 0;				//if the value is 10 -> 10%
public:
	DiscountProduct():Product("No name", 0) {
		this->discountPercent = 0;
		cout << endl << "DiscountProduct default ctor";
	}
	DiscountProduct(string Name, float Price, float Discount)
		:Product(Name, Price), discountPercent(Discount)
	{
		this->discountPercent = Discount;	//redundant
		cout << endl << "DiscountProduct ctor with arguments";
	}

	DiscountProduct(
		string Name, float Price, float Discount, const char* Description) 
		:Product(Name, Price)
	{
		this->discountPercent = Discount;
		this->description = new char[strlen(Description) + 1];
		strcpy(this->description, Description);
		cout << endl << "DiscountProduct ctor with arguments";
	}

	~DiscountProduct() {
		cout << endl << "DiscountProduct destructor";

		//not recommended
		if (this->description != nullptr) {
			delete[] this->description;
			this->description = nullptr;	//at least avoid the dangling pointer
		}
	}

	float getPriceWithDiscount() {
		return this->price * (1 - this->discountPercent / (float)100);
	}

	//overriding the parent class method
	float getPrice() {

		//calling the parent class version
		float initialPrice = this->Product::getPrice();

		return  this->getPriceWithDiscount();
	}

	string getName() {
		return this->name;
	}
};

int main() {
	Product p1("Laptop",1000);			//Product  ctor with args
	cout << endl << "The price is " << p1.getPrice();
	DiscountProduct dp1;				//Product ctor with args + DiscountProduct default
	DiscountProduct dp2("Smartphone", 590, 15);	//Product ctor with args +  DiscountProduct ctor with args
	cout << endl << "The price of the smartphone is " << dp2.getPrice();
	//cout << endl << "The price of the smartphone is " << dp2.getPriceWithDiscount();

	//remember the function stack is a STACK
	//DiscountProduct destructor + Product destructor for dp2
	//DiscountProduct destructor + Product destructor for dp1
	//Product destructor for p1
}