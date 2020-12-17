#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name;
	float price;
public:
	Product(string Name, float Price):name(Name), price(Price) {
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
		cout << endl << "Product destructor";
	}
};

class DiscountProduct: public Product {
	float discount;					//percentage 20 ~ 20%
public:
	DiscountProduct(): Product("No name", 0) {
		cout << endl << "DiscountProduct default ctor";
	}

	DiscountProduct(string Name, float Price, float Discount)
		: Product(Name, Price), discount(Discount) {
		//this->discount = Discount;
		cout << endl << "DiscountProduct ctor with arguments";
	}

	void setPrice(float newPrice) {
		this->price = newPrice;
	}

	//DiscountProduct(float Discount): Product("",0) {
	//}

	~DiscountProduct() {
		cout << endl << "DiscountProduct destructor";
	}

	float getPriceWithDiscount() {
		//int value = 10;
		//float result = (float)value / 100;
		return this->price - (this->discount / 100 * this->price);
	}

	//override the function from parent
	float getPrice() {
		return this->price - (this->discount / 100 * this->price);
	}

	float getIntialPrice() {
		//return this->price;
		//calling the version from Product
		return this->Product::getPrice();
	}

};

class ProductWithExpirationDate {
protected:
	string productionDate;
	int noDaysTillExpiration;
	string name;
};

class GroceryProduct : public DiscountProduct, public ProductWithExpirationDate {
public:
	GroceryProduct(): ProductWithExpirationDate(), DiscountProduct() {
		cout << endl << "GroceryProduct default ctor";
	}

	void setName(string Name) {
		this->DiscountProduct::name = Name;
		this->Product::name = Name;
		this->ProductWithExpirationDate::name = Name;
	}
};



int main() {
	Product p1;
	Product p2("Laptop", 1000);
	cout << endl << "The product price is " << p2.getPrice();

	DiscountProduct dp1;
	DiscountProduct dp2("Monitor", 750, 15);

	cout << endl << "The monitor price is " << dp2.getPrice();
	cout << endl << "The monitor initial price is " << dp2.getIntialPrice();
	//cout << endl << "The monitor price is " << dp2.getPriceWithDiscount();

	//p2.price = 10;
	//dp2.price = 10;
}
