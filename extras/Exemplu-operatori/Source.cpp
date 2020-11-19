#include <iostream>
#include <string>

using namespace std;

class Student {
private:
	string nume = "Anonim";
	int varsta = 0;

private:

	int* note = NULL;
	int nrNote = 0;
public:
	const int id;
	static int nrStudenti;

public:
	//constructorul default
	//Student() {
	//	cout << endl << "Apel constructor default";
	//}

	Student(string nume) :id(0), varsta(23) {
		this->nume = nume;
		Student::nrStudenti += 1;
	}

	Student(string nume, int varsta) : id(Student::nrStudenti) {
		this->nume = nume;
		this->varsta = varsta;
		Student::nrStudenti += 1;
	}

	Student(int varsta, string nume) : id(Student::nrStudenti) {
		this->nume = nume;
		this->varsta = varsta;
		Student::nrStudenti += 1;
	}

	Student(string nume, int varsta, int nrNote) : id(Student::nrStudenti) {
		this->nume = nume;
		this->varsta = varsta;

		this->nrNote = nrNote;
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->note[i] = 0;


		Student::nrStudenti += 1;
	}

	//destructor
	~Student() {
		//cout << endl << "Apel destructor";
		if (this->note != NULL)
			delete[] this->note;
	}

	//copy constructor
	Student(const Student& existent) :id(existent.id) {
		//existent.varsta = 45;
		//cout << endl << "Apel constructor copiere";
		this->nume = existent.nume;
		this->varsta = existent.varsta;
		this->nrNote = existent.nrNote;
		//shallow copy
		//this->note = existent.note;
		this->note = new int[existent.nrNote];
		for (int i = 0; i < existent.nrNote; i++)
			this->note[i] = existent.note[i];
	}

	int getVarsta() {
		return this->varsta;
	}

	int getNrNote() {
		return this->nrNote;
	}

	int getNota(int index) {
		if (index >= 0 && index < this->nrNote)
			return this->note[index];
		else
			throw new exception();
	}

	static int getNrStudenti() {
		return Student::nrStudenti;
	}

	string getNume() {
		return this->nume;
	}

	//Student operator+(int nota) {
	//	//adaugam o nota noua la lista existenta
	//	//NU ASA
	//	//this->note[this->nrNote] = nota;

	//	int* listaNoua = new int[this->nrNote + 1];
	//	for (int i = 0; i < this->nrNote; i++)
	//		listaNoua[i] = this->note[i];
	//	listaNoua[this->nrNote] = nota;

	//	if (this->note != NULL)
	//		delete[] this->note;

	//	this->note = listaNoua;
	//	this->nrNote += 1;

	//}

	void operator=(const Student& s) {
		//existent.varsta = 45;
		this->nume = s.nume;
		this->varsta = s.varsta;
		this->nrNote = s.nrNote;
		//shallow copy
		//this->note = existent.note;

		if (this->note != NULL)
			delete[] this->note;

		this->note = new int[s.nrNote];
		for (int i = 0; i < s.nrNote; i++)
			this->note[i] = s.note[i];
	}

	void operator-=(int nrNoteDeSters) {
		if (nrNoteDeSters <= this->nrNote) {
			int* listaNoua = new int[this->nrNote - nrNoteDeSters];
			for (int i = 0; i < this->nrNote - nrNoteDeSters; i++)
				listaNoua[i] = this->note[i];
			if (this->note != NULL)
				delete[] this->note;
			this->note = listaNoua;
			this->nrNote -= nrNoteDeSters;
		}
		else
			throw new exception();
	}

	float getMedie() {
		float medie = 0;
		for (int i = 0; i < this->nrNote; i++)
			medie += this->note[i];
		return (float)medie / this->nrNote;
	}

	bool operator==(Student stud) {
		//const char* test1 = "Gigel";
		//const char* test2 = "gigel";
		//if (strcmp(test1, test2) == 0)
		//	cout << endl << " gigel == Gigel";
		//else
		//	cout << endl << "Sunt diferite";
		if (this->nume.compare(stud.nume) == 0)
			return true;
		else
			return false;

	}

	//operatorul la float
	explicit operator float() {
		return this->getMedie();
	}

	explicit operator int() {
		return this->varsta;
	}

	int operator()(int min, int max) {
		int contor = 0;
		for (int i = 0; i < this->nrNote; i++)
			if (this->note[i] >= min && this->note[i] <= max)
				contor += 1;
		return contor;
	}

	int& operator[](int index) {
		if (index >= 0 && index <= this->nrNote)
			return this->note[index];
		else
			throw new exception();
	}

	//preincrementare
	Student operator++() {
		this->varsta += 1;
		return *this;
	}

	//postincrementare
	Student operator++(int) {
		Student copie = *this;
		this->varsta += 1;
		return copie;
	}

	friend Student operator+(Student& stud, int nota);
	friend void operator>>(istream& in, Student& stud);
};

int Student::nrStudenti = 0;

Student operator+(Student& stud, int nota) {

	Student rezultat = stud;

	//adaugam o nota noua la lista existenta
	//NU ASA
	//this->note[this->nrNote] = nota;

	int* listaNoua = new int[rezultat.getNrNote() + 1];
	for (int i = 0; i < rezultat.getNrNote(); i++)
		listaNoua[i] = rezultat.note[i];
	listaNoua[rezultat.nrNote] = nota;

	if (rezultat.note != NULL)
		delete[] rezultat.note;

	rezultat.note = listaNoua;
	rezultat.nrNote += 1;

	return rezultat;

}

Student operator+(int nota, Student& stud) {
	return stud + nota;
}

//void printInfo(Student stud) {
//	cout << endl << "Numele studentului este " << stud.nume;
//	cout << endl << "Varsta studentului este " << stud.varsta;
//}

//void printInfo2(Student* stud) {
//	cout << endl << "Numele studentului este " << stud->nume;
//	cout << endl << "Varsta studentului este " << stud->varsta;
//}

Student ceva() {
	Student s("Anonim", 21);
	return s;
}

ostream& operator<<(ostream& out, Student stud) {
	out << endl << "----------------------------";
	out << endl << "Numele este :" << stud.getNume();
	out << endl << "Varsta este: " << stud.getVarsta();
	out << endl << "Id-ul este: " << stud.id;
	out << endl << " Notele sunt:";
	for (int i = 0; i < stud.getNrNote(); i++)
		out << " " << stud.getNota(i);
	return out;
}

void operator>>(istream& in, Student& stud) {
	cout << endl << "Nume nou student:";
	in >> stud.nume;
	cout << "Noua varsta este: ";
	in >> stud.varsta;
	if (stud.note != NULL)
		delete[] stud.note;

	cout << endl << "Noul numar de note: ";
	in >> stud.nrNote;

	stud.note = new int[stud.nrNote];
	for (int i = 0; i < stud.nrNote; i++)
	{
		cout << "nota " << i + 1 << ": ";
		in >> stud.note[i];
	}
}

bool operator>(Student stud1, Student stud2) {
	if(stud1.getMedie() > stud2.getMedie())
		return true;
	else
		return false;
}

bool operator!(Student stud) {
	bool esteRestantier = false;
	for(int i=0;i<stud.getNrNote();i++)
		if (stud.getNota(i) < 5) {
			esteRestantier = true;
			break;
		}
	return esteRestantier;
}

void main() {
	//Student s;
	Student s1("Gigel", 22);
	Student s3("Vader", 22, 5);

	//apel constructor de copiere
	Student s4 = s3;
	Student s5(s3);

	s4 = s3;	//operator= (Student&, Student)

	s4 = s4 + 10;	//operator+	  s4.operator+(10)
					//	Student operator+(Student, int)
	s4 = 10 + s4;

	cout << s4 << s3;	//void operator<<(ostream,Student)
	cin >> s3;

	cout << s3;

	s3 -= 2;		//anulam ultimele 2 examene

	cout << s3 << s4;

	if (s4 > s3)
		cout << endl << s4.getNume() << " are media mai mare decat " << s3.getNume();
	if (s3 > s4)
		cout << endl << s3.getNume() << " are media mai mare decat " << s4.getNume();

	if (s4 == s3)
		cout << endl << "Au acelasi nume";

	if (!s4)
		cout << endl << s4.getNume() << " are restante !";
	if (!s3)
		cout << endl << s3.getNume() << " are restante !";

	char* pointerChar = (char*)&s3;

	float medieS3 = (float)s3;

	int nrNoteInIntervalData = s3(6,8);

	s3[2] = 10;

	Student temp1 = s3++;
	Student temp2 = ++s3;

	 
}