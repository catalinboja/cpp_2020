#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Util {
public:
	static void writeString(ofstream& file, string value) {
		//write the number of characters + \0
		int dim = value.size() + 1;
		file.write((char*)&dim, sizeof(int));
		//write the string value
		file.write(value.c_str(), dim * sizeof(char));
	}

	static void readString(ifstream& file, string& value) {
		//read the dimension
		int dim;
		file.read((char*)&dim, sizeof(int));
		//read the value
		char buffer[1000];
		file.read(buffer, dim * sizeof(char));
		value = string(buffer);
	}
};

class Email {
	string from = "";
	char subject[50] = "";
	char content[300] = "";
public:
	Email(){
	}

	Email(string From, const char* Subject, const char* Content):from(From) {
		//this->from = From;
		strcpy_s(this->subject, sizeof(Email::subject), Subject);
		strcpy_s(this->content, sizeof(Email::content), Content);
	}

	void writeToFile(ofstream& file) {
		//write the from
		Util::writeString(file, this->from);
		file.write(this->subject, sizeof(Email::subject) * sizeof(char));
		file.write(this->content, sizeof(Email::content) * sizeof(char));
	}

	void readFromFile(ifstream& file) {
		Util::readString(file, this->from);
		file.read(this->subject, sizeof(Email::subject) * sizeof(char));
		file.read(this->content, sizeof(Email::content) * sizeof(char));
	}

	friend void operator<<(ostream& console, Email& email);
};

class Inbox {
	Email* emails = nullptr;
	int noEmails = 0;
	string account = "";
public:
	Inbox() {
	}

	Inbox(string Account) : account(Account) {
	}

	void setEmails(Email* emails, int noEmails) {
		if (this->emails) {
			delete[] this->emails;
		}
		this->emails = new Email[noEmails];
		for (int i = 0; i < noEmails; i++) {
			this->emails[i] = emails[i];
		}
		this->noEmails = noEmails;
	}

	Inbox(const Inbox& inbox): account(inbox.account) {
		this->setEmails(inbox.emails, inbox.noEmails);
	}

	~Inbox() {
		if (this->emails)
			delete[] this->emails;
	}

	void operator=(Inbox& inbox) {
		if (this != &inbox) {
			this->account = inbox.account;
			this->setEmails(inbox.emails, inbox.noEmails);
		}
	}

	//overloading the function operator
	void operator()(Email& email) {
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

	void backup(string filename) {
		ofstream file(filename, ios::out | ios::binary | ios::trunc);
		if (file.is_open()) {
			//write the account name
			Util::writeString(file, this->account);
			//write the number of emails
			file.write((char*)&this->noEmails, sizeof(int));

			for (int i = 0; i < this->noEmails; i++) {
				this->emails[i].writeToFile(file);
			}

			file.close();
		}
	}

	void import(string filename) {
		ifstream file(filename, ios::in | ios::binary);
		if (file.is_open()) {
			Util::readString(file, this->account);
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
		else
		{
			cout << endl << "The file is not opened";
		}
	}

	friend void operator<<(ostream& console, Inbox& inbox);
};

void operator<<(ostream& console, Email& email) {
	console << endl << "Email from " << email.from << " with subject '"
		<< email.subject << "'";
	console << endl << "The content: " << email.content;
}

void operator<<(ostream& console, Inbox& inbox) {
	console << endl << "----------------------------";
	console << endl << "The inbox for the account " << inbox.account;
	for (int i = 0; i < inbox.noEmails; i++) {
		console << inbox.emails[i];
	}
}

int main(int argc, char* argv[]) {
	Email email1;
	Email email2("john@stud.ase.ro", "Project deadline", "The deadline is next week");

	Inbox inbox1;
	Inbox inbox2("me@stud.ase.ro");

	 inbox2(email1);			//function operator
	//inbox2(email2, email1, 10, 25);
	 inbox2(email2);

	 cout << inbox2;

	 //inbox2.backup("Emails.inbox");
	 inbox1.import("Emails.inbox");
	 cout << endl << "----------------- " << inbox1;
}
