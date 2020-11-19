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
	Product(const int Id, const string Name, const ProdType Type): id(Id) {
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

	Product(Product& p): id(p.id) {
		this->name = p.name;
		this->setSales(p.salesVolume, p.noMonths);
		this->type = p.type;
	}

	string getName() {
		return this->name;
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

int main(int argc, char* argv[]) {
	//Product p1;
	Product p1(1, "Pepsi", ProdType::NORMAL);
	Product p2(2, "Laptop", ProdType::DISCOUNT);

	cout << p1;			//operator<<(cout, p1)
	cout << p2;
	cout << p1 << p2;

	cin >> p1;
	cout << p1;

	char name[] = "John";
}