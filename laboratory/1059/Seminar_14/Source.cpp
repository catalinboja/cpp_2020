#include <iostream>
#include <string>
using namespace std;

class AutoAbstract {
protected:
	string model = "nimic";
	int vitezaMaxim;
	//__vfptr[]
public:
	string getModel() {
		return this->model;
	}
	virtual void afisareConsola() = 0;
};



class Tesla: public AutoAbstract {
	int capacitateAcumulator;
public:
	void afisareModel() {
		cout << endl << this->getModel();
	}

	string getModel() {
		return " Este o TESLA";
	}

	virtual void afisareConsola() {
		cout << endl << " Este o TESLA";
	}

	void superEcranTesla() {

	}
};


class Hibrid: public AutoAbstract {

	virtual void afisareConsola() {
		cout << endl << " Este un model hibrid";
	}
};

//int suma(int a, int b) {
//	return a + b;
//}
//
//float suma(float a, float b) {
//	return a + b;
//}
//
//string suma(string a, string b) {
//	return a + b;
//}

template<typename tip> tip suma(tip a, tip b) {
	return a + b;
}

template<typename T, typename X> class Cutie {
	float greutate;
	T continut;
	X culoare;
public:
	T getContinut() {
		return this->continut;
	}
	Cutie(float g, T c, X Culoare) {
		this->greutate = g;
		this->continut = c;
		this->culoare = Culoare;
	}
};


int main() {

	Cutie<string,int> c1(10,"Hello",3);

	Tesla t;
	Hibrid h;

	//AutoAbstract automobil;
	AutoAbstract* pAuto;

	AutoAbstract* flotaAuto[5];
	flotaAuto[0] = new Tesla();			//up-cast
	flotaAuto[1] = new Hibrid();
	flotaAuto[2] = new Tesla();
	flotaAuto[3] = new Hibrid();
	flotaAuto[4] = new Tesla();
	for (int i = 0; i < 5; i++) {
		//cout << endl << flotaAuto[i]->getModel();
		flotaAuto[i]->afisareConsola();
		//flotaAuto[i]->_vfptr[0]();

		Tesla* pTesla = dynamic_cast<Tesla*>(flotaAuto[i]);			//down-cast
		if (pTesla != nullptr) {
			pTesla->superEcranTesla();

			Tesla t = *pTesla;
			t.superEcranTesla();

		}
	}

	cout << endl << "-----------------";
	int rezultat = suma<int>(2, 3);
	float rez = suma<float>(2.3, 4.1);
	string mesaj = suma<string>("salut ", "C++");
	cout << endl << mesaj;
}