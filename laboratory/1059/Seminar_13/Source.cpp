#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Produs {
protected:
	string denumire = "";
	float pret = 0;
	char* descriere = nullptr;
public:
	Produs(string Denumire, float Pret): denumire(Denumire), pret(Pret) {

	}

	Produs(string Denumire, float Pret, const char* Descriere) : denumire(Denumire), pret(Pret) {
		this->descriere = new char[strlen(Descriere)];
		strcpy(this->descriere, Descriere);
	}

	//Produs() {

	//}

	float getPret() {
		return this->pret;
	}

	virtual void getDescriere() {
		cout << endl << "Produsul " << this->denumire << " are pretul " << this->pret;
	}
};

class Jucarie : public Produs {
	int varstaMinima = 0;
public:
	Jucarie() : Produs("Nimic", 0) {

	}

	Jucarie(string Denumire, float Pret, int Varsta): Produs(Denumire, Pret) {
		this->varstaMinima = Varsta;
	}

	//supradefinire
	void getDescriere() {
		cout << endl << "Jucaria " << this->denumire << " are pretul " << this->pret;
		cout << endl << "Si varsta minima este " << this->varstaMinima;
	}
};

class Laptop : public Produs {
	int diagonalaEcran;
public:
	Laptop(string Denumire, float Pret, int Diagonala)
		:Produs(Denumire, Pret), diagonalaEcran(Diagonala) {

	}

	void getDescriereLaptop() {
		this->getDescriere();
		cout << endl << "Si are o diagonala de " << this->diagonalaEcran;
	}

	//supradefinire
	void getDescriere() {
		//cout << endl << "Produsul " << this->denumire << " are pretul " << this->pret;
		this->Produs::getDescriere();
		cout << endl << "Si are o diagonala de " << this->diagonalaEcran;
	}
};

int main() {
	Produs p1("Laptop", 1000);
	Produs p2("Monitor", 500, "Diagonala 14 inch");
	p1.getDescriere();
	p2.getDescriere();

	Jucarie jucarie;
	Jucarie jucarie2("Masina teleghidata", 100, 10);

	jucarie.getDescriere();
	jucarie2.getDescriere();

	Laptop laptop1("Lenovo", 1500, 14);
	laptop1.getDescriere();
	//laptop1.getDescriereLaptop();

	//up-casting
	p1 = laptop1;			// la nivel de obiect
	Produs* pProdus;
	pProdus = &p1;
	pProdus = &laptop1;		//la nivel de pointeri/adrese

	//down-casting
	//laptop1 = p1;

	//Produs produse[5];
	//produse[0] = p1;
	//produse[1] = p2;
	//produse[2] = jucarie;		//pret|denumire|descriere|varsta
	//produse[3] = jucarie2;
	//produse[4] = laptop1;

	Produs* produse[5];
	produse[0] = new Produs("Biscuiti",25,"nimic");
	produse[1] = &p2;
	produse[2] = &jucarie;
	produse[3] = &jucarie2;		//@[pret|denumire|descriere|varsta]
	produse[4] = &laptop1;		//@[pret|denumire|descriere|diagonala]

	cout << endl << "-------------------";
	for (int i = 0; i < 5; i++) {
		produse[i]->getDescriere();		//early-binding
		//produse[i]->_vfptr[0]();		//late-binding

		//Laptop* pLaptop = (Laptop*)produse[i];

		Laptop* pLaptop = dynamic_cast<Laptop*>(produse[i]);
		if (pLaptop != nullptr) {
			cout << endl << "Am gasit un laptop";
		}
	}

}