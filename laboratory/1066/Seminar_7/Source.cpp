#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

enum Month {JAN = 1, FEB = 2, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
enum ProductType {NORMAL = 100, PROMO = 200, FAST_SALE = 300};

class CalendarDate {
	int day = 0;
	//int month = 0;
	Month month;
	int year;
};

class WrongInputException {

};

class Product {
	//CalendarDate date;

	//12/11/2020
	//char date[11];

	//int day = 0;
	////int month = 0;
	//Month month;
	//int year;

	string name = "";
	char* date = nullptr;
	float price = 0;
	ProductType type = ProductType::NORMAL;
	static int PROMO_PRODUCTS;
	const static int MIN_DATE_LENGTH = 5;
public:

	//1/11/2020
	//1/1/2020
	void setDate(const char* newDate) {
		if (newDate != nullptr && strlen(newDate) > MIN_DATE_LENGTH) {
			if (this->date != nullptr) {
				delete[] this->date;
			}
			this->date = new char[strlen(newDate) + 1];
			strcpy(this->date, newDate);
		}
		else {
			throw WrongInputException();
		}
	}

	Product(string name, const char* date, float price, ProductType type) {
		this->name = name;
		this->setDate(date);
		this->price = price;
		this->type = type;

		if (this->type == ProductType::PROMO) {
			Product::PROMO_PRODUCTS += 1;
		}
	}

	~Product() {
		if (this->date != nullptr) {
			delete[] this->date;
		}
		if (this->type == ProductType::PROMO) {
			Product::PROMO_PRODUCTS -= 1;
		}
	}

	//int getPromoProducts() {
	//	//return this->PROMO_PRODUCTS;
	//	//return PROMO_PRODUCTS;
	//	return Product::PROMO_PRODUCTS;
	//}

	static int getPromoProducts() {
		//return PROMO_PRODUCTS;
		//return this->PROMO_PRODUCTS;	//this does not exist here
		return Product::PROMO_PRODUCTS;
	}

	Product(const Product& p) {
		//p.name = this->name;
		this->name = p.name;
		this->price = p.price;
		this->type = p.type;
		this->setDate(p.date);
		if (this->type == ProductType::PROMO) {
			Product::PROMO_PRODUCTS += 1;
		}
	}

	string getName() const {
		//this->price = 1000;
		return this->name;
	}




	friend void operator<<(ostream& console, Product& p);

};

int Product::PROMO_PRODUCTS = 0;

void doNothing(Product p) {

}

Product anotherFunction() {
	Product p("Pepsi", "10/11/2020", 3.5, ProductType::NORMAL);
	return p;
}

//Product readProductFromFile(string filename) {
//
//}
//
//Product readProductFromConsole() {
//
//}


void operator<<(ostream& console, Product& p) {
	//p.price = 1000;
	console << "\n---------------------------";
	console << "\nProduct name is " << (p.getName());
	console << endl << "Price is " << p.price;
	console << endl << "Date is " << p.date;
	console << endl << "Type is " << p.type;
}


int main(int argc, char* argv[]) {

	Product p1("Pepsi", "10/11/2020", 3.5, ProductType::NORMAL);
	Product* p2 = new Product("Laptop", "1/7/2020", 1200, ProductType::PROMO);

	//cout << endl << "Total number of sales: " << p1.getPromoProducts();
	//cout << endl << "Total number of sales: " << p2->getPromoProducts();

	cout << endl << "Total number of sales: " << Product::getPromoProducts();

	delete p2;

	cout << endl << "Total number of sales: " << Product::getPromoProducts();

	doNothing(p1);
	anotherFunction();

	Product p3 = p1;

	cout << p1;
	
	//p1 = p1 + 10;		//function + (p1, 10);
	//p1 += 20;
}