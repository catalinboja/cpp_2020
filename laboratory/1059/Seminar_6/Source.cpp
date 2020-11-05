#include <iostream>
#include <string>

using namespace std;

class Produs {
	unsigned int id = 0;
	std::string nume = "";
	char* descriere = nullptr;
public:
	Produs() {
		cout << endl << "Apel constructor implicit";
		this->descriere = nullptr;
	}

	Produs(int id) {
		this->id = id;
		this->nume = "Nimic";
		//this->descriere = "Ceva";
		this->setDescriere("Fara descriere");
	}

	Produs(int id, string nume) {
		this->id = id;
		this->nume = nume;
	}

	Produs(int id, string nume, const char* descriere) {
		this->id = id;
		this->nume = nume;
		this->setDescriere(descriere);
	}

	void setDescriere(const char* nouaDescriere) {
		if (this->descriere != nullptr) {
			delete[] this->descriere;
		}
		this->descriere = new char[strlen(nouaDescriere) + 1];
		strcpy_s(this->descriere, strlen(nouaDescriere) + 1, nouaDescriere);
	}

	int getId() {
		return this->id;
	}

	string getNume() {
		return this->nume;
	}

	friend ostream& operator<<(ostream& consola, Produs p);
};

ostream& operator<<(ostream& consola, Produs p) {
	consola << endl << "-----------------";
	consola << endl << "Id: " << p.getId();
	consola << endl << "Nume: " << p.getNume();
	if(p.descriere != nullptr)
		consola << "Descriere: " << p.descriere;

	return consola;
}


int main() {
	//apel constructor implicit
	Produs p1;
	Produs p2;
	Produs* pp1 = new Produs();

	//cu parametri
	Produs p3(1, "Pepsi");
	Produs p4(2, "Mirinda", "Cu aroma de mandarine");

	Produs* pp5 = new Produs(5, "Coca Cola");

	cout << p3 << p4 << *pp5;


	//vector de Produse
	Produs produse[10];
	Produs* produseNoi = new Produs[10];

	cout << p1 << p2;;
	cout << p2;

	//sterg produs din Heap
	delete pp1;
	delete[] produseNoi;

}
