
#include <iostream>
#include "Seminar6.h"

int main(int argc, char* argv[]) {
	printMessage("Let's start");

	Product p1;
	Product p2;
	Product* pProduct = new Product();

	cout << endl << "Number of objects " << p1.getObjCounter();

	Product p3(3);
	Product* pProduct2 = new Product(4);

	float* records = new float[] {1000, 500, 5000, 23};
	int noRecords = 4;

	p3.setMonthlySales(records, noRecords);
	pProduct2->setMonthlySales(records, noRecords);

	delete pProduct2;

	cout << endl << "Number of objects " << p1.getObjCounter();
}

