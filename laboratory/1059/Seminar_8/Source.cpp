#include <iostream>
#include <string>
using namespace std;

enum TipProdus {NORMAL = 100, VANZARE_ACCELERATA = 200, PROMO = 300};

class Produs {
	const int id;
	string denumire = "";
	TipProdus tip = TipProdus::NORMAL;
	int* vanzari = nullptr;
	int nrLuni = 0;
	const int ceva;
	static int NR_INVENTAR;
public:
	Produs(int Id, string Denumire): id(Id), ceva(1) {
		//this->id = Id;
		this->denumire = Denumire;
		Produs::NR_INVENTAR += 1;
	}

	Produs(string denumire, TipProdus tip): id(Produs::NR_INVENTAR), ceva(-1) {
		this->denumire = denumire;
		this->tip = tip;
		Produs::NR_INVENTAR += 1;
	}

	void setVanzari(int* vanzari, int nr) {
		if (vanzari != nullptr) {
			if (this->vanzari) {
				delete[] this->vanzari;
			}
			this->vanzari = new int[nr];
			memcpy(this->vanzari, vanzari, nr * sizeof(int));
			this->nrLuni = nr;
		}
	}

	~Produs() {
		if (this->vanzari) {
			delete[] this->vanzari;
		}
	}

	Produs(const Produs& p): id(p.id), ceva(NR_INVENTAR) {
		this->denumire = p.denumire;
		this->tip = p.tip;
		this->setVanzari(p.vanzari, p.nrLuni);
	}

	Produs operator=(const Produs& p) {

		//verificare egalitate obiecte
		if (this->id != p.id) {
			//this->id = p.id;
			this->denumire = p.denumire;
			this->tip = p.tip;
			this->setVanzari(p.vanzari, p.nrLuni);
		}

		return *this;
	}

	friend void operator<<(ostream& consola, Produs p);
	friend void operator>>(istream& input, Produs& p);
};

int Produs::NR_INVENTAR = 0;

void operator<<(ostream& consola, Produs p) {
	consola << endl << "----------------";
	consola << endl << "Denumire: " << p.denumire;
	consola << endl << "Id: " << p.id;
	consola << endl << "Tip: " << p.tip;
	if (p.vanzari) {
		consola << endl << "Vanzari: ";
		for (int i = 0; i < p.nrLuni; i++) {
			consola << " " << p.vanzari[i];
		}
	}
}

void operator>>(istream& input, Produs& p) {
	//cout << "Id = ";
	//input >> p.id;
	cout << endl << "Denumire: ";
	input >> p.denumire;

	//pt char*
	//char buffer[1000];
	//input >> buffer;
	//char* nume = new char[strlen(buffer) + 1];
	//strcpy(nume, buffer);

	cout << endl << "Tip: ";
	//input >> p.tip;
	int tip;
	input >> tip;
	switch (tip) {
	case 100:
		p.tip = TipProdus::NORMAL;
		break;
	case 200:
		p.tip = TipProdus::VANZARE_ACCELERATA;
		break;
	case 300:
		p.tip = TipProdus::PROMO;
		break;
	default:
		p.tip = TipProdus::NORMAL;
	}

	cout << endl << "Vanzari:";
	cout << endl << "Numar luni: ";
	int nrLuni;
	input >> nrLuni;
	int* vanzari = new int[nrLuni];
	for (int i = 0; i < nrLuni; i++) {
		cout << endl << "Luna " << i + 1 << ": ";
		input >> vanzari[i];
	}

	p.setVanzari(vanzari, nrLuni);

	delete[]  vanzari;
}


int main(int argc, char* argv[]) {
	Produs p1("Pepsi",TipProdus::PROMO);
	Produs p2(100,"Coca Cola");
	Produs p3(100,"Coca Cola");

	cout << p1;
	cout << p2;
	cin >> p1;
	cout << p1;

	p1 = p3;
	p2 = p2;
}