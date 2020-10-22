#include <iostream>
using namespace std;

class ProdusComercial {
private:			//este implicit si daca nu-l scriem
	unsigned int id;
	float pret;			// te rog frumos - doar valori pozitive
public:
	bool esteProdusAlimentar;
private:
	char denumire[50];
	int* volumVanzariLunare;
	int nrLuni;

	//interfata publica a clasei
	//metode accesor - dau acces in mod citire si/sau scriere la atributele private
public:
	int getId() {
		//primeste implicit adresa obiectului care va apela metoda
		//adresa este stocata in pointerul ProdusComercial* this
		return this->id;
	}

	float getPret() {
		return this->pret;
	}

	char* getDenumire() {
		return this->denumire;
	}

	int getNrLuni() {
		return this->nrLuni;
	}

	//nu este ok dar merge pentru azi
	int* getVolumVanzari() {
		return this->volumVanzariLunare;
	}

	//functii accesor pentru a da acces in mod scriere
	void setPret(float pretNou) {
		//validam input-ul
		if (pretNou > 0) {
			this->pret = pretNou;
		}
		else {
			//un mesaj
			throw "Valoare nu este ok";
		}
	}

	void printInfo() {
		cout << endl << "---------------------------------";
		cout << endl << "Denumire produs " << this->denumire;
		cout << endl << "Id produs " << this->id;
		cout << endl << "Pret produs " << this->pret;

		cout << endl << "Produsul este alimentar: "
			<< (this->esteProdusAlimentar ? "da" : "nu");

		cout << endl << "Nr luni vanzari " << this->nrLuni;
		cout << endl << "Vanzari lunare: ";
		for (int i = 0; i < this->nrLuni; i++) {
			cout << " " << this->volumVanzariLunare[i];
		}
	}

};

int main(int argc, char* argv[]) {

	int variabila;
	ProdusComercial produs;
	ProdusComercial produs2;

	produs.esteProdusAlimentar = true;
	//if (produs.esteProdusAlimentar) {
	//	cout << endl << "Produsul este alimentar: da";
	//}
	//else{
	//	cout << endl << "Produsul este alimentar: nu";
	//}

	cout << endl << "Produsul este alimentar: "
		<< (produs.esteProdusAlimentar ? "da" : "nu");

	cout << endl << "Id-ul este " << produs.getId();
	cout << endl << "Id-ul este " << produs2.getId();

	ProdusComercial* pProdus = &produs;
	cout << endl << "Produsul este alimentar: "
		<< (pProdus->esteProdusAlimentar ? "da" : "nu");

	cout << endl << "Produsul este alimentar: "
		<< ((*pProdus).esteProdusAlimentar ? "da" : "nu");

	//produs.setPret(-23);		//arunca exceptie
	produs.setPret(100);
	cout << endl << "Pretul este " << produs.getPret();

	produs.printInfo();

}