#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class ProdusComercial {
	//implicit private deoarece incapsulare
	unsigned int id = 0;
	float pret = 0;
	char* denumire = nullptr;
	string descriere = "";
	char alteInformatii[100];
public:

	ProdusComercial() {

	}



	//interfata publica a clasei - colectie de metode
	int getId() {
		//return (*this).id;
		return this->id;
	}

	char* getAlteInformatii() {
		return this->alteInformatii;
	}

	void printInfo() {
		cout << endl << "-------------------------";
		cout << endl << "Id: " << this->id;
		cout << endl << "Pret: " << this->pret;
		if (this->denumire != nullptr) {
			cout << endl << "Denumire: " << this->denumire;
		}
		else
		{
			cout << endl << "Fara denumire";
		}
		cout << endl << "Descriere: " << this->descriere;
		cout << endl << "Alte info: " << this->alteInformatii;
	}

	void setAlteInformatii(char* alteInformatii) {
		//pentru vectori statici
		//NU merge pentru ca pointerul catre vectorii statici este constant
		//this->alteInformatii = info;
		if (strlen(alteInformatii) <= 99) {
			strcpy(this->alteInformatii, alteInformatii);
		}
		else
		{
			throw "Valorea gresita pentru alte informatii";
		}
	}

	void setDescriere(string descriere) {
		//string test = "Ceva";
		//test = test + " altceva";

		//acceptam doar descrieri cu minim 5 caractere
		if (descriere.size() >= 5) {
			this->descriere = descriere;
		}
		else {
			throw "Descriere prea mica";
		}
	}

	void setDenumire(char* denumire) {
		

		//evitare memory leak
		if (this->denumire != nullptr)
			delete[] this->denumire;

		//1 creare spatiu
		this->denumire = new char[strlen(denumire) + 1];
		//2 copiere
		//this->denumire = denumire;		NU ASA
		strcpy(this->denumire, denumire);

	}

	void setPret(float pret) {
		//shadowing
		//pret = pret;
		this->pret = pret;
	}
};

int suma(int a, int b) {
	return a + b;
}

int diferenta(int a, int b) {
	return a - b;
}

int operatii(int a, int b, int tipOperatie) {
	if (tipOperatie == 1)
		return suma(a,b);
	if (tipOperatie == 2)
		return diferenta(a, b);
}

int operatiiSmart(int a, int b, int(* pf)(int, int)) {
	return pf(a, b);
}

int ceva() {

}

int ceva(int a) {

}

int ceva(int a, int b) {

}

ostream& operator<< (ostream&, ProdusComercial) {

}

int main(int argc, char* argv[]) {
	ProdusComercial produs1;
	ProdusComercial produs2;

	produs1.getId();
	//apeleaza ProdusComercial.getId(&produs1)

	produs2.getId();

	//cout << endl << "Info produs: " << produs1.getAlteInformatii();

	produs1.printInfo();

	cout << endl << "Suma este " << operatiiSmart(2, 3, suma);
	cout << endl << "Diferenta este " << operatiiSmart(2, 3, diferenta);

	produs1.setPret(100);

	const char* test = "Nimic";

	char* pepsi = new char[6] {"Pepsi"};

	produs1.setDenumire(pepsi);
	//produs1.setDenumire("Coca Cola");

	produs1.printInfo();

	cout << produs1;

}