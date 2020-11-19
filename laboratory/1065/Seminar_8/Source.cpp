#include <iostream>
#include <string>
using namespace std;

enum ProdType {NORMAL, FAST_SALE = 100, DISCOUNT = 200};

class Product {
public:
	const int id;
private:
	string name = "";
	int* salesVolume = nullptr;
	int noMonths = 0;
	ProdType type = ProdType::NORMAL;
public:
	Product(int Id, string Name, ProdType Type): id(Id) {
		this->name = Name;
		this->type = Type;
	}
	~Product() {
		if (this->salesVolume) {
			delete[] this->salesVolume;
		}
	}

	void setSales(int* sales, int no) {
		if (sales != nullptr) {
			if (this->salesVolume) {
				delete[]  this->salesVolume;
			}
			this->salesVolume = new int[no];
			for (int i = 0; i < no; i++) {
				this->salesVolume[i] = sales[i];
			}
			this->noMonths = no;
		}
		/*else
			throw "We got null pointer";*/
	}

	Product(const Product& p): id(p.id) {
		this->name = p.name;
		this->setSales(p.salesVolume, p.noMonths);
		this->type = p.type;
	}

	string getName() {
		return this->name;
	}

	//void operator=(Product p)
	//void operator=(Product& p)
	Product operator=(const Product& p) {

		//check for self =
		if (p.id == this->id)
			return *this;

		this->type = p.type;
		this->name = p.name;
		//this->id = p.id;
		this->setSales(p.salesVolume, p.noMonths);
		//return p;		//but the copy ctor needs const Product&
		return *this;
	}

	Product operator+(int value) {
		Product result = *this;
		int* newSales = new int[result.noMonths + 1];
		for (int i = 0; i < result.noMonths; i++) {
			newSales[i] = result.salesVolume[i];
		}
		newSales[result.noMonths] = value;
		result.setSales(newSales, result.noMonths + 1);
		return result;
	}

	void operator+=(int value) {
		//*this = *this + value;
		int* newSales = new int[this->noMonths + 1];
		for (int i = 0; i < this->noMonths; i++) {
			newSales[i] = this->salesVolume[i];
		}
		newSales[this->noMonths] = value;
		this->setSales(newSales, this->noMonths + 1);
	}

	explicit operator int() {
		int total = 0;
		for (int i = 0; i < this->noMonths; i++) {
			total += this->salesVolume[i];
		}
		return total;
	}

	friend ostream& operator<<(ostream& console, Product& p);
	friend void operator >>(istream& input, Product& p);

};

ostream& operator<<(ostream& console, Product& p) {
	console << endl << "---------------------";
	console << endl << "Id = " << p.id;
	console << endl << "Name = " << p.getName();
	console << endl << "Type = " << p.type;
	if (p.salesVolume) {
		console << endl << "Sales records: ";
		for (int i = 0; i < p.noMonths; i++) {
			console << p.salesVolume[i] << " ";
		}
	}

	return console;
}

void operator >>(istream& input, Product& p) {
	//cout << endl << "New id = ";
	//input >> p.id;
	cout << endl << "New name: ";
	input >> p.name;
	cout << endl << "New type (0,100,200): ";
	int type;
	input >> type;
	switch (type)
	{
	case 0:
		p.type = ProdType::NORMAL;
		break;
	case 100:
		p.type = ProdType::FAST_SALE;
		break;
	case 200:
		p.type = ProdType::DISCOUNT;
	default:
		p.type = ProdType::NORMAL;
	}
	cout << endl << "Sales records no: ";
	int no;
	input >> no;

	//for reading a char* from console - we use a temp buffer
	//char buffer[1000];
	//input >> buffer;

	int* sales = new int[no];
	for (int i = 0; i < no; i++) {
		cout << endl << "Sales volume: ";
		input >> sales[i];
	}

	p.setSales(sales, no);

}

Product operator+(int value, Product p) {
	return p + value;
}

int main(int argc, char* argv[]) {
	//Product p1;
	Product p1(1, "Pepsi", ProdType::NORMAL);
	Product p2(2, "Laptop", ProdType::DISCOUNT);

	cout << p1;			//operator<<(cout, p1)
	cout << p2;
	cout << p1 << p2;

	//cin >> p1;
	//cout << p1;

	int sales[] = { 10,11,22 };
	int no = 3;
	p1.setSales(sales, no);

	p2 = p1;			//operator=(p2, p1)			//mandatory by a class member function

	Product p3 = p2;		//copy ctor

	p3 = p2 = p1;
	//p1 = p1;

	//p1 = p1 + 10;

	cout << p1;
	cout << p3;

	p2 = p1 + 10;
	cout << p2;
	p2 = 55 + p2;

	p2 += 10;

	int totalSales = (int)p2;			//operator int(p2)

	//p2 * 100;
}