#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	float price = 0;
	string name = "";
public:
	Product(string Name, float Price) : name(Name), price(Price) {

	}

	float getPrice() {
		return this->price;
	}

	virtual void getDescription() {
		cout << endl << "The product " << this->name << " has a price of " <<
			this->price;
	}
};

class DiscountProduct : public Product {
	float discountPercent = 0;
public:
	DiscountProduct() : Product("Nothing", 0) {

	}

	DiscountProduct(string Name, float Price, float Discount)
		:Product(Name, Price), discountPercent(Discount)
	{

	}

	void getDiscountDescription() {
		this->getDescription();
		cout << endl << "The discount is " << this->discountPercent;
	}

	void getDescription() {
		this->Product::getDescription();
		cout << endl << "The discount is " << this->discountPercent << "%";
	}

	void getdescription() {
		cout << endl << "bla bla";
	}
};

class Toy: public Product {
	int minAge;
public:
	Toy(string Name, float Price, int Age): Product(Name, Price) {
		this->minAge = Age;
	}

	void getDescription() {
		cout << endl << "The toy " << this->name << " has a price of " << this->price;
		cout << endl << "Not suited for kids under " << this->minAge;
	}

	void pushButon() {
		cout << endl << "The toy starts running";
	}
};

class AbstractPerson {
	int age;

	virtual void doSomethingImportant() = 0;		//virtual pure functions
	virtual void doAnAction() = 0;
};

class Student : public AbstractPerson {
	void doSomethingImportant() {
		cout << endl << "Important";
	}

	void doAnAction() {
		cout << endl << "An action";
	}
};

class Professor : public AbstractPerson {

};

int main() {

	Student student;
	//Professor prof;
	//AbstractPerson person;

	AbstractPerson* p;
	p = &student;
	AbstractPerson* persons[5];



	Product product("Pepsi", 100);
	product.getDescription();
	DiscountProduct discount;
	DiscountProduct discount2("Apples", 2.5, 20);

	discount2.getDescription();
	//discount2.getDiscountDescription();

	Toy toy("RC Tank", 150, 5);
	toy.getDescription();

	Product product2("Nothing", 0);
	product2 = toy;			//UP CASTING at object level
	Product* pProduct = nullptr;
	pProduct = &product;
	pProduct = &toy;		//UP CASTING at pointer level

	Toy* pToy = nullptr;
	pToy = &toy;
	//pToy = &product;		//DOWN CASTING - does not work by default

	//an array of parent objects
	//Product products[5];
	//products[0] = toy;
	//products[1] = discount2;

	//an array of pointers to Parent objects
	Product* list[5];
	list[0] = &product;
	list[1] = &toy;
	list[2] = &discount2;
	list[3] = new Product("Fanta", 2.7);
	list[4] = new Toy("Puzzle", 15, 3);

	cout << endl << "-----------------------------";
	for (int i = 0; i < 5; i++) {
		list[i]->getDescription();			//early-binding without virtual methods
		//list[i]->_vfptr[0]();				//late-binding 

		//do a safe DOWN CAST
		Toy* pToy = dynamic_cast<Toy*>(list[i]);
		if (pToy != nullptr) {
			pToy->pushButon();
		}
	}



	//int n = 1000;
	//Product* * catalogue = new Product*[n];
	//for (int i = 0; i < 1000; i++) {
	//	catalogue[i] = new Product("Nothing", 0);
	//	//catalogue[i] = &product2;
	//	//catalogue[i] = nullptr;
	//}

	////catalogue[0]->price = 99;
	////catalogue[1]->price = 60;

	//catalogue[0] = &product2;

}
