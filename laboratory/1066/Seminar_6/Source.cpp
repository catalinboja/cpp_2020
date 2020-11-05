
#include <iostream>
#include <string>

using namespace std;


class Product {

	unsigned int id = 0;
	string name = "";
	float* montlhySales = nullptr;
	int noMonths = 0;

	static int counter;
	const static int MIN_SALES_FILTER = 1000;

public:
	Product() {
		//this->counter += 1;
		//counter += 1;
		Product::counter += 1;
	}

	Product(int id) {
		this->id = id;
		this->name = "No name";
		Product::counter += 1;
	}

	~Product() {
		if (this->montlhySales) {
			delete[] this->montlhySales;
		}

		Product::counter -= 1;

	}

	//define the constructor that requires arguments for all attributes
	// test in main by creating an object using it - use your name for the Product name
	//


	int getCounter() {
		return Product::counter;
	}

	void setMonthlySales(float* records, int noRecords) {
		if (this->montlhySales != nullptr) {
			delete[] this->montlhySales;
		}
		this->montlhySales = new float[noRecords];
		for (int i = 0; i < noRecords; i++) {
			this->montlhySales[i] = records[i];
		}
		this->noMonths = noRecords;
	}

	void printProduct() {
		cout << endl << "---------------------------";
		cout << endl << " ID = " << this->id;
		cout << endl << " Name = " << this->name;
		cout << endl << " Records: ";
		for (int i = 0; i < this->noMonths; i++) {
			cout << " " << this->montlhySales[i];
		}
	}

	//counting how many months have sale volumes > filter
	int getBestMonthsNumber() {
		int no = 0;
		for (int i = 0; i < this->noMonths; i++) {
			if (this->montlhySales[i] >= MIN_SALES_FILTER)
			{
				no += 1;
			}
		}
		return no;
	}
};

int Product::counter = 0;


int main(int argc, char* argv[]) {
	//default ctors
	Product p1, p2;
	Product p3;

	//ctor with arguments
	Product p4(4);

	Product* pProd = new Product();
	Product* pProd2 = new Product(5);

	cout << endl << "The number of Products is " << p1.getCounter();

	float* records = new float[] {100, 5000, 1200, 7};
	int noRecords = 4;

	p4.setMonthlySales(records, noRecords);
	p4.printProduct();
	p1.printProduct();

	cout << endl << "No best months = " << p4.getBestMonthsNumber();

	pProd->setMonthlySales(records, noRecords);

	delete pProd;
	delete pProd2;

	cout << endl << "The number of Products is " << p1.getCounter();

}


