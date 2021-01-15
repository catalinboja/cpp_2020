#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name = "";
	float price = 0;
	char* description = nullptr;
	//__vfptr[]			//an array of pointers to all the virtual methods in the class
public:
	Product(string Name, float Price): name(Name), price(Price) {
		this->description = nullptr;
	}

	float getPrice() {
		return this->price;
	}


	//__vfptr[0] - stores the address of getDescription from Product
	virtual void getDescription() {
		cout << endl << "The product " << this->name << " has a price of " << this->price;
	}
};

class Toy : public Product {
	int minAge;
public:
	Toy(string Name, float Price, int Age) : Product(Name, Price), minAge(Age) {

	}


	//by overriding __vfptr[0] has now the address of getDescription from Toy
	void getDescription() {
		this->Product::getDescription();
		cout << endl << "The toy is NOT for kids under " << this->minAge;
	}

	void doSomething() {
		this->getPrice();
	}
};

class Monitor : public Product {
	int diagonal;
public:
	Monitor(string Name, float Price, int Diagonal) : Product(Name, Price) {
		this->diagonal = Diagonal;
	}

	void getDescription() {
		cout << endl << "The monitor " << this->name << " costs " << this->price << " RON";
		cout << endl << "Its diagonal has " << this->diagonal << " inch";
	}

	void powerOn() {
		cout << endl << "Power on";
	}
};

class Person {
public:
	int age;
	string name;
	virtual void doSomething() = 0;			//virtual pure method - a virtual method without implementation
};

class Student : public Person {
public:
	void doSomething() {

	}
};

class Prof : public Person {

};

int main() {

	Student student;


	Product product("Laptop", 1500);
	product.getDescription();
	Toy toy("RC Speedboat",250,10);
	toy.getDescription();
	Monitor monitor("HP", 700, 24);
	monitor.getDescription();

	//toy.getPrice();

	//up-cast
	Product testProduct("", 0);
	testProduct = monitor;			//at object level
	testProduct.getDescription();
	Product* pProduct;
	pProduct = &product;
	pProduct = &monitor;			//at pointer level

	//down-cast
	//monitor = testProduct;
	//it's dangerous with proper checks
	//Monitor* pMonitor = (Monitor*)&product;
	//pMonitor->getDescription();

	//Product p;
	Product p("Test", 1);

	//Product* p = new Product();
	Product* pProd = new Product("Test 2", 1);

	Product* p2;			//defining a pointer DOES NOT MEAN creating an object

	//Product products[5];	//IS ALWAYS CALLING THE default constructor 
	Product* products[5];
	products[0] = &product;
	products[1] = &toy;
	products[2] = &monitor;
	products[3] = new Toy("Ball",5,3);
	products[4] = new Monitor("Samsung", 250, 23);

	cout << endl << "-----------------";
	for (int i = 0; i < 5; i++) {
		products[i]->getDescription();			//early-binding 
		//products[i]->__vfptr[0]();			//late-binding with virtual methods

		//doing the down-cast in a safe way
		Monitor* m = dynamic_cast<Monitor*>(products[i]);
		if (m != nullptr) {
			m->powerOn();
		}
	}

}