#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name = "";
	float price = 0;
	char* description = nullptr;

	//_vfptr[]			//array of pointers to all the virtual methods defined in the class
public:
	Product(string Name, float Price): name(Name), price(Price) {
		//this->name = Name;
	}

	//Product() {

	//}

	float getPrice() {
		return this->price;
	}

	//_vfptr[0]
	virtual void getDescription() {
		cout << endl << "The product " << this->name << " has a price of " << this->price;
	}
};

class Toy : public Product {
	int minAge = 0;
public:
	Toy(): Product("Nothing",0) {
	}

	Toy(string Name, float Price, int age) : Product(Name, Price) {
		this->minAge = age;
	}

	//override the parent version
	void getDescription() {
		cout << endl << "The toy " << this->name << " costs " << this->price;
		cout << endl << "It's not suited for kids under age " << this->minAge;
	}
};

class Laptop : public Product {
	int screenSize = 0;
public:
	Laptop(string Name, float Price, int ScreenSize)
		: Product(Name, Price), screenSize(ScreenSize) {

	}
	//override the parent version
	void getDescription() {
		this->Product::getDescription();
		cout << endl << "The screen size is " << this->screenSize << " inch";
	}
};


class AbstractPerson {
public:
	string name;

	virtual void print() {
		cout << endl << "This is a person";
	}

	virtual void doSomethingImportant() = 0;		// a virtual pure method
};

class Student: public AbstractPerson{
	void Print() {
		cout << endl << "This is a student";
	}

	virtual void doSomethingImportant() {
		cout << endl << "The student is doing something important";
	}
};

class Prof : public AbstractPerson {
	//I hate him
	//I don't want to override
};

int main() {

	Student student;
	//AbstractPerson person;
	AbstractPerson* person;
	AbstractPerson* persons[5];
	persons[0] = &student;

	//Prof* prof = new Prof();
	//prof->doSomethingImportant();


	Product p1("Laptop", 1500);
	p1.getDescription();
	Toy toy;
	toy.getDescription();
	Laptop laptop("Lenovo", 1800, 14);
	laptop.getDescription();

	//up-casting
	p1 = laptop;			//at object level
	Product* pProduct = &p1;
	pProduct = &laptop;		//at pointer level

	//down-casting
	//laptop = p1;
	//Laptop* pLaptop = &p1;

	//Product products[5];
	//products[0] = p1;
	//products[1] = toy;
	//products[2] = laptop;
	//products[3] = Laptop("HP",2000,15);
	//products[4] = Toy("RC Speedboat",250,10);

	Product* products[5];
	products[0] = &p1;
	products[1] = &toy;
	products[2] = &laptop;
	products[3] = new Laptop("HP", 2000, 15);
	products[4] = new Toy("RC Speedboat", 250, 10);


	cout << endl << "----------------";
	for (int i = 0; i < 5; i++) {
		products[i]->getDescription();		//early-binding
		//products[i]->_vfptr[0]();			//late-binding
	}

	int n = 10;
	Product* *list;
	list = new Product*[n];
	list[0] = &toy;
	list[1] = new Laptop("Lenovo", 2000, 15);
 
}
