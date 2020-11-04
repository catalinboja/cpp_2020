
#include "Header.h"

int main(int argc, char* argv[]) {

	printMsg("Let's start");

	Product product1;
	Product product2;

	product1.printInfo();
	product1.setProducer("Pepsi CO");
	product1.setName("Pepsi");
	product1.setName("Mirinda");
	product1.setDescription("Something for hot days");
	product1.printInfo();


	Product* pProduct;

	void* genericPointer; // Object reference in C# and Java

}