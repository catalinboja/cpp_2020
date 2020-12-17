#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Email {
	string subiect = "";
	string from = "";
	char continut[100] = "";
	bool solicitaConfirmareCitire = false;
public:
	Email() {

	}

	Email(string subiect, string from, const char* continut, bool solicitaConfirmare)
		:subiect(subiect), from(from), solicitaConfirmareCitire(solicitaConfirmare) {
		//this->from = from;
		strcpy_s(this->continut,100,continut);
	}

	void scrieInFisier(ofstream& fisier) {
		//scriu dimensiunea sirului de caractere - ne ajuta la citire
		int dim = this->subiect.size()+ 1;
		fisier.write((char*)&dim, sizeof(int));
		//descarcam sirul de caractere cu \0 - > +1
		fisier.write(this->subiect.c_str(), dim * sizeof(char));

		//scriu dimensiunea sirului de caractere - ne ajuta la citire
		dim = this->from.size() + 1;
		fisier.write((char*)&dim, sizeof(int));
		//descarcam sirul de caractere cu \0 - > +1
		fisier.write(this->from.c_str(), dim * sizeof(char));

		//sirul static de caractere este scris cu totul
		fisier.write(this->continut, sizeof(this->continut) * sizeof(char));

		//confirmarea
		fisier.write((char*)&this->solicitaConfirmareCitire, sizeof(bool));
	}

	void citesteDinFisier(ifstream& fisier) {
		int dim;
		char buffer[1000];

		//citim dimensiune subiect
		fisier.read((char*)&dim, sizeof(int));
		//citim subiectul
		fisier.read(buffer, dim * sizeof(char));
		this->subiect = string(buffer);

		//citim dimensiune from
		fisier.read((char*)&dim, sizeof(int));
		//citim from
		fisier.read(buffer, dim * sizeof(char));
		this->from = string(buffer);

		//citesc continut
		fisier.read(this->continut, sizeof(this->continut));

		//citesc confirmarea
		fisier.read((char*)&this->solicitaConfirmareCitire, sizeof(bool));

	}

	friend void operator<<(ostream& console, Email& email);
};

class Inbox {
	string email = "";
	Email* emailuri = nullptr;
	int noEmailuri = 0;
public:
	Inbox(string email) {
		this->email = email;
	}
	Inbox(const Inbox& inbox): email(inbox.email) {
		this->emailuri = new Email[inbox.noEmailuri];
		for (int i = 0; i < inbox.noEmailuri; i++) {
			this->emailuri[i] = inbox.emailuri[i];
		}
		this->noEmailuri = inbox.noEmailuri;
	}

	~Inbox() {
		if (this->emailuri) {
			delete[] this->emailuri;
		}
	}

	void operator=(Inbox& inbox) {
		if (this != &inbox) {
			if (this->emailuri) {
				delete[] this->emailuri;
			}
			this->emailuri = new Email[inbox.noEmailuri];
			for (int i = 0; i < inbox.noEmailuri; i++) {
				this->emailuri[i] = inbox.emailuri[i];
			}
			this->noEmailuri = inbox.noEmailuri;
		}
	}

	//operator functie
	void operator()(Email email) {
		Email* vectorNou = new Email[this->noEmailuri + 1];
		for (int i = 0; i < this->noEmailuri; i++) {
			vectorNou[i] = this->emailuri[i];
		}
		vectorNou[this->noEmailuri] = email;
		this->noEmailuri += 1;
		if (this->emailuri) {
			delete[] this->emailuri;
		}
		this->emailuri = vectorNou;
	}

	void backupInbox(string numeFisier) {
		ofstream fisier(numeFisier, ios::out | ios::binary | ios::trunc);
		if (fisier.is_open()) {
			//pentru fisiere binare NU FOLOSIM << sau >>

			//scriu email-ul contului
			//Recomandare: evitati sa scrieti obiectul -> scrieti doar valoarea din obiect care va intereseaza
			
			//scriu dimensiunea sirului de caractere - ne ajuta la citire
			int dim = this->email.size() + 1;
			fisier.write((char*)&dim, sizeof(int));
			//descarcam sirul de caractere cu \0 - > +1
			fisier.write(this->email.c_str(), (this->email.size() + 1) * sizeof(char));

			//numarul de email-uri
			fisier.write((char*)&this->noEmailuri, sizeof(int));

			for (int i = 0; i < this->noEmailuri; i++) {
				this->emailuri[i].scrieInFisier(fisier);
			}

			fisier.close();
		}
	}

	void loadEmailuri(string numeFisier) {
		ifstream fisier(numeFisier, ios::in | ios::binary);
		if (fisier.is_open()) {
			//citesc email-ul contului
			char buffer[1000];
			int dim;

			//citim dimensiune email
			fisier.read((char*)&dim, sizeof(int));
			//citim email-ul
			fisier.read(buffer, dim * sizeof(char));
			this->email = string(buffer);

			//citim numarul de email-uri
			fisier.read((char*)&this->noEmailuri, sizeof(int));

			if (this->emailuri) {
				delete[] this->emailuri;
			}

			this->emailuri = new Email[this->noEmailuri];

			for (int i = 0; i < this->noEmailuri; i++) {
				this->emailuri[i].citesteDinFisier(fisier);
			}

			fisier.close();
		}
		else
		{
			cout << endl << "Fisierul un a fost deschis";
		}
	}

	friend void operator<<(ostream& console, Inbox& inbox);
};

void operator<<(ostream& console, Email& email) {
	console << endl << "Email de la " << email.from << " cu subiectul '" <<
		email.subiect << "'";
	if (email.solicitaConfirmareCitire) {
		console << endl << "*Solicita confirmare primire";
	}
}

void operator<<(ostream& console, Inbox& inbox) {
	console << endl << "Inbox pentru " << inbox.email;
	for (int i = 0; i < inbox.noEmailuri; i++) {
		cout << inbox.emailuri[i];
	}
}

int main(int argc, char* argv[]) {
	Email email1;
	Email email2("Laborator POO", "gigel@stud.ase.ro", "Exemplu laborator", true);

	Inbox inbox1("eu@stud.ase.ro");
	Inbox inbox2 = inbox1;
	inbox2 = inbox1;

	inbox1(email1);			//operatorul functie
	inbox1(email2);

	cout << inbox1;
}