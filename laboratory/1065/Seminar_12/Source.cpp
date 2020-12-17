#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name = "";
	float price = 0;
	int* values;
public:
	Product(string Name, float Price):name(Name), price(Price){
		cout << endl << "Product constructor with arguments";
	}

	float getPrice() {
		return this->price;
	}

	~Product() {
		cout << endl << "Product destructor";
		delete[] values;
	}

	string getDescription() {
		string description = "The product " + this->name + " has a price of " +
			to_string(this->price);
		return description;
	}
};

class DiscountProduct: public Product {
	float discountPercent;				//0.1 ~ 10%
public:
	//string getName() {
	//	return this->name;
	//}

	DiscountProduct():Product("", 0) {
		cout << endl << "DiscountProduct default ctor";
	}

	//DiscountProduct(float discount):Product("",0) {

	//}

	DiscountProduct(string Name, float Price, float Discount) :Product(Name, Price) {
		this->discountPercent = Discount;
		cout << endl << "DiscountProduct ctor with arguments";
		this->name += " with a discount";
	}


	float getDiscountValue() {
		return this->price * this->discountPercent;
	}

	~DiscountProduct() {
		cout << endl << "DiscountProduct destructor";
	}

	float getPriceWithDiscount() {
		return this->price - this->getDiscountValue();
	}

	//overriding the parent class getPrice() method
	float getPrice() {
		return this->price - this->getDiscountValue();
	}

	string getDescription() {
		//reuse the parent version
		string description = this->Product::getDescription();
		description += ". The product has a discount of " +
			to_string(this->discountPercent) + " and the final price is " +
			to_string(this->getPrice());
		return description;
	}
};


class ProductWithChildRegulations: public DiscountProduct {
	int minimumAge;
	bool isSafeForSmallKids;

public:
	ProductWithChildRegulations() {
		cout << endl << "Default ctor from ProductWithChildRegulations";
	}
};

class ValidityTerm {
	string productionDate;
	string expirationDate;
};

class YogurtForKids : public ProductWithChildRegulations, public ValidityTerm {

};

int main() {
	//Product p1;
	Product p2("Laptop", 1000);
	//p2.price = 23;
	cout << endl << "The price of the product is " << p2.getPrice();

	//DiscountProduct dp1;
	DiscountProduct dp2("Toy", 250, 0.15);

	cout << endl << "The Toy at the promotion has a price of " << dp2.getPrice();
	//cout << endl << "The Toy at the promotion has a price of " << dp2.getPriceWithDiscount();


	cout << endl << p2.getDescription();
	cout << endl << dp2.getDescription();

	ProductWithChildRegulations pr1;

}

