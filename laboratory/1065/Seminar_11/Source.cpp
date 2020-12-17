#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Utility {
public:
	static void writeString(ofstream& file, string value) {
		int size = value.size() + 1;	//we will store also \0
		file.write((char*)&size, sizeof(int));
		file.write(value.c_str(), size * sizeof(char));
	}

	static void readString(ifstream& file, string& value) {
		int size;
		file.read((char*)&size, sizeof(int));
		char buffer[1000];
		file.read(buffer, size * sizeof(char));
		value = string(buffer);
	}
};

class Email {
	string from = "";
	char subject[100] = "";
	bool askReadConfirmation = false;
public:
	Email(string from, const char* subject, bool requireConfirmation) {
		this->askReadConfirmation = requireConfirmation;
		this->from = from;
		strcpy(this->subject, subject);
	}

	Email() {

	}

	void writeIntoFile(ofstream& file) {
		Utility::writeString(file, this->from);
		//we write the subject = the entire array
		file.write(this->subject, sizeof(Email::subject) * sizeof(char));
		file.write((char*)&this->askReadConfirmation, sizeof(bool));
	}

	void readFromFile(ifstream& file) {
		int subkSize = sizeof(Email::subject);
		Utility::readString(file, this->from);
		file.read(this->subject, sizeof(Email::subject) * sizeof(char));
		file.read((char*)&this->askReadConfirmation, sizeof(bool));
	}

	friend void operator<<(ostream& console, Email& email);
};

class Inbox {
	Email* emails = nullptr;
	int noEmails = 0;
	string email = "";
public:
	Inbox(string Email):email(Email) {
		//this->email = Email;
	}

	//overloading function operator
	void operator()(Email email) {
		Email* newEmails = new Email[this->noEmails + 1];
		for (int i = 0; i < this->noEmails; i++) {
			newEmails[i] = this->emails[i];
		}
		newEmails[this->noEmails] = email;
		if (this->emails) {
			delete[] this->emails;
		}
		this->noEmails += 1;
		this->emails = newEmails;
	}

	Inbox(const Inbox& inbox) {
		this->email = inbox.email;
		this->noEmails = inbox.noEmails;
		this->emails = new Email[this->noEmails];
		for (int i = 0; i < this->noEmails; i++) {
			this->emails[i] = inbox.emails[i];
		}
	}

	~Inbox() {
		if (this->emails)
			delete[] this->emails;
	}

	void operator=(Inbox& inbox) {
		if (this != &inbox) {
			this->email = inbox.email;
			this->noEmails = inbox.noEmails;
			if (this->emails) {
				delete[] this->emails;
			}
			this->emails = new Email[this->noEmails];
			for (int i = 0; i < this->noEmails; i++) {
				this->emails[i] = inbox.emails[i];
			}
		}
	}

	void exportEmails(string filename) {
		ofstream file(filename, ios::out | ios::trunc | ios::binary);
		if (file.is_open()) {
			//we write the account email
			Utility::writeString(file, this->email);
			//write the number of emails
			file.write((char*)&this->noEmails, sizeof(int));
			//write each email
			for (int i = 0; i < this->noEmails; i++) {
				this->emails[i].writeIntoFile(file);
			}
			file.close();
		}
	}

	void importEmails(string filename) {
		ifstream file(filename, ios::in | ios::binary);
		if (file.is_open()) {
			//read the account email
			Utility::readString(file, this->email);
			//read the number of emails
			file.read((char*)&this->noEmails, sizeof(int));

			if (this->emails) {
				delete[] this->emails;
			}
			this->emails = new Email[this->noEmails];
			for (int i = 0; i < this->noEmails; i++) {
				this->emails[i].readFromFile(file);
			}
			file.close();
		}
		else {
			cout << endl << "File not there";
		}
	}

	friend void operator<<(ostream& console, Inbox& inbox);
};

void operator<<(ostream& console, Email& email) {
	console << endl << "Email from " << email.from << " with subject '" <<
		email.subject << "'";
	if (email.askReadConfirmation) {
		console << endl << "*Requires confirmation";
	}
}

void operator<<(ostream& console, Inbox& inbox) {
	console << endl << "Emails for " << inbox.email;
	for (int i = 0; i < inbox.noEmails; i++) {
		cout << inbox.emails[i];
	}
}

int main(int argc, char* argv[]) {
	Email email1("john@stud.ase.ro", "Assignment", true);
	Email email2("alice@stud.ase.ro", "Assignment", true);
	Inbox inbox("me@email.com");
	//inbox = inbox + email1;
	//inbox = email1 + inbox;
	//inbox += email1;
	//inbox << email1;
	//inbox = inbox & email1;
	//inbox = inbox | email1;
	inbox(email1);			//function operator
	inbox(email2);

	cout << endl << inbox;

	//export emails
	//inbox.exportEmails("MyEmails.eml");

	Inbox inbox2("alice@Stud.ase.ro");
	cout << inbox2;
	inbox2.importEmails("MyEmails.eml");
	cout << endl << "-----------------------";
	cout << inbox2;
}

