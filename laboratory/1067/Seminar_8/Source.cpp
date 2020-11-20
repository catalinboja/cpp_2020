#include <iostream>
#include <string>

using namespace std;

enum ProductType { NORMAL = 100, DISCOUNT = 200, PROMO = 300 };

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

	void setSales(int* sales, int no) {
		if (sales != nullptr) {
			if (this->sales) {
				delete[] this->sales;
			}
			this->sales = new int[no];
			memcpy(this->sales, sales, no * sizeof(int));
			this->noMonths = no;
		}
	}

	//we choose to copy also the id
	Product(const Product& p): id(p.id) {
		this->name = p.name;
		this->type = p.type;
		this->setSales(p.sales, p.noMonths);
	}

	~Product() {
		if (this->sales) {
			delete[] this->sales;
		}
	}

	//inner space
	//class member function

	void operator=(const Product& p) {

		//check for same object
		if (this == &p) {
			return;
		}

		//this->id = p.id;
		this->name = p.name;
		this->type = p.type;
		this->setSales(p.sales, p.noMonths);
	}

	void operator+=(int value) {
		for (int i = 0; i < this->noMonths; i++) {
			this->sales[i] += value;
		}
	}

	//cast 
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

//global space
//global methods

ostream& operator<<(ostream& console, const Product& p) {
	//p.name = "test";
	console << endl << "--------------------";
	console << endl << "Id = " << p.id;
	console << endl << "Name = " << p.name;
	console << endl << "Type = " << p.type;
	if (p.sales != nullptr) {
		console << endl << "Sales records: ";
		for (int i = 0; i < p.noMonths; i++) {
			console << " " << p.sales[i];
		}
	}
	return console;
}

void operator>>(istream& input, Product& p) {
	//cout << "Id = ";
	//input >> p.id;
	cout << endl << "Name = ";
	input >> p.name;
	cout << endl << "Type = ";
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

	cout << endl << "No of previous months: ";
	int no;
	input >> no;

	int* temp = new int[no];
	for (int i = 0; i < no; i++) {
		cout << endl << "Month " << i + 1 << ": ";
		input >> temp[i];
	}

	p.setSales(temp, no);

	//char buffer[1000];
	//char* name;
	////cout << endl << "No of caharacters in the name ";
	//input >> buffer;
	//name = new char[strlen(buffer) + 1];
	//strcpy(name, buffer);
}

int main() {
	Product p1(1,"Pepsi",ProductType::PROMO);
	Product p2(2,"Coca Cola",ProductType::NORMAL);

	cout << p1;		//operator<<(cout, p1)
	cout << p2;
	cout << p1 << p2;

	cin >> p1;		//operator>>(cin, p1);
	//cout << p1;

	//p1 = p2;

	p1 += 10;			//increase sales with 10 for each month
	int totalSales = (int)p1;		//operator int(p1)
	cout << endl << totalSales;
	//p1 * 10;

	//[]
	//++ / --
}