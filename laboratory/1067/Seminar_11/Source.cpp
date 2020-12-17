#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class Util {
public:
	static void writeString(ofstream& file, string value) {
		int dim = value.size() + 1;		//because we store the \0 also 
		//write the size
		file.write((char*)&dim, sizeof(int));
		//write the string value
		file.write(value.c_str(), dim * sizeof(char));
	}

	static void readString(ifstream& file, string& value) {
		int dim;
		file.read((char*)&dim, sizeof(int));
		char buffer[1000];
		file.read(buffer, dim * sizeof(char));
		value = string(buffer);
	}
};

class Email {
	string from = "";
	char subject[100] = "";
	char content[100] = "";
	bool requireReadConfirmation = false;
public:
	Email(string From, const char* Subject, const char* Content, bool Confirmation)
		:from(From), requireReadConfirmation(Confirmation)  {
		//this->from = From;
		strcpy_s(this->subject, sizeof(Email::subject), Subject);
		strcpy_s(this->content, sizeof(Email::content), Content);
	}

	Email() {

	}

	void serialize(ofstream& file) {
		//write the from
		Util::writeString(file, this->from);
		//write the subject and the content

		//string temp = string(this->content);
		//Util::writeString(file, temp);

		file.write(this->content, sizeof(Email::content) * sizeof(char));
		file.write(this->subject, sizeof(Email::subject) * sizeof(char));
		//write the confirmation flag
		file.write((char*)&this->requireReadConfirmation, sizeof(bool));
	}

	void deserialize(ifstream& file) {
		Util::readString(file, this->from);
		file.read(this->content, sizeof(Email::content) * sizeof(char));
		file.read(this->subject, sizeof(Email::subject) * sizeof(char));
		file.read((char*)&this->requireReadConfirmation, sizeof(bool));
	}

	friend void operator<<(ostream& console, Email& email);
};

class Inbox {
	string account = "";
	Email* emails = nullptr;
	int noEmails = 0;
public:
	Inbox(string Account) : account(Account) {

	}
	void setEmails(Email* emails, int noEmails) {
		if (emails != nullptr) {
			if (this->emails) {
				delete[] this->emails;
			}
			this->emails = new Email[noEmails];
			for (int i = 0; i < noEmails; i++) {
				this->emails[i] = emails[i];
			}
			this->noEmails = noEmails;
		}
	}

	Inbox(const Inbox& inbox): account(inbox.account) {
		this->setEmails(inbox.emails, inbox.noEmails);
	}

	void operator=(Inbox& inbox) {
		if (this != &inbox) {
			this->account = inbox.account;
			this->setEmails(inbox.emails, inbox.noEmails);
		}
	}
	~Inbox() {
		if (this->emails)
			delete[] this->emails;
	}

	//overload function operator
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

	void backup(string filename) {
		ofstream file(filename, ios::out | ios::trunc | ios::binary);
		if (file.is_open()) {
			//write the account
			Util::writeString(file, this->account);
			//write the no emails
			file.write((char*)&this->noEmails, sizeof(int));
			//write the emails
			for (int i = 0; i < this->noEmails; i++) {
				this->emails[i].serialize(file);
			}
			file.close();
		}
	}

	void import(string filename) {
		ifstream file(filename, ios::in | ios::binary);
		if (file.is_open()) {
			//read the account
			Util::readString(file, this->account);
			//read the no emails
			file.read((char*)&this->noEmails, sizeof(int));

			if (this->emails)
				delete[] this->emails;
			this->emails = new Email[this->noEmails];

			for (int i = 0; i < this->noEmails; i++) {
				this->emails[i].deserialize(file);
			}
			file.close();
		}
		else
		{
			cout << endl << "The file is not opened";
		}
	}

	friend void operator<<(ostream& console, Inbox& inbox);
};

void operator<<(ostream& console, Email& email) {
	console << endl << "Email from " << email.from << " with subject '" <<
		email.subject << "'";
	console << endl << "Content: " << email.content;
	if (email.requireReadConfirmation) {
		console << endl << "* requires confirmation";
	}
}

void operator<<(ostream& console, Inbox& inbox) {
	console << endl << "------------------------------";
	console << endl << "\tInbox for " << inbox.account;
	for (int i = 0; i < inbox.noEmails; i++) {
		console << inbox.emails[i];
	}
}

int main(int argc, char* argv[]) {
	Inbox inbox1("me@stud.ase.ro");
	Email spam;
	Email email1("alice@stud.ase.ro", "Assignment", "Here is my solution", true);
	Email email2("john@stud.ase.ro", "Question", "Where is the source code", true);

	Inbox inbox2 = inbox1;
	inbox2 = inbox1;

	cout << email1;
	cout << inbox1;

	inbox1(email1);				//function operator
	inbox1(email2);
	inbox1(spam);
	cout << inbox1;

	//inbox1.backup("EmailBck.emails");
	inbox2.import("EmailBck.emails");
	cout << endl << "****************";
	cout << inbox2;


}