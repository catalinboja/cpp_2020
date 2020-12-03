#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Grupa {
	int grupa = 0;
	string facultate = "";
	string adresaFacultate = "";
public:
	Grupa(int grupa, string facultate, string adresa) {
		this->grupa = grupa;
		this->facultate = facultate;
		this->adresaFacultate = adresa;
	}

	friend void operator<<(ostream& consola, Grupa& grupa);
};

class Nota {
	int valoare = 0;
	string numeCurs = "";
public:
	Nota(int valoare, string curs) {
		this->valoare = valoare;
		this->numeCurs = curs;
	}
	Nota() {

	}


	friend void operator<<(ostream& facultate, Nota& nota);
};

//Student are o relatie de tip "has-a" cu Nota si cu Grupa
class Student {
	string nume = "";
	int varsta = 0;
	Grupa grupa;

	Nota note[100];
	int nrNote = 0;
public:
	Student():grupa(1000,"CSIE","Calea Dorobanti"),varsta(0) {
		//this->varsta = 0;
	}

	Student(string nume, int varsta, Grupa grupaPrimita):grupa(grupaPrimita) {
		this->nume = nume;
		this->varsta = varsta;
		this->nrNote = 0;
	}

	//Student(string nume, int varsta, Grupa grupaPrimita)
	//	:grupa(grupaPrimita.grupa, grupaPrimita.facultate, grupaPrimita.adresa) {

	//}

	void adaugaNota(Nota nota) {
		if (this->nrNote < 100) {
			this->note[this->nrNote] = nota;	//operatorul = din Nota - acum forma implicita
			this->nrNote += 1;
		}
	}

	friend void operator<<(ostream& consola, Student& student);
	friend void operator<<(ofstream& fisier, Student& student);
};

void operator<<(ostream& consola, Grupa& grupa) {
	consola << endl << grupa.grupa << " | " << grupa.facultate 
		<< " - " << grupa.adresaFacultate;
}

void operator<<(ostream& consola, Nota& nota) {
	consola << endl << "Nota la disciplina " << nota.numeCurs << " este " << nota.valoare;
}

void operator<<(ostream& consola, Student& student) {
	consola << endl << "Nume " << student.nume;
	consola << endl << "Varsta " << student.varsta;
	consola << student.grupa;
	consola << endl << "Note: ";
	for (int i = 0; i < student.nrNote; i++) {
		consola << student.note[i];
	}
} 

void operator<<(ofstream& fisier, Student& student) {
	fisier << endl << "--------------------------------------";
	fisier << endl << "Nume " << student.nume;
	fisier << endl << "Varsta " << student.varsta;
	fisier << student.grupa;
	fisier << endl << "Note: ";
	for (int i = 0; i < student.nrNote; i++) {
		fisier << student.note[i];
	}
}

int main(int argc, char* argv[]) {
	Student student1;
	Grupa g1059(1059,"CSIE","Calea Dorobanti 15-17");
	Student student2("Gigel", 20, g1059);

	Nota nota1(9, "POO");
	Nota nota2(10, "Tehnologii Web");

	student2.adaugaNota(nota1);
	student2.adaugaNota(nota2);

	cout << student1;
	cout << student2;

	//FILE* pf;
	//pf = fopen("Test.txt", "r+");

	//scriere in fisiere text
	//ofstream raport("Raport Studenti.txt", ios::out);
	ofstream raport;
	raport.open("Raport Studenti.txt", ios::out | ios::trunc);
	if (raport.is_open()) {
		raport << "Lista studenti CSIE" << endl;
		raport << student1;
		raport << student2;

		raport.close();

	}
	else {
		cout << endl << "******************* Fisierul un a fost deschis";
	}

	//citire din fisier text
	ifstream fisier("Studenti.txt", ios::in);
	if (fisier.is_open()) {
		int nrStudenti;
		fisier >> nrStudenti;

		int contor = 0;

		//e nevoie pentru a muta cursorul pe linia urmatoare
		string temp;
		getline(fisier, temp);

		while (!fisier.eof()) {
			char buffer[100];
			string nume;

			//fisier.getline(buffer, 100);
			//nume = string(buffer);
			getline(fisier, nume);

			int varsta;
			fisier.getline(buffer, 100);
			varsta = atoi(buffer);

			int grupa;
			fisier.getline(buffer, 100);
			grupa = atoi(buffer);
			string facultate;
			string adresa;
			getline(fisier, facultate);
			getline(fisier, adresa);

			Grupa grupaStudent(grupa, facultate, adresa);
			Student student(nume, varsta, grupaStudent);

			int nrNote;
			fisier.getline(buffer, 100);
			nrNote = atoi(buffer);

			for (int i = 0; i < nrNote; i++) {
				int nota;
				fisier.getline(buffer, 100);
				nota = atoi(buffer);

				string curs;
				getline(fisier, curs);

				Nota notaStudent(nota, curs);
				student.adaugaNota(notaStudent);
			}

			cout << endl << "Student citit din fisier";
			cout << student;
			contor += 1;

		}

		fisier.close();
	}
	else {
		cout << endl << "******************* Fisierul un a fost deschis";
	}
}