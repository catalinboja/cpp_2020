#include <iostream>
#include <string>
using namespace std;

class Produs {
protected:
	string denumire;
	float pret;
	int* valori = new int[10];
public:
	Produs(string Denumire, float Pret): denumire(Denumire), pret(Pret) {
		//this->pret = Pret;
		cout << endl << "Apel ctor Produs cu parametri";
	}

	Produs() {
		cout << endl << "Apel ctor default Produs";
	}

	float getPret() {
		return this->pret;
	}

	string getDescriere() {
		string descriere = "Produsul " + this->denumire + " are pretul " 
			+ to_string(this->pret);
		return descriere;
	}

	~Produs() {
		cout << endl << "Apel destructor Produs";
		if(this->valori!=nullptr)
			delete[] this->valori;
	}
};

class ProdusCuDiscount: public Produs {
protected:
	float discountInProcente = 0;					//10 ~ 10%
public:
	ProdusCuDiscount(): Produs("Fara denumire", 0) {
		this->discountInProcente = 0;
		cout << endl << "Apel ctor default ProdusCuDiscount ";
	}

	//ProdusCuDiscount(float discount): Produs("", 0) {
	//	this->discountInProcente = discount;
	//}

	ProdusCuDiscount(string Denumire, float Pret, float Discount):Produs(Denumire, Pret) {
		this->discountInProcente = Discount;
		cout << endl << "Apel ctor ProdusCuDiscount cu parametri";
	}

	float getValoareDiscount() {
		//return this->getPret() * (this->discountInProcente / 100);
		return this->pret * (this->discountInProcente / 100);
	}

	float getPretcuDiscount() {
		return this->pret - this->getValoareDiscount();
	}

	//supradefinire metoda din parinte
	float getPret() {
		//apel versiune din parinte
		float valoare = this->Produs::getPret();

		return valoare - this->getValoareDiscount();
	}

	~ProdusCuDiscount() {
		cout << endl << "Apel destructor ProdusCuDiscount";
		//delete[] this->valori;
		//this->valori = nullptr;
	}
};	

class ProdusPerisabil {
protected:
	string dataExpirare;
	string denumire;
public:
	ProdusPerisabil(string data, string denumire) {
		this->dataExpirare = data;
		this->denumire = denumire;
	}
};

class ProdusAlimentar : public ProdusCuDiscount, public ProdusPerisabil {
	string categorie;
public:
	ProdusAlimentar(
		string denumire, float pret, float discount, string data, string Denumire)
		:ProdusPerisabil(data, Denumire), ProdusCuDiscount(denumire, pret, discount) {
	}

	void oFunctie() {
		this->ProdusCuDiscount::denumire = "ceva";
		this->ProdusPerisabil::denumire = "ceva";
	}
};


int main() {
	//Produs p1;
	Produs p2("Laptop", 1500);
	cout << endl << p2.getDescriere();

	//float pret = p2.pret;

	cout << endl << "Pretul pentru produsul p2 este " << p2.getPret();

	ProdusCuDiscount pd1;
	ProdusCuDiscount pd2("Monitor", 750, 10);

	cout << endl << "Pretul pentru monitor este " << pd2.getPret();
	cout << endl << "Pretul pentru monitor este " << pd2.getPretcuDiscount();

	//ProdusAlimentar pa1;
}
