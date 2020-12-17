#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Util {
public:
	static void writeString(ofstream& file, const string& value) {
		//count with the \0 
		int dim = value.size() + 1;
		file.write((char*)&dim, sizeof(int));
		file.write(value.c_str(), dim * sizeof(char));
	}

	static void readString(ifstream& file, string& value) {
		int dim;
		char buffer[1000];
		file.read((char*)&dim, sizeof(int));
		file.read(buffer, dim * sizeof(char));
		value = string(buffer);
	}
};


class Email {
	string from = "";
	char subject[100] = "";
	char content[100] = "";
	bool requestReadConfirmation = false;
public:
	Email() {

	}

	Email(string From, const char* Subject, const char* Content, bool Confirmation)
		:from(From), requestReadConfirmation(Confirmation) {
		this->from = From;
		this->requestReadConfirmation = Confirmation;
		strcpy_s(this->subject, sizeof(Email::subject), Subject);
		strcpy_s(this->content, sizeof(Email::content), Content);
	}

	void write2File(ofstream& file) {
		//write From
		Util::writeString(file, this->from);
		//write content and subject - write the entire static array
		file.write(this->content, sizeof(Email::content) * sizeof(char));
		file.write(this->subject, sizeof(Email::subject) * sizeof(char));
		//the confirmation
		file.write((char*)&this->requestReadConfirmation, sizeof(bool));
	}

	void readFromFile(ifstream& file) {
		Util::readString(file, this->from);
		file.read(this->content, sizeof(Email::content) * sizeof(char));
		file.read(this->subject, sizeof(Email::subject) * sizeof(char));
		file.read((char*)&this->requestReadConfirmation, sizeof(bool));
	}

	friend void operator<<(ostream& console, Email& email);
};

class Inbox {
	string accountEmail = "";
	Email* emails = nullptr;
	int noEmails = 0;
public:
	Inbox(string account):accountEmail(account) {

	}

	Inbox(const Inbox& inbox):accountEmail(inbox.accountEmail) {
		this->emails = new Email[inbox.noEmails];
		for (int i = 0; i < inbox.noEmails; i++) {
			this->emails[i] = inbox.emails[i];
		}
		this->noEmails = inbox.noEmails;
	}

	~Inbox() {
		if (this->emails)
			delete[] this->emails;
	}

	void operator=(Inbox& inbox) {
		if (this != &inbox) {
			this->accountEmail = inbox.accountEmail;

			if (this->emails)
				delete[] this->emails;

			this->emails = new Email[inbox.noEmails];
			for (int i = 0; i < inbox.noEmails; i++) {
				this->emails[i] = inbox.emails[i];
			}
			this->noEmails = inbox.noEmails;
		}
	}

	//overloading function operator
	void operator()(Email& email) {
		Email* newEmails = new Email[this->noEmails + 1];
		for (int i = 0; i < this->noEmails; i++) {
			newEmails[i] = this->emails[i];
		}
		newEmails[this->noEmails] = email;
		this->noEmails += 1;
		if (this->emails)
			delete[] this->emails;
		this->emails = newEmails;
	}

	void backUpEmails(string filename) {
		ofstream file(filename, ios::out | ios::trunc | ios::binary);
		if (file.is_open()) {
			//write the account email
			Util::writeString(file, this->accountEmail);
			//write the no of emails
			file.write((char*)&this->noEmails, sizeof(int));

			for (int i = 0; i < this->noEmails; i++) {
				this->emails[i].write2File(file);
			}

			file.close();
		}
	}

	void importEmails(string filename) {
		ifstream file(filename, ios::in | ios::binary);
		if (file.is_open()) {
			//read account
			Util::readString(file, this->accountEmail);
			//read no emails
			file.read((char*)&this->noEmails, sizeof(int));
			if (this->emails)
				delete[] this->emails;
			this->emails = new Email[this->noEmails];
			for (int i = 0; i < this->noEmails; i++) {
				this->emails[i].readFromFile(file);
			}
			file.close();
		}
		else {
			cout << endl << "******** File NOT opened";
		}
	}

	friend void operator<<(ostream& console, Inbox& inbox);
};

void operator<<(ostream& console, Email& email) {
	console << endl << "Email from " << email.from << " with subject '" <<
		email.subject << "'";
	console << endl << "Content: " << email.content;
	if (email.requestReadConfirmation) {
		console << endl << "* Requires confirmation";
	}
}

void operator<<(ostream& console, Inbox& inbox) {

	console << endl << "---------------------------------";
	console << endl << "Account " << inbox.accountEmail;
	console << endl << "Emails: ";
	for (int i = 0; i < inbox.noEmails; i++) {
		cout << endl << inbox.emails[i];
	}
}

int main(int argc, char* argv[]) {
	Email email1;
	Email email2("john@stud.ase.ro", "Assignment", "Here is the .cpp", true);

	Inbox inbox1("me@stud.ase.ro");
	Inbox inbox2 = inbox1;
	inbox2 = inbox1;

	cout << email2;
	cout << inbox1;

	inbox2(email2);				//function operator
	inbox2(email1);
	cout << inbox2;

	//inbox2.backUpEmails("EmailsBck.emails");

	Inbox inbox3("test@stud.ase.ro");
	inbox3.importEmails("EmailsBck.emails");

	cout << endl << "********** Imported emails";
	cout << inbox3;
}

