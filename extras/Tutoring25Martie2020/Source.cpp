#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

enum TipEmail {NORMAL, IMPORTANT=100, EVENIMENT};

class Email {

	const int idEmail;		//obligatoriu

	char subject[50];		//obligatoriu
	string from;			//obligatoriu
	string * to = NULL;
	int nrAdreseDestinatie = 0;
	char* continut = NULL;
	TipEmail tip;			//obligatoriu

	int zi;					//obligatoriu
	int luna;				// --
	int an;					// --

public:
	Email(int id, const char* subject, string from,
		TipEmail tip, int zi, int luna, int an):idEmail(id) {

		strcpy(this->subject, subject);
		this->from = from;
		this->tip = tip;

		this->zi = zi;
		this->luna = luna;
		this->an = an;

		this->to = NULL;
		this->continut = NULL;
		this->nrAdreseDestinatie = 0;
	}

	void oFunctie() {
		int an = this->an;
	}

	int getId() {
		return this->idEmail;
	}

	~Email() {
		if (this->continut != NULL)
			delete[] this->continut;
		delete[] this->to;
	}

	//TO DO constructor copiere

	friend void operator<<(ostream& consola, Email& email);
	friend void operator>>(istream& in, Email& email);

	//supraincarcare operatori in clasa

	Email operator+(const char* adresa) {

		//facem o copie pentru this prin constructor cu parametri
		Email rezultat(this->idEmail, this->subject,
			this->from, this->tip, this->zi,
			this->luna, this->an);
		
		//daca avem constructorul de copiere
		//Email copie = *this;

		string adresaNoua = string(adresa);
		string* destinatari = 
			new string[this->nrAdreseDestinatie + 1];
		for (int i = 0; i < this->nrAdreseDestinatie; i++)
			destinatari[i] = this->to[i];
		destinatari[this->nrAdreseDestinatie] = adresaNoua;

		strcpy(rezultat.subject, this->subject);
		rezultat.nrAdreseDestinatie = 
			this->nrAdreseDestinatie + 1;
		rezultat.to = destinatari;

		return rezultat;
	}

	//operator =
	void operator=(const Email& email) {
		//este constant
		//this->idEmail = email.idEmail;
		strcpy(this->subject, email.subject);
		this->from = email.from;
		this->zi = email.zi;
		this->luna = email.luna;
		this->an = email.an;

		delete[] this->continut;

		if (email.continut != NULL) {
			this->continut = new char[strlen(email.continut) + 1];
			strcpy(this->continut, email.continut);
		}
		else
			this->continut = NULL;

		delete[] this->to;

		if (email.nrAdreseDestinatie != 0) {
			this->to = new string[email.nrAdreseDestinatie];
			for (int i = 0; i < email.nrAdreseDestinatie; i++)
				this->to[i] = email.to[i];
			this->nrAdreseDestinatie = email.nrAdreseDestinatie;
		}
		else
		{
			this->nrAdreseDestinatie = 0;
			this->to = NULL;
		}

		this->tip = email.tip;
	}

	//constructor de copiere
	Email(const Email& email):idEmail(email.idEmail) {

		strcpy(this->subject, email.subject);
		this->from = email.from;
		this->zi = email.zi;
		this->luna = email.luna;
		this->an = email.an;

		if (email.continut != NULL) {
			this->continut = new char[strlen(email.continut) + 1];
			strcpy(this->continut, email.continut);
		}
		else
			this->continut = NULL;

		if (email.nrAdreseDestinatie != 0) {
			this->to = new string[email.nrAdreseDestinatie];
			for (int i = 0; i < email.nrAdreseDestinatie; i++)
				this->to[i] = email.to[i];
			this->nrAdreseDestinatie = email.nrAdreseDestinatie;
		}
		else
		{
			this->nrAdreseDestinatie = 0;
			this->to = NULL;
		}

		this->tip = email.tip;
	}


};

//supraincarcare operatori in zona globala
void operator<<(ostream& consola, Email& email) {
	consola << std::endl << " -------------- ";
	consola << endl << email.getId();
	consola << endl << "Subject: " << email.subject;
	consola << endl << "From: " << email.from;
	consola << endl << "Data: " << email.zi << "/" << 
		email.luna << "/" << email.an;
	consola << endl << "Tip: " << email.tip;

	if (email.continut == NULL)
		consola << endl << "Fara continut";
	else
		consola << endl << email.continut;

	if (email.nrAdreseDestinatie == 0) {
		consola << endl << "To: -";
	}
	else {
		consola << endl << "To: ";
		for (int i = 0; i < email.nrAdreseDestinatie; i++)
			consola << email.to[i] << ";";
	}
}

void operator>>(istream& in, Email& email) {
	cout << endl << "Date email";
	//este constant - NU se mai poate modifica
	//cout << endl << "Noul id: ";
	//in >> email.idEmail;

	cout << endl << "Subiect: ";
	in >> email.subject;

	cout << endl << "From: ";
	in >> email.from;

	cout << endl << "Continut: ";

	char buffer[10000];
	in >> buffer;

	if (email.continut != NULL)
		delete[] email.continut;

	email.continut = new char[strlen(buffer) + 1];
	strcpy(email.continut, buffer);

	cout << endl << "Numar destinatari: ";
	in >> email.nrAdreseDestinatie;

	if (email.to != NULL)
		delete[] email.to;
	email.to = new string[email.nrAdreseDestinatie];

	for (int i = 0; i < email.nrAdreseDestinatie; i++) {
		cout << endl << "To: ";
		in >> email.to[i];
	}

	cout << endl << 
		"Tip email (1-Important, 2 - Normal, 3 - Eveniment):";
	int tipCitit;
	in >> tipCitit;

	switch (tipCitit) {
	case 1:
		email.tip = TipEmail::IMPORTANT;
		break;
	case 2:
		email.tip = TipEmail::NORMAL;
		break;
	case 3:
		email.tip = TipEmail::EVENIMENT;
		break;
	default:
		email.tip = TipEmail::NORMAL;
	}

	cout << endl << "Zi: ";
	in >> email.zi;
	cout << endl << "Luna: ";
	in >> email.luna;
	cout << endl << "An: ";
	in >> email.an;
}

//supraincarcare string + Email
Email operator+(const char* adresa, Email email) {
	return email + adresa;
}

int main() {
	Email email(1, "Tutoring C++", "me@ie.ase.ro",
		TipEmail::IMPORTANT, 25, 3, 2020);

	Email* pEmail = new Email(2, "Tutoring C++", "me@ie.ase.ro",
		TipEmail::IMPORTANT, 25, 3, 2020);

	cout << email;
	cout << *pEmail;

	//cin >> email;
	//cout << email;

	//int vb1 = 10;
	//vb1 = vb1 + 10;

	email = email + "test@ase.ro";

	Email email2 = email;

	email2 = email2 + "zoom@ase.ro";

	cout << email2;

	email2 = "test2@ase.ro" + email2;


	//delete pEmail;
}
