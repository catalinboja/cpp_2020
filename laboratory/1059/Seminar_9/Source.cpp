#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class EmailInvalidExceptie {
	string mesaj = "";
	int codEroare = 0;
public:
	EmailInvalidExceptie() {

	}

	EmailInvalidExceptie(string mesaj, int cod) {
		this->mesaj = mesaj;
		this->codEroare = cod;
	}

	string getMesaj() {
		return this->mesaj;
	}

	int getCod() {
		return this->codEroare;
	}
};

class ExceptieServer {

};

class Util {
public:
	static void setEmail(string email, string& adresa) {
		//string numar = "1234";
		//int valoare = atoi(numar.c_str());

		//test.me@csie.ase.ro
		int indexAt = email.find("@");
		int indexPunct = email.find_last_of(".");
		if (indexAt < 0) {
			throw EmailInvalidExceptie();
			//throw new EmailInvalidExceptie();
			//throw "Lipseste @";
		}
		if (indexPunct < 0) {
			//throw EmailInvalidExceptie();
			//throw "Lipseste .";
			throw EmailInvalidExceptie("Lipseste .", 1);
		}
		if (indexAt > indexPunct) {
			//throw EmailInvalidExceptie();
			//throw "@ este dupa .";
			throw EmailInvalidExceptie("@ este dupa .", 2);
		}
	}
};

class Email {
	string from = "";
	string subject = "";
	char continut[100] = "";
	bool confirmarePrimire = false;
public:
	Email(string from, string subject, const char* continut, bool cuConfirmarePrimire) {
		//this->from = from;
		this->setFrom(from);
		this->subject = subject;
		this->confirmarePrimire = cuConfirmarePrimire;
		//this->continut = continut;
		strcpy_s(this->continut, 100, continut);
	}
private:
	Email() {

	}
public:
	void setFrom(string email) {

		//string numar = "1234";
		//int valoare = atoi(numar.c_str());

		//test.me@csie.ase.ro
		int indexAt = email.find("@");
		int indexPunct = email.find_last_of(".");
		if (indexAt < 0) {
			throw EmailInvalidExceptie();
			//throw new EmailInvalidExceptie();
			//throw "Lipseste @";
		}
		if (indexPunct < 0) {
			//throw EmailInvalidExceptie();
			//throw "Lipseste .";
			throw EmailInvalidExceptie("Lipseste .", 1);
		}
		if (indexAt > indexPunct) {
			//throw EmailInvalidExceptie();
			//throw "@ este dupa .";
			throw EmailInvalidExceptie("@ este dupa .", 2);
		}
		this->from = email;
	}

	friend class Inbox;
};

class Inbox {
	string contEmail = "";
	Email* emailuri = nullptr;
	int nrMesaje = 0;
public:
	Inbox(string email) {
		//this->contEmail = email;
		Util::setEmail(email, this->contEmail);
	}
	
	~Inbox() {
		if (this->emailuri)
			delete[] this->emailuri;
	}

	//TO DO 
	//constructor de copiere
	//operator =

	void operator<<(const Email& email) {
		Email* vectorNou = new Email[this->nrMesaje + 1];
		for (int i = 0; i < this->nrMesaje; i++) {
			vectorNou[i] = this->emailuri[i];		//operator = din Email
		}
		vectorNou[this->nrMesaje] = email;
		this->nrMesaje += 1;
		if (this->emailuri)
			delete[] this->emailuri;
		this->emailuri = vectorNou;
	}

	void operator+=(const Email& email) {
		(*this) << email;
	}
};

void afisareNumar(int numar) {
	cout << endl << numar;
}

void afisareNumar(int* numar) {
	cout << endl << numar;
}

int main(int argc, char* argv[]) {

	try {
		Email email1("gigel@stud.ase.ro",
			"Link Zoom seminar", "Iti trimit link-ul pentru Zoom", false);
		Email email2("gigelstud.ro",
			"Link Zoom seminar", "Iti trimit link-ul pentru Zoom", false);
		cout << endl << "Sfarsit try";
		throw ExceptieServer();
	}
	catch(EmailInvalidExceptie ex) {
		cout << endl << "Avem o problema";
		cout << endl << "Detalii: " << ex.getMesaj();

	}
	catch (EmailInvalidExceptie* pEx) {
		cout << endl << "Avem o problema";
		cout << endl << "Detalii: " << pEx->getMesaj();
		delete pEx;
	}
	catch (const char* ex) {
		cout << endl << ex;
		//cum determin care este motivul ?
		if (strcmp(ex, "Lipseste @") == 0) {
			cout << endl << "Incercam sa adaugam noi un @";
		}
	}
	catch (...) {
		cout << endl << "Avem o problema generica !!!";
	}

	while (true) {
		try {
			cout << endl << "Email-ul tau ?";
			string email;
			cin >> email;
			Email email3(email, "Test", "", false);
			break;
		}
		catch (EmailInvalidExceptie ex) {
			cout << endl << "Valoare gresita " << ex.getMesaj();
		}
	}

	afisareNumar(10);

	Email email1("gigel@stud.ase.ro",
		"Link Zoom seminar", "Iti trimit link-ul pentru Zoom", false);
	Email email2("gigel@stud.ase.ro",
		"Link Zoom seminar", "Iti trimit link-ul pentru Zoom", false);

	Inbox inbox("eu@ase.ro");
	//inbox += email1;
	//inbox = inbox + email1;
	inbox << email1;
	inbox << email2;

}