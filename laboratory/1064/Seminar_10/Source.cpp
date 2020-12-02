#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class InvalidEmailException {
	string message = "";
public:
	InvalidEmailException() {

	}
	InvalidEmailException(string msg) {
		this->message = msg;
	}
	string getMessage() {
		return this->message;
	}
};

class Util {
public:
	static void setEmail(string from, string& emailAddress ) {
		//test@ase.ro
		//test.test@csie.ase.ro
		//not valid: test@asero; test.test@ase
		int indexAt = from.find("@");
		int indexLastDot = from.find_last_of(".");

		if (indexAt == -1) {
			throw new InvalidEmailException("Missing @");
		}
		if (indexLastDot == -1) {
			throw InvalidEmailException("Missing .");
		}
		if (indexAt > indexLastDot) {
			throw InvalidEmailException("The email is invalid. Missing domain");
		}
		emailAddress = from;
	}
};

class Email {
	string from = "";
	char subject[100] = "";
	string content = "";
	bool requestReadConfirmation = false;
public:
	Email(string from, const char* subject, string content) {
		this->setFrom(from);
		//this->subject = subject;
		strcpy_s(this->subject, 100, subject);
		this->subject[99] = '\0';		//in case you copy 100 chars
		this->content = content;
	}

private:
	Email() {

	}
public:
	void setFrom(string from) {
		//test@ase.ro
		//test.test@csie.ase.ro
		//not valid: test@asero; test.test@ase
		int indexAt = from.find("@");
		int indexLastDot = from.find_last_of(".");

		if (indexAt == -1) {
			throw new InvalidEmailException("Missing @");
		}
		if (indexLastDot == -1) {
			throw InvalidEmailException("Missing .");
		}
		if (indexAt > indexLastDot) {
			throw InvalidEmailException("The email is invalid. Missing domain");
		}

		this->from = from;
	}

	friend class Inbox;
	friend void operator<<(ostream& console, Email& email);
};

class Inbox {
	std::string account;
	Email* emails = nullptr;			//composition - "has a" relations
	int noEmails = 0;
public:
	Inbox(string account) {
		//this->account = account;
		Util::setEmail(account, this->account);
	}

	~Inbox() {
		if (emails != nullptr) {
			delete[] emails;
		}
	}

	Inbox(const Inbox& inbox) {
		this->account = inbox.account;
		//don't
		//this->emails = inbox.emails;
		this->emails = new Email[inbox.noEmails];
		for (int i = 0; i < inbox.noEmails; i++) {
			this->emails[i] = inbox.emails[i];	//operator = from Email
		}
		this->noEmails = inbox.noEmails;
	}

	void operator=(const Inbox& inbox) {
		if (this != &inbox) {
			if (this->emails) {
				delete[] this->emails;
			}
			this->account = inbox.account;
			this->emails = new Email[inbox.noEmails];
			for (int i = 0; i < inbox.noEmails; i++) {
				this->emails[i] = inbox.emails[i];	//operator = from Email
			}
			this->noEmails = inbox.noEmails;
		}
	}

	void operator<<(Email email) {
		Email* newEmails = new Email[this->noEmails + 1];
		for (int i = 0; i < this->noEmails; i++) {
			newEmails[i] = this->emails[i];
		}
		newEmails[this->noEmails] = email;
		this->noEmails += 1;

		if (this->emails) {
			delete[] this->emails;
		}

		this->emails = newEmails;
	}

	void operator+=(Email email) {
		*this << email;
	}

	friend void operator<<(ostream& console, Inbox& inbox);
	friend void operator<<(ofstream& console, Inbox& inbox);
};

void operator<<(ostream& console, Inbox& inbox) {
	console << endl << "Inbox for account " << inbox.account;
	if (inbox.noEmails > 0) {
		console << endl << "Emails: ";
		for (int i = 0; i < inbox.noEmails; i++) {
			console << inbox.emails[i];
		}
	}
}

void operator<<(ofstream& console, Inbox& inbox) {
	console << endl << "**************Inbox for account " << inbox.account;
	if (inbox.noEmails > 0) {
		console << endl << "Emails: ";
		for (int i = 0; i < inbox.noEmails; i++) {
			console << inbox.emails[i];
		}
	}
}

void operator<<(ostream& console, Email& email) {
	console << endl << "-----------------------";
	console << endl << "From: " << email.from;
	console << endl << "Subject: " << email.subject;
	console << endl << "Content: " << email.content;
	console << endl << (email.requestReadConfirmation ? "*** Send confirmation ***" : "");
}


int main(int argc, char* argv[]) {
	try {
		Email email1("john@stud.ase.ro", "Zoom link", "Here is the lab zoom link");
		Email email2("alicestud", "Zoom link", "Here is the lab zoom link");
		cout << endl << "End of try block";
	}
	catch (InvalidEmailException ex) {
		cout << endl << ex.getMessage();
	}
	catch (InvalidEmailException* pEx) {
		cout << endl << "*****" << pEx->getMessage();
	}

	while (true) {
		try {
			string emailAddr;
			cout << endl << "Give me your email: ";
			cin >> emailAddr;
			Email email3(emailAddr, "Test email", "Hello");
			break;
		}
		catch (...) {
			cout << endl << "Wrong email. Try again.";
		}
	}

	Inbox inbox("me@ase.ro");

	Email email1("john@stud.ase.ro", "Zoom link", "Here is the lab zoom link");
	Email email2("alice@stud.ase.ro", "Project class", "Here is the class");

	cout << inbox;

	//inbox = inbox + email1;
	//inbox = email1 + inbox;
	inbox += email1;
	inbox << email1;
	inbox << email2;

	cout << inbox;

	ofstream report;
	report.open("My emails.txt", ios::out | ios::trunc);
	if (report.is_open()) {
		report << inbox;

		report.close();
	}
	else {
		cout << endl << "We have a problem with the file";
	}

}