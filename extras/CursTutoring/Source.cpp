#include <iostream>
#include <string>
using namespace std;

class ClasaAbstracta {
	int valoare;
public:
	int functie() {
		return 10;
	}
	virtual int functieObligatorie(float vb) = 0;
};

class A: public ClasaAbstracta {
	char valoare;

public:
	A(int vb) {

	}

	void printMesaj() {
		cout << endl << "Hello din A";
	}
	virtual void printMesajVirtual() {
		cout << endl << "Hello virtual din A";
	}

	int functieObligatorie(float vb) {
		return 0;
	}
};

class B : public A{
	int valori[1000];

public:

	B(): A(50){
		for (int i = 0; i < 1000; i++)
			this->valori[i] = 0;
	}

	//supradefinire
	void printMesaj() {
		cout << endl << "Hello din B";
		//afisare vector de 1000 de int
	}

	//supraincarcare - mai avem deja o versiune
	void printMesaj(int vb) {
		cout << endl << "Hello din B";
		//afisare vector de 1000 de int
	}
	void printMesajVirtual() {
		this->A::printMesajVirtual();
		//this->printMesajVirtual();	//recursivitate infinita
		cout << endl << "Hello virtual din B";
		//afisare vector de 1000 de int
	}

	float medie() {
		float s = 0;
		for (int i = 0; i < 1000; i++)
			s += valori[i];
		return s / 1000;
	}

	//operator !
	bool operator!() {
		if (this->medie() == 0)
			return true;
		else
			return false;
	}

	explicit operator float() {
		return this->medie();
	}

	int functie1(int vb) {
		return vb / 10;
	}

	int functie1(int vb1, int vb2) {
		return vb1 + vb2;
	}

	string functie1(string msj, int vb) {
		return msj + std::to_string(vb);
	}
};

//supraincarcare/overloading
int functie1(int vb) {
	return vb / 10;
}

int functie1(int vb1, int vb2) {
	return vb1 + vb2;
}

string functie1(string msj, int vb) {
	return msj + std::to_string(vb);
}

class Student {
	int varsta = 0;
	char nume[50];
	char* facultate = NULL;
public:

	Student() {

	}
	Student(int Varsta, const char *Nume, 
		const char* Facultate) {
		varsta = Varsta;
		strcpy(nume, Nume);
		facultate = new char[strlen(Facultate)+1];
		strcpy(facultate, Facultate);
	}
};


int main() {

	//ClasaAbstracta ca;
	ClasaAbstracta *pCA;

	A a(1);
	B b;
	A* pA = new A(1);
	B* pB = new B();

	a.printMesaj();	//early-binding compilatorul verifica tipul lui a
	b.printMesaj(); //early-binding compilatorul verifica tipul lui b

	pA->printMesaj();	//early-binding compilatorul verifica tipul lui pA
	pB->printMesaj(); //early-binding compilatorul verifica tipul lui pB

	//upcasting
	a = b;
	pA = &b;

	cout << endl << "-----------------";
	a.printMesaj();	//early-binding compilatorul verifica tipul lui a
	a.printMesajVirtual();	//early-binding compilatorul verifica tipul lui a

	pA->printMesaj();	//early-binding compilatorul verifica tipul lui pA 
						//si faptul ca functia ca nu este virtuala
	pA->printMesajVirtual();	//late-binding pentru ca functia este virtuala
								//si pentru ca la adresa pointerului de tip *A
								//este continut de B
	pB->printMesajVirtual();


	pCA = &a;
	pCA->functieObligatorie(10);
	pCA = &b;
	pCA->functieObligatorie(10);

	string mesaj;
	cout << endl << "Mesajul este :";
	cin >> mesaj;
	cout << endl << "****** " << mesaj;

	if (!b)
		cout << endl << "Media valorilor este 0";
	else
		cout << endl << " Media este" << (float)b;


	//Student studenti[10];
	//int nrStudenti;

	Student *lista = new Student[10];
	

	Student s1(21, "Gigel", "CSIE");
	lista[0] = s1;

	Student * *grupa = new Student*[10];
	grupa[0] = new Student(21, "Ana", "CSIE");
	grupa[1] = new Student(21, "Ana", "CSIE");

	//dezalocare - cand stiu SIGUR ca toate adresele sunt in HEAP
	for (int i = 0; i < 2; i++)
		delete grupa[i];
	delete[] grupa;

}