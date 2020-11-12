#include <iostream>
#include <string>
using namespace std;

class WrongInputException {

};

class Product {
	int id = 0;
	float price = 0;
	bool hasDiscount = false;
	float* monthlySales = nullptr;
	int noMonths = 0;

	static int noDiscountedProducts;
	static const float MIN_PRICE;
public:
	void setPrice(float newPrice) {
		if (newPrice >= Product::MIN_PRICE) {
			this->price = newPrice;
		}
		else
		{
			throw WrongInputException();
		}
	}

	void setDiscount() {
		if (!this->hasDiscount) {
			this->hasDiscount = true;
			Product::noDiscountedProducts += 1;
		}
	}

	void removeDiscount() {
		if (this->hasDiscount) {
			this->hasDiscount = false;
			Product::noDiscountedProducts -= 1;
		}
	}

	void setSalesRecords(float* records, int noRecords) {

		if (records != nullptr && noRecords > 0) {

			if (this->monthlySales) {
				delete[] this->monthlySales;
			}

			this->monthlySales = new float[noRecords];
			memcpy(this->monthlySales, records, sizeof(float) * noRecords);
			//for (int i = 0; i < noRecords; i++) {
			//	this->monthlySales[i] = records[i];
			//}
			this->noMonths = noRecords;
		}
		else {
			throw WrongInputException();
		}
	}

	Product(int id, float price, bool hasDiscount, float* records, int noRecords) {
		if (hasDiscount) {
			this->setDiscount();
		}
		this->setPrice(price);
		this->id = id;
		this->setSalesRecords(records, noRecords);
	}

	static int getNoDiscounts() {
		return Product::noDiscountedProducts;
	}

	~Product() {
		if (this->monthlySales) {
			delete[] this->monthlySales;
		}
	}

	Product(const Product& p) {
		//p.id = this->id;
		this->id = p.id;

		//don't do the shallow copy
		//this->monthlySales = p.monthlySales;

		this->setSalesRecords(p.monthlySales, p.noMonths);
		if (p.hasDiscount) {
			this->setDiscount();
		}
		this->price = p.price;
	}

	friend void operator<<(ostream& console, Product p);
};

int Product::noDiscountedProducts = 0;
const float Product::MIN_PRICE = 1;

void operator<<(ostream& console, Product p) {
	console << endl << "------------------------";
	console << endl << "The product id is " << p.id;
	console << endl << "The product price is " << p.price;
	console << endl << "Has discount " << (p.hasDiscount ? "true" : "false");
	console << "\nThe product records are ";
	for (int i = 0; i < p.noMonths; i++) {
		console << " " << p.monthlySales[i];
	}
}

int main(int argc, char* argv[]) {
	float* sales = new float[]{ 10000,5000.5,10000,2000 };
	int noRecords = 4;

	Product p1(1, 23.5, false, sales, noRecords);
	Product p2(2, 20.5, true, sales, noRecords);

	p1.setDiscount();
	p1.setDiscount();
	p1.setDiscount();
	p1.setDiscount();
	p1.setDiscount();

	Product p3 = p2;
	Product p4(p2);

	cout << endl << "No of discounts : " << Product::getNoDiscounts();


	int vb1 = 10;
	int vb2 = 20;
	vb1 = vb1 + vb2;		//function+(int, int)
	cout << p1;				//function<<(cout,p1)
	cout << p2;
	//p1 = p1 + 10;
	//p1 += 10;

}