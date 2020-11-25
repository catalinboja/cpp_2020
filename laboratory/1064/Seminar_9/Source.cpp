#include <iostream>
#include <string>
using namespace std;

enum ProductType {NORMAL=100, DISCOUNT=200, PROMO=300};

class Test {

};

class Product {
public:
	const int id;
private:
	string name = "";
	int* sales = nullptr;
	int noMonths = 0;
	ProductType type = ProductType::NORMAL;
public:
	Product(int Id, string Name, ProductType Type): id(Id) {
		//this->id = Id;
		this->name = Name;
		this->type = Type;
	}
	~Product() {
		if (this->sales)
			delete[] this->sales;
	}

	void setSales(int* values, int no) {
		if (values != nullptr) {
			if (this->sales) {
				delete[] this->sales;
			}
			this->sales = new int[no];
			memcpy(this->sales, values, no * sizeof(int));
			this->noMonths = no;
		}
	}

	//we create an identical copy - including id
	Product(const Product& p): id(p.id) {
		this->name = p.name;
		this->type = p.type;
		this->setSales(p.sales, p.noMonths);
	}

	string getName() {
		return this->name;
	}

	void operator=(const Product& p) {

		//check for same object
		if (this == &p) {
			return;
		}

		//p.name = this->name;
		this->name = p.name;
		this->type = p.type;
		this->setSales(p.sales, p.noMonths);
	}

	void addNewRecord(int value) {
		int* newSales = new int[this->noMonths + 1];
		memcpy(newSales, this->sales, this->noMonths * sizeof(int));
		newSales[this->noMonths] = value;
		delete[] this->sales;
		this->sales = newSales;
		this->noMonths += 1;
	}

	//pre increment
	//incrementation is done before returning the object value
	Product operator++() {
		this->addNewRecord(0);
		return *this;
	}

	//post increment
	//incrementation is done after you return the object value
	Product operator++(int ) {
		Product copy = *this;
		this->addNewRecord(0);
		return copy;
	}

	friend ostream& operator<<(ostream& console, Product& p);
	friend void operator>>(istream& input, Product& p);
	friend class Test;
};

ostream& operator<<(ostream& console, Product& p) {
	console << endl << "---------------------------";
	console << endl << "Id = " << p.id;
	console << endl << "Name = " << p.getName();
	console << endl << "Type = " << p.type;
	if (p.sales != nullptr) {
		console << endl << "Previous data: ";
		for (int i = 0; i < p.noMonths; i++) {
			console << " " << p.sales[i];
		}
	}
	return console;
}

void operator>>(istream& input, Product& p) {
	cout << endl << "Name: ";
	input >> p.name;
	cout << endl << "Type (100,200,300): ";
	//input >> p.type;
	int type;
	input >> type;
	switch (type) {
	case 100:
		p.type = ProductType::NORMAL;
		break;
	case 200:
		p.type = ProductType::DISCOUNT;
		break;
	case 300:
		p.type = ProductType::PROMO;
		break;
	default:
		p.type = ProductType::NORMAL;
	}


	int no;
	int* data;
	cout << endl << "No of previous records: ";
	input >> no;
	data = new int[no];
	for (int i = 0; i < no; i++) {
		cout << endl << "Record " << i+1 <<": ";
		input >> data[i];
	}
	p.setSales(data, no);
	delete[] data;

	//char buffer[10000];
	//char* description = nullptr;
	//cout << endl << "Product description: ";
	//input >> buffer;
	//description = new char[strlen(buffer) + 1];
	//strcpy(description, buffer);

}

int main(int argc, char* argv[]) {
	Product p1(1, "Pepsi", ProductType::DISCOUNT);
	Product p2(2, "Coca-Cola", ProductType::PROMO);

	cout << p1;
	cout << p2;
	cout << p1 << p2;
	//p1 << p2;

	cin >> p1;
	cout << p1;

	p1 = p2;
	//p1 = p1;

	p2 = ++p1;
	p2 = p1++;
}