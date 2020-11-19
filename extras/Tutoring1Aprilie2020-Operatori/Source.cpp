#include <iostream>
#include <string>
using namespace std;

class Mesaj {
	int prioritate = 0;
	string text = "";
public:
	Mesaj(int prioritare, string text) {
		this->prioritate = prioritare;
		this->text = text;
	}

	Mesaj() {
		this->prioritate = 0;
		this->text = "";
	}

	string getText() {
		return this->text;
	}

	int getPrioritate() {
		return this->prioritate;
	}

	//operatorul = este obligatoriu supraincarcat prin functie membra
	//pentru return void operatorul nu se poate apela in cascada
	Mesaj operator=(Mesaj mesaj) {
		this->prioritate = mesaj.prioritate;
		this->text = mesaj.text;
		//return mesaj;
		return *this;
	}

	//operatorul + (Mesaj + string)
	Mesaj operator+(string msg) {
		//NU modificati this
		//this->text += msg;
		//return *this;

		Mesaj rezultat = *this;
		rezultat.text += msg;
		return rezultat;
	}

	//operator + (Mesaj  + Mesaj)
	Mesaj operator+(Mesaj m2) {
		//nu modificam this
		Mesaj rezultat = *this;
		rezultat.text += m2.text;
		return rezultat;
	}

	//operator = (Mesaj = string)
	void operator=(string textMesaj) {
		this->text = textMesaj;
	}

	//operator+= (Mesaj += string)
	void operator+=(string unText) {
		//aici este ok sa modificam this
		this->text += unText;
	}

	//operator *= (Mesaj *= int)
	void operator*=(int repetitii) {
		//aleg sa fac acelasi lucru ca si pentru *
		//folosesc operatorul * definit anterior 
		*this = repetitii * (*this);
	}

	//operator++ (Mesaj++)
	Mesaj operator++(int) {
		//post - incrementare
		//Atentie - trebuie facuta o copie inainte de a-l modifica pe this
		Mesaj copie = *this;
		this->prioritate += 1;
		return copie;
	}

	//operator++ (++Mesaj)
	Mesaj operator++() {
		//pre-incrementare
		this->prioritate += 1;
		return *this;
	}

	//operator ! 
	//sterge continutul textului'
	//void operator!() {
	//	this->text = "";
	//}

	//varianta 2
	//verificam lungimea textului vs 5 caractere
	bool operator!() {
		if (this->text.size() > 5)
			return true;
		else
			return false;
	}

	//operator functie (Mesaj, string, int)
	Mesaj operator()(string msj, int repetitii) {
		//atentie sa nu modificati this
		Mesaj rezultat = *this;
		for (int i = 0; i < repetitii; i++)
			rezultat.text += msj;
		return rezultat;
	}

	//operator functie (Mesaj, int , int)
	Mesaj operator()(int index1, int index2) {
		//atentie sa nu modificati this
		Mesaj rezultat = *this;
		//TO DO de extras subsirul 
		//
		return rezultat;
	}

	//operator [] - permite DOAR citirea valorilor
	//char operator[](int index) {
	//	if (index >= 0 && index < this->text.size())
	//		return this->text[index];
	//	else
	//		throw new exception("indexul este gresit");
	//}

	//operator [] - permite citirea si modificarea valorilor
	char& operator[](int index) {
		if (index >= 0 && index < this->text.size())
			return this->text[index];
		else
			throw new exception("indexul este gresit");
	}

	//operator cast la int
	//returneaza prioritatea mesajului
	//forma implicita - nu scriem explicit (DAR sa evitati)
	explicit operator int() {
		return this->prioritate;
	}

	//zona friend
	friend Mesaj operator+(string msg, Mesaj mesaj);
	friend Mesaj operator*(int nr, Mesaj mesaj);
};

//se apeleaza si Constr Copiere din Mesaj deoarece m este transmis prin valoare
//pentru return void operatorul nu se poate apela in cascada
ostream& operator<<(ostream& consola, Mesaj m) {
	consola << endl << m.getPrioritate() << " - " << m.getText();
	return consola;
}

//operator + (string + Mesaj)
Mesaj operator+(string msg, Mesaj mesaj) {
	Mesaj rezultat = mesaj;
	rezultat.text = msg + rezultat.text;
	return rezultat;
}

//operator *(int * Mesaj)
Mesaj operator*(int nr, Mesaj mesaj) {
	Mesaj rezultat = mesaj;
	string textInitial = rezultat.getText();
	rezultat.text = "";
	for (int i = 0; i < nr; i++) {
		rezultat.text += textInitial;
	}
	return rezultat;
}

int main() {
	Mesaj mesaj1(1, "Salut !");

	cout << mesaj1;

	//Constructor de copiere
	Mesaj mesaj2 = mesaj1;

	Mesaj mesaj3(10, "Prezentare operatori");

	cout << mesaj3 << mesaj2;
	//cout << mesaj2;

	//operator =
	mesaj3 = mesaj1 = mesaj2;

	//alternativa
	mesaj3 = mesaj2;
	mesaj1 = mesaj2;

	cout << mesaj3;

	//operatori binari
	// +, -, *, /
	//rezultat = sursa1 + sursa2
	//NU MODIFICA valoarea operanzilor (sursa1 sau sursa2)

	cout << endl << " ---------------------- Operatori binari";
	cout << mesaj1;	//Salut !

	mesaj2 = mesaj1 + " completare";

	cout << mesaj1;//Salut !
	cout << mesaj2;//Salut ! completare

	Mesaj mesaj4;//""
	mesaj3 = " Am uitat sa adaug " + mesaj2;
	mesaj4 = mesaj2 + mesaj3;

	cout << mesaj3;//Am uitat sa adaug Salut ! completare
	cout << mesaj4;//Salut ! completare Am uitat sa adaug Salut ! completare

	//operator = 
	mesaj2 = "Salut ";

	cout << endl << mesaj2; //Salut
	mesaj1 = 3 * mesaj2;
	cout << mesaj1; //Salut Salut Salut

	//operatori binari
	//+=, -=, *=, /+
	//sursa += ceva <-> sursa = sursa + ceva

	cout << endl << " ---------------------- Operatori binari *=, +=, etc";
	mesaj1 = "Test";
	mesaj2 = "Hello ";

	mesaj1 += " operatori";
	mesaj2 *= 4;

	cout << mesaj1;//Test operatori
	cout << mesaj2;//Hello Hello Hello Hello

	//operatori binari
	//++ sau -- in cele 2 forme post si pre
	int vb1 = 10;
	int vb2 = vb1++; //returneaza valoarea initiala
	int vb3 = ++vb1; //returneaza valoarea modificata

	cout << endl << " ---------------------- Operatori unari ++ si --";
	
	cout << endl << vb1 << " " << vb2 << " " << vb3; // 12 10 12

	Mesaj mesaj5(20, "Mesaj important");
	mesaj1 = mesaj5++;
	cout << mesaj1;//20 - Mesaj important
	cout << mesaj5;//21 - Mesaj important
	mesaj2 = ++mesaj5;
	cout << mesaj2;//22 - Mesaj important
	cout << mesaj5;//22 - Mesaj important

	//operatori speciali
	//functie
	//!
	//[] - indexare

	cout << endl << " ---------------------- Operatori speciali";
	mesaj1 = "Un text de lungime mare";
	
	//!mesaj1;
	//cout << mesaj1;

	if (!mesaj1)
		cout << endl << "Textul are mai mult de 5 caractere";
	else
		cout << endl << "Textul are cel mult 5 caractere";

	//operator functie
	mesaj2 = mesaj1(2,6);	//extragem subsirul intre caracterul 2 si 6
	cout << mesaj2;
	//mesaj1(2, 6, 8);
	mesaj2 = mesaj1("test", 2); //multiplica textul primit si il adauga
	cout << mesaj2;

	//operator [] 
	//da acces citire sau scriere/citire la o colectie interna privata
	mesaj1 = "test";
	cout << endl << "Primul caracter din mesaj este " << mesaj1[0];
	mesaj1[0] = 'T';
	cout << mesaj1;

	//operator cast
	Mesaj mesaj6(20, "Mesaj important");
	int prioritate = (int)mesaj6;

	//operatori conditionali
	// ==, <, >, <=, >=, !=
	//TO DO
}
