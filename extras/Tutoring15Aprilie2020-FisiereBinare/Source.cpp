#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

enum tipParticular {rural = 10, diaspora, minoritati, nu};

class altString {
	char* adresaSiruluiDeCaractere;
	int nrCaractere;
	//alte atribute

public:
	char* c_str() {
		return this->adresaSiruluiDeCaractere;
	}

};

class Student {
	int id;
	char gen;
	float medieBAC;
	bool esteOlimpic;
	tipParticular tip;
	int credite[10];	//credite din activitati voluntare
	int nrCredite;
	int *note = NULL;
	int nrNote;
	string nume;
	char prenume[100];
	char* facultate = NULL;

public:
	Student(int Id, char Gen, float Medie, bool EsteOlimpic, tipParticular Tip,
		int* Credite, int NrCredite, int* Note, int NrNote, string Nume,
		const char* Prenume, const char* Facultate) {
		this->id = Id;
		this->gen = Gen;
		this->medieBAC = Medie;
		this->esteOlimpic = EsteOlimpic;
		this->tip = Tip;
		//this->credite = Credite;			NU copiem vectorii cu =
		for (int i = 0; i < NrCredite; i++)
			this->credite[i] = Credite[i];
		this->nrCredite = NrCredite;
		//pentru vectori dinamici NU uita sa aloci
		this->note = new int[NrNote];
		for (int i = 0; i < NrNote; i++)
			this->note[i] = Note[i];
		this->nrNote = NrNote;
		this->nume = Nume;
		strcpy(this->prenume, Prenume);
		this->facultate = new char[strlen(Facultate) + 1];
		strcpy(this->facultate, Facultate);
	}

	Student() {

	}

	//metoda care scrie datele obiectului intr-un fisier binar
	void scrieStudent(ofstream& fisierBinar) {
		//scriu id-ul
		fisierBinar.write((char*)&this->id, sizeof(int));
		//scriu genul
		fisierBinar.write(&this->gen, sizeof(char));
		//scriu media
		fisierBinar.write((char*)&this->medieBAC, sizeof(float));
		//este olimpic
		fisierBinar.write((char*)&this->esteOlimpic, sizeof(bool));
		//tipul
		fisierBinar.write((char*)&this->tip, sizeof(tipParticular));
		//scriu numarul de credite
		fisierBinar.write((char*)&this->nrCredite, sizeof(int));
		//scriu valorile creditelor
		//varianta in care scriu tot vectorul
		fisierBinar.write((char*)this->credite, sizeof(int) * this->nrCredite);
		//scriu numarul de note
		fisierBinar.write((char*)&this->nrNote, sizeof(int));
		//varianta in care scriu valorile cate una
		for (int i = 0; i < this->nrNote; i++) {
			fisierBinar.write((char*)&this->note[i], sizeof(int));
		}

		//zona de siruri de caractere
		//nume - string
		//scriu numarul de caractere al numelui  + \0
		int nrCaractereCuTerminator = this->nume.size() + 1;
		fisierBinar.write((char*)&nrCaractereCuTerminator, sizeof(int));
		//scriu numele cu \0
		fisierBinar.write(this->nume.c_str(), nrCaractereCuTerminator * sizeof(char));
		
		//prenume char[1000]
		//varianta 1 - scriu tot vectorul static
		fisierBinar.write(this->prenume, sizeof(this->prenume));

		////varianta 2 - procedam ca in cazul numelui
		//nrCaractereCuTerminator = strlen(this->prenume) + 1;
		//fisierBinar.write((char*)&nrCaractereCuTerminator, sizeof(int));
		////scriu prenume cu \0
		//fisierBinar.write(this->prenume, nrCaractereCuTerminator * sizeof(char));

		//facultatea
		//varianta 1 - aleg sa scriu facultatea sub forma unui buffer static de 100 caractere
		char buffer[100];
		strcpy(buffer, this->facultate);
		fisierBinar.write(buffer, sizeof(buffer));

		////varianta 2 - ca in cazul numelui
		//nrCaractereCuTerminator = strlen(this->facultate) + 1;
		//fisierBinar.write((char*)&nrCaractereCuTerminator, sizeof(int));
		//fisierBinar.write(this->facultate, nrCaractereCuTerminator * sizeof(char));
	}

	//citire date obiect din fisier binar
	void citireStudent(ifstream& fisierBinar) {
		//id-ul
		fisierBinar.read((char*)&this->id, sizeof(int));
		//citesc genul
		fisierBinar.read(&this->gen, sizeof(char));
		//citesc media
		fisierBinar.read((char*)&this->medieBAC, sizeof(float));
		//este olimpic
		fisierBinar.read((char*)&this->esteOlimpic, sizeof(bool));
		//tipul
		fisierBinar.read((char*)&this->tip, sizeof(tipParticular));
		//citesc numarul de credite
		fisierBinar.read((char*)&this->nrCredite, sizeof(int));
		//citesc creditele - toate odata
		fisierBinar.read((char*)this->credite, sizeof(int) * this->nrCredite);
		//citesc numarul de note
		fisierBinar.read((char*)&this->nrNote, sizeof(int));
		//NU UITA sa aloci vectorul - este dinamic
		//evitam memory leak
		if (this->note != NULL)
			delete[] this->note;
		this->note = new int[this->nrNote];

		for (int i = 0; i < this->nrNote; i++) {
			fisierBinar.read((char*)&this->note[i], sizeof(int));
		}

		//citesc numarul de caractere al numelui  + \0
		int nrCaractereCuTerminator;
		fisierBinar.read((char*)&nrCaractereCuTerminator, sizeof(int));
		//citesc numele care este in Student stocat intr-un string
		char bufferNume[100];
		fisierBinar.read(bufferNume, nrCaractereCuTerminator * sizeof(char));
		this->nume = string(bufferNume);

		//citesc tot vectorul static (pt ca asa am ales sa il scriem)
		fisierBinar.read(this->prenume, sizeof(this->prenume));

		//citesc facultatea - atentie este in oglinda cu scrierea
		char bufferFacultate[100];
		fisierBinar.read(bufferFacultate, sizeof(bufferFacultate));

		if (this->facultate != NULL)
			delete[] this->facultate;
		this->facultate = new char[strlen(bufferFacultate) + 1];
		strcpy(this->facultate, bufferFacultate);
	}

	friend ostream& operator<<(ostream& out, Student& s);
};

ostream& operator<<(ostream& out, Student& s) {

	out << endl << s.id << " | " << s.nume << " | " << s.prenume << " | " << s.facultate;
	out << endl << "Este olimpic : " << s.esteOlimpic;
	out << endl << "Este tip particular " << s.tip;
	out << endl << " Note: ";
	for (int i = 0; i < s.nrNote; i++)
		out << "  " << s.note[i];

	return out;
}


int main() {

	int crediteInitiale[] = { 4,4,6,2 };
	int nrCredite = 4;
	int noteInitiale[] = { 9,9,10 };
	int nrNote = 3;

	Student s1(1, 'M', 9.75, false, tipParticular::nu, crediteInitiale, nrCredite,
		noteInitiale, nrNote, "Gigel", "Ionescu", "CSIE");
	Student s2(1, 'F', 9.85, true, tipParticular::nu, crediteInitiale, nrCredite,
		noteInitiale, nrNote, "Ana", "Alexandrescu", "CSIE");
	Student s3(1, 'F', 9.75, false, tipParticular::diaspora, crediteInitiale, nrCredite,
		noteInitiale, nrNote, "Ioana", "Ionescu", "MK");

	//afisare la consola
	cout << s1 << s2 << s3;

	//afisare fisier text
	ofstream raport("studenti.txt", ios::app);
	if (raport.is_open()) {
		raport << s1;
		raport << s2;
		raport << s3;
		//raport << s1 << s2 << s3;
		raport.close();
	}
	else
	{
		cout << endl << "EROARE Fisierul nu a fost creat";
	}

	//fisiere binare
	//scriere
	ofstream fisierDate("studenti.dat", ios::binary | ios::trunc);
	if (fisierDate.is_open()) {
		int numar = 23;
		//fisierDate << numar;	//Atentie! nu folosim  << pentru fisiere binare pentru ca 
								//	face conversie la text pentru toate valorile
		
		//NU merge pentru obiecte ce contin minim un camp dinamic
		//fisierDate.write((char*)&s1, sizeof(Student));

		s1.scrieStudent(fisierDate);
		s2.scrieStudent(fisierDate);
		s3.scrieStudent(fisierDate);
		
		fisierDate.close();
	}

	//citire
	ifstream fisierStudenti("studenti.dat", ios::binary);
	if (fisierStudenti.is_open()) {
		Student s4;
		//NU merge - vezi motivul anterior
		//fisierStudenti.read((char*)&s4, sizeof(Student));

		s4.citireStudent(fisierStudenti);

		cout << endl << " Date din fisier binar ";
		cout << s4;

		fisierStudenti.close();
	}
	else
		cout << endl << "********************* NU am deschis fisierul !";
}
