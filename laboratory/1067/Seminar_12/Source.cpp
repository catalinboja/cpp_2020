#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name = "";
	float price = 0;
	int* values = new int[10];
public:
	Product(string Name, float Price): name(Name), price(Price) {
		//this->name = Name;
		cout << endl << "Product ctor with arguments";
	}

	Product() {
		cout << endl << "Product default ctor";
	}

	float getPrice() {
		return this->price;
	}

	~Product() {
		cout << endl << "The Product destructor";
		if (this->values)
			delete[] this->values;
	}
};

class DiscountProduct: public Product{
	float discountPercent;		//20 means 20%
public:
	DiscountProduct(): Product("No name",0) {
		cout << endl << "DiscountProduct default ctor";
	}

	DiscountProduct(string name, float price, float discount)
		:Product(name, price), discountPercent(discount) {
		//this->discountPercent = discount;
		cout << endl << "DiscountProduct ctor with arguments";
	}

	//DiscountProduct(float discount): Product("",0) {
	//	this->discountPercent = discount;
	//}

	float getDiscountValue() {
		return this->price * (this->discountPercent / 100);
	}

	~DiscountProduct() {
		cout << endl << "DiscountProduct destructor";
		//if (this->values) {
		//	delete[] this->values;
		//	this->values = nullptr;
		//}
	}

	float getFinalPrice() {
		return this->price - this->getDiscountValue();
	}

	//override the parent method
	float getPrice() {
		//return this->price - this->getDiscountValue();

		//we are calling the parent version of getPrice
		return this->Product::getPrice() - this->getDiscountValue();
	}
};

class ProductWithExpirationDate {
protected:
	string exDate;
	string name;
};

class GroceryProduct : public DiscountProduct, public ProductWithExpirationDate {
	string type;
public:
	void doSomething() {
		this->Product::name = "test";
		this->DiscountProduct::name = "test";
		this->ProductWithExpirationDate::name = "test";
	}
};

int main(int argc, char* argv[]) {
	//Product p1;
	Product p2("Laptop", 1500);

	DiscountProduct dp1;
	DiscountProduct dp2("Monitor", 750, 20);

	cout << endl << "The price of the Laptop is " << p2.getPrice();
	cout << endl << "The price of the Monitor is " << dp2.getPrice();
	//cout << endl << "The price of the Monitor is " << dp2.getFinalPrice();
	
	//p2.price = 20;
}
