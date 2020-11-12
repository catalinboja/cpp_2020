#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class DataCalendaristica {
	int zi;
	int luna;
	string denumireLuna;
	int an;
};

class Eveniment {
	string denumire = "";
	int ora = 0;			//doar ora, fara minute
	bool esteImportant = false;

	//DataCalendaristica data;
	char* data = nullptr;		//12/11/2020

	//char data[11];	//data + \0
	//int zi;
	//int luna;
	//string denumireLuna;
	//int an;

	//variabila ce contorizeaza cate evenimente importante avem
	const static int ORA_MAXIMA = 20;
	static int nrEvenimenteImportante;
public:
	void setData(const char* data) {
		if (data != nullptr) {
			//evitam memory leak-ul
			if (this->data != nullptr) {
				delete[] this->data;
			}
			this->data = new char[strlen(data) + 1];
			strcpy(this->data, data);
		}
		else
		{
			throw "Data primita nu este ok";
		}
	}

	Eveniment(string denumire, int ora, bool esteImportant, const char* data) {
		this->denumire = denumire;
		this->ora = ora;
		this->esteImportant = esteImportant;
		this->setData(data);

		if (this->esteImportant) {
			Eveniment::nrEvenimenteImportante += 1;
		}
	}

	~Eveniment() {
		if (this->data != nullptr) {
			delete[] this->data;
		}
		if (this->esteImportant) {
			Eveniment::nrEvenimenteImportante -= 1;
		}
	}

	string getDenumire() {
		return this->denumire;
	}

	//int getNrEvenimenteImportante() {
	//	return Eveniment::nrEvenimenteImportante;
	//	//return this->nrEvenimenteImportante;
	//	//return nrEvenimenteImportante;
	//}

	static int getNrEvenimenteImportante() {
		return Eveniment::nrEvenimenteImportante;
		//return nrEvenimenteImportante;
	}

	//constructor copiere
	Eveniment(const Eveniment& ev) {
		//ev.denumire = this->denumire;
		this->denumire = ev.denumire;
		this->esteImportant = ev.esteImportant;
		if (this->esteImportant) {
			Eveniment::nrEvenimenteImportante += 1;
		}
		this->setData(ev.data);
		this->ora = ev.ora;
	}

	Eveniment operator=(Eveniment& ev2) {
		this->denumire = ev2.denumire;
		this->esteImportant = ev2.esteImportant;

		//de verificat toate situatiile posibile
		if (this->esteImportant) {
			Eveniment::nrEvenimenteImportante += 1;
		}

		this->setData(ev2.data);
		this->ora = ev2.ora;
	}


	friend ostream& operator<<(ostream& consola, Eveniment& ev);
};

ostream& operator<<(ostream& consola, Eveniment& ev) {
	consola << endl << "------------------------";
	consola << endl << "Eveniment: " << ev.getDenumire();
	consola << endl << "Ora " << ev.ora;
	consola << endl << "Data " << ev.data;
	consola << endl << (ev.esteImportant ? "Important !" : "");
	return consola;
}


int Eveniment::nrEvenimenteImportante = 0;

void nimicImportant(Eveniment ev) {

}

Eveniment altceva() {
	Eveniment temp("Seminar POO", 11, true, "12/11/2020");
	return temp;
}

int main(int argc, char* argv[]) {

	Eveniment ev1("Seminar POO", 11, true, "12/11/2020");
	Eveniment ev2("Consultatii POO", 16, false, "12/11/2020");
	Eveniment* pEv = new Eveniment("Curs POO", 10, true, "13/11/2020");
	//!ev1;
	cout << ev1;
	cout << ev1 << (*pEv) << ev2;

	//cout << endl << "Nr evenimente importante este " << ev1.getNrEvenimenteImportante();
	//cout << endl << "Nr evenimente importante este " << pEv->getNrEvenimenteImportante();
	cout << endl << "Nr evenimente importante este " << 
		Eveniment::getNrEvenimenteImportante();

	//apel constructor de copiere
	Eveniment ev3 = ev1;

	ev3 = ev2;
	//ev3 = (ev2 + 5);

	int* pvb = nullptr;
	pvb = (int*)25;


	nimicImportant(ev1);
}
