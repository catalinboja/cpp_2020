#include <string>
#include <iostream>
using namespace std;

class Test {
public:

	char nume[50] = "";
	char* altNume;

	int alteValori[5];
	int nrValoriFolosite = 0;

	const int valoare;
	const int valoare2;
	int* valori;
	int nrValori;
	string descriere;
	const static int variabilaStatica;
public:
	Test() :valoare(0), valoare2(1) {
		this->valori = new int[10];
		this->nrValori = 10;
	}


	Test(int Valoare, string descriere)
		:valoare(Valoare), valoare2(0) {

	}

	Test(Test& existent) :valoare(existent.valoare), valoare2(0) {
		this->descriere = existent.descriere;
	}

	void oFunctie() {
		this->descriere = "altceva";
		cout << endl << "Descrierea este " << this->descriere;
	}

	void operator=(Test t) {
		//this->valoare = t.valoare;

		//NU ASA
		//this->valori = t.valori;

		delete[] this->valori;

		this->valori = new int[t.nrValori];
		for (int i = 0; i < t.nrValori; i++)
			this->valori[i] = t.valori[i];

	}
};

const int Test::variabilaStatica = 0;

istream& operator>>(istream& in, Test& t) {

	cout << endl << "Noua descriere: ";
	in >> t.descriere;
	cout << endl << "Numar de valori: ";
	in >> t.nrValori;


	delete[] t.valori;
	t.valori = new int[t.nrValori];
	for (int i = 0; i < t.nrValori; i++) {
		cout << endl << "Valoare :";
		in >> t.valori[i];
	}

	//t.altNume = new char[1000];
	char buffer[1000];
	in >> buffer;
	t.altNume = new char[strlen(buffer) + 1];
	strcpy(t.altNume, buffer);

	return in;
}

void main() {


	int vb = 100;
	int* pointer;
	pointer = &vb;
	pointer = new int[50];
	//*pointer = new int[20];

	Test t1;
	Test t2 = t1;
	Test t3;
	//Test t3 = t2;
	t3 = t2;	//void operator=(Test&,Test)
	//t1 = t3 = t2;		//Test operator=(Test&,Test)

	//t3 = t2 + 1;

	//cout << t2 << t1;

	Test* pointerT;
	pointerT = new Test(1,"test");
	delete pointerT;
	pointerT = new Test(1, "test");
	cout << endl << pointerT->descriere;

	Test t4(2, "test");
	cout << endl << t4.descriere;


	t4.oFunctie();
	t3.oFunctie();

	cin >> t4 >> t3;		//operator>>(istream&, Test&)

}