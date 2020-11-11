#include <iostream>
#include <string>
using namespace std;

class Product {
	unsigned int id = 0;
	string name = "";
	float* monthlySales = nullptr;
	int noMonths = 0;

	static int noObjects;

public:
	static const int MONTH_VALUE_FILTER = 5000;

	int getNoBestMonths() {
		if (this->monthlySales == nullptr) {
			return -1;
		}
		int counter = 0;
		for (int i = 0; i < this->noMonths; i += 1) {
			if (this->monthlySales[i] > MONTH_VALUE_FILTER) {
				counter += 1;
			}
		}

		return counter;
	}

	int getNoMonths() {
		return this->noMonths;
	}

	Product() {
		cout << endl << "The default ctor";
		//this->noObjects += 1;
		//noObjects += 1;
		Product::noObjects += 1;
	}

	Product(int id) {
		this->id = id;
		cout << endl << "The constructor with id";
		Product::noObjects += 1;
	}

	~Product() {
		cout << endl << "The destructor";
		Product::noObjects -= 1;
		if (this->monthlySales) {
			delete[] this->monthlySales;
		}
	}

	int getNoObjects() {
		return Product::noObjects;
	}

	void setMonthlySales(float* sales, int noMonths) {

		if (this->monthlySales != nullptr) {
			delete[] this->monthlySales;
		}
		this->noMonths = noMonths;
		this->monthlySales = new float[noMonths];
		
		for (int i = 0; i < noMonths; i++) {
			this->monthlySales[i] = sales[i];
		}

	}
};

int Product::noObjects = 0;

void doSomething() {
	Product temp;
}


int main(int argc, char* argv[]) {
	Product p1;
	Product p2;

	float* records = new float[] {6000, 45, 10000, 3670};
	int noMonths = 4;

	p1.setMonthlySales(records, noMonths);

	Product* addrProd = new Product();

	Product p3(3);
	Product* addrProd2 = new Product(4);

	delete addrProd2;

	cout << endl << "Calling doSomething";
	doSomething();

	cout << endl << "Number of best months for p1 = " << p1.getNoBestMonths();
	cout << endl << "Number of best months for Prod = " << addrProd->getNoBestMonths();

	cout << endl << "Number of objects in memory is " << p1.getNoObjects();
	
	delete addrProd;
}


