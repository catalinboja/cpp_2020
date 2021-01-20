#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name = "";
	float price = 0;
	char* description = nullptr;
	//__vfptr[]
public:
	Product(string Name, float Price) :name(Name), price(Price) {

	}

	float getPrice() {
		return this->price;
	}
	virtual void getDescription() {
		cout << endl << "The product " << this->name << " has a price of "
			<< this->price;
	}
};

class Toy : public Product {
	int minAge = 0;
	//__vfptr[]
public:
	Toy():Product("No name",0) {
	}
	Toy(string Name, float Price, int Age) :Product(Name, Price) {
		this->minAge = Age;
	}

	void getToyDescription() {
		cout << endl << "The product " << this->name << " has a price of "
			<< this->price;
		cout << endl << "Is for kids above " << this->minAge;
	}

	void getDescription() {
		//this->Product::getDescription();
		cout << endl << "The toy " << this->name << " has a price of "
			<< this->price;
		cout << endl << "Is for kids above " << this->minAge;
	}
};

class ComputerMonitor : public Product {
	int diagonal = 0;
public:
	ComputerMonitor(string Name, float Price, int Size) :Product(Name, Price)
	{
		this->diagonal = Size;
	}
	void getDescription() {
		cout << endl << "The monitor " << this->name << " has a price of "
			<< this->price;
		cout << endl << "The diagonal is " << this->diagonal << " inch";
	}
};

int main() {
	Product product("Laptop", 1000);
	product.getDescription();

	Toy toy("RC Speedboat",250,10);
	toy.getDescription();
	toy.getToyDescription();
	ComputerMonitor monitor("Dell", 700, 24);

	//up-casting
	//at object level
	product = toy;
	product = monitor;
	//at pointers level
	Product* p;
	p = &product;
	p = &toy;
	p = &monitor;

	//down-casting
	//monitor = product;
	//ComputerMonitor* cm = &product;

	//Product products[5];
	//products[0] = toy;

	Product* products[5];
	int size = 0;
	Product* *listProducts = new Product*[size];
	products[0] = &product;
	products[1] = &toy;
	products[2] = &monitor;
	products[3] = new Toy("Ball",12,3);
	products[4] = new ComputerMonitor("HP", 279, 23);

	cout << endl << "-------------------";

	for (int i = 0; i < 5; i++) {
		products[i]->getDescription();		//early-binding without virtual
		//products[i]->__vfptr[0]();			//late-binding

		Toy* pToy = dynamic_cast<Toy*>(products[i]);
		if (pToy != nullptr) {
			cout << endl << "It's a Toy";
			pToy->getToyDescription();
		}
	}

}