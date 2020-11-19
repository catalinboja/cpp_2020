#include <iostream>
#include <string>
using namespace std;

enum ProductType {NORMAL = 100, FAST_SALE = 200, PROMO = 300};

class Product {
	const int id;
	string name = "";
	ProductType type = ProductType::NORMAL;
	int* sales = nullptr;
	int noMonths = 0;
public:
	Product(int Id, string Name, ProductType Type): id(Id) {
		this->name = Name;
		this->type = Type;
	}

	void setSales(int* sales, int no) {
		if (sales != nullptr) {
			if (this->sales)
				delete[]  this->sales;
			this->sales = new int[no];
			memcpy(this->sales, sales, no * sizeof(int));
			this->noMonths = no;
		}
	}

	Product(const Product& p): id(p.id) {
		this->type = p.type;
		this->name = p.name;
		this->setSales(p.sales, p.noMonths);
	}

	~Product() {
		if (this->sales) {
			delete[] this->sales;
		}
	}

	Product operator=(const Product& p) {

		//check for same object
		if (this != &p) {
			//this->id = p.id;
			this->name = p.name;
			this->type = p.type;
			this->setSales(p.sales, p.noMonths);
		}

		//return p;
		return *this;
	}

	Product operator+(int value) {
		Product result = *this;

		if (result.sales)
			delete[] result.sales;
		result.sales = new int[result.noMonths + 1];
		memcpy(result.sales, this->sales, this->noMonths * sizeof(int));
		result.sales[result.noMonths] = value;
		result.noMonths += 1;

		return result;
	}

	void operator+=(int value) {
		*this = *this + value;
	}

	//cast operator
	explicit operator int() {
		int total = 0;
		for (int i = 0; i < this->noMonths; i++) {
			total += this->sales[i];
		}
		return total;
	}

	friend ostream& operator<<(ostream& console, const Product& p);
	friend void operator>>(istream& input, Product& p);
};

ostream& operator<<(ostream& console, const Product& p) {
	//p.name = "test";
	console << endl << "--------------------------------------";
	console << endl << "Id = " << p.id;
	console << endl << "Name = " << p.name;
	console << endl << "Type = " << p.type;
	if (p.sales != nullptr) {
		console << endl << "The sales array is ";
		for (int i = 0; i < p.noMonths; i++) {
			console << " " << p.sales[i];
		}
	}
	return console;
}

void operator>>(istream& input, Product& p) {
	//cout << endl << "The id = ";
	//input >> p.id;

	cout << endl << "The name: ";
	input >> p.name;

	//char *
	//char* name;
	//char buffer[1000];
	//input >> buffer;
	//name = new char[strlen(buffer) + 1];
	//strcpy(name, buffer);

	//string buffer2;
	//input >> buffer2;
	//name = new char[buffer2.size() + 1];
	//strcpy(name, buffer2.c_str());

	cout << endl << "The type: ";
	//input >> p.type;
	int type;
	input >> type;
	switch (type)
	{
	case 100:
		p.type = ProductType::NORMAL;
		break;
	case 200:
		p.type = ProductType::FAST_SALE;
		break;
	case 300:
		p.type = ProductType::PROMO;
		break;
	default:
		p.type = ProductType::NORMAL;
		break;
	}

	int no;
	int* sales;

	cout << endl << "No previous sales records: ";
	input >> no;
	cout << endl << "The values are ";
	sales = new int[no];
	for (int i = 0; i < no; i++) {
		cout << endl << "Record " << i + 1 << ": ";
		input >> sales[i];
	}

	p.setSales(sales, no);

	delete[] sales;

}

Product operator+(int value, Product p) {
	return p + value;
}

int main(int argc, char* argv[]) {
	Product p1(1,"Pepsi",ProductType::PROMO);
	Product p2(2,"Coca Cola",ProductType::NORMAL);
	Product p3 = p2;

	cout << p1;		//operator<<(cout, p1)
	cout << p1 << p2;
	//cin >> p1;

	cout << p1;

	p2 = p1;
	//p2 = p2;

	cout << p2;

	Product p4 = p1;	//copy ctor
	p4 = p2 + 50;

	cout << p4;
	
	p4 = 10 + p4;

	cout << p4;

	p4 += 60;

	cout << p4;
	
	int totalSales = (int)p4;		//operator int(p4)

	cout << endl << " Total sales " << totalSales;

	//p2 * 10;
}