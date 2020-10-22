#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

class Product {
//	private: - added by default
	unsigned int id = 0;		//4B
	float price = 0;			//4B
public:
	bool isFragile = false;			//1B
	char name[50] = "Nothing";			//50B
private:
	int* salesVolume = nullptr;			//sales recorded each month		//4B
	int noMonths = 0;			//4B
							//Total: 67B

public:
	//accessor methods
	//give read and/or write accesss (rights) on private attributes
	int getId() {
		//receives by default the address of the  object that will call this method
		//that address is stored in the this pointer
		return this->id;	
	}

	float getPrice() {
		return this->price;
	}

	//we don't need it because is already public
	//bool getIsFragile() {
	//	return this->isFragile;
	//}

	int* getSalesVolume() {
		return this->salesVolume;
	}

	int getNoMonths() {
		return this->noMonths;
	}

	void printProductData() {
		cout << endl << "------------------------------------";
		cout << endl << "The product name is " << this->name;
		cout << endl << "The product id is " << this->id;
		cout << endl << "The product price is " << this->price;
		cout << endl << "The product no of monthly records " << this->noMonths;
		cout << endl << "The product is fragile " << (this->isFragile ? "yes" : "no");
		if (this->salesVolume != nullptr) {
			cout << endl << "Sales volume: ";
			for (int i = 0; i < this->noMonths; i++) {
				cout << " " << this->salesVolume[i];
			}
		}
		else {
			cout << endl << "No sales records";
		}

	}

	//for write access
	void setPrice(float value) {
		if (value > 0) {
			this->price = value;
		}
		else {
			throw "Wrong value";
		}
	}
};

int main(int argc, char* argv[]) {

	//create an object
	Product prod1;
	//prod1.name[9] = '\0';
	strcpy(prod1.name, "Milk"); 
	prod1.setPrice(23);

	//cout << endl << "The size of a product is " << sizeof(prod1);	//it's different than 67 because of cache optimization - compiler
	//cout << endl << "The product name is " << prod1.name;
	//cout << endl << "The product id is " << prod1.getId();
	//cout << endl << "The product no of monthly records " << prod1.getNoMonths();
	//cout << endl << "The product is fragile " << (prod1.isFragile ? "yes" : "no");
	//
	//int* sales = prod1.getSalesVolume();

	//if (sales != nullptr) {
	//	cout << endl << "The product volume sales for 1st month "
	//		<< prod1.getSalesVolume()[0];
	//	cout << endl << "The product volume sales for 1st month "
	//		<< sales[0];
	//}

	prod1.printProductData();

}