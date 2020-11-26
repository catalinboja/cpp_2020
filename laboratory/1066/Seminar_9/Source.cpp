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

class Utility {
public:
	static void setEmail(string email, string& emailAddr) {
		//test.test@csie.ase.ro
		int indexAt = email.find("@");
		int indexDot = email.find_last_of(".");
		if (indexAt < 0) {
			throw InvalidEmailException("The @ is missing");
		}
		if (indexDot < 0) {
			throw InvalidEmailException("The dot is missing");
		}
		if (indexAt > indexDot) {
			throw InvalidEmailException("The email domain is missing");
		}
		emailAddr = email;
	}
};

class Email {
	string subject = "";
	string from = "";
	char content[100] = "";
	bool requireConfirmation = false;
public:
	Email(string subject, string from, const char* content) {
		this->subject = subject;
		//this->from = from;
		this->setFrom(from);
		//this->content = content;
		strcpy_s(this->content, 99, content);
	}

	void setFrom(string email) {
		//test.test@csie.ase.ro
		int indexAt = email.find("@");
		int indexDot = email.find_last_of(".");
		if (indexAt < 0) {
			throw InvalidEmailException("The @ is missing");
		}
		if (indexDot < 0) {
			throw InvalidEmailException("The dot is missing");
		}
		if (indexAt > indexDot) {
			throw InvalidEmailException("The email domain is missing");
		}
		this->from = email;
	}
private:
	Email() {

	}

	friend class Inbox;
	friend void operator<<(ostream& console, Email& email);
};

class Inbox {
	string account = "";
	Email* emails = nullptr;
	int noEmails = 0;
public:
	Inbox(string account) {
		Utility::setEmail(account, this->account);
	}
	~Inbox() {
		if (this->emails)
			delete[] this->emails;
	}

	Inbox(const Inbox& inbox) {
		this->account = inbox.account;
		this->emails = new Email[inbox.noEmails];
		for (int i = 0; i < inbox.noEmails; i++) {
			this->emails[i] = inbox.emails[i];		//operator = from Email 
		}
	}

	void operator<<(Email email) {
		Email* newArray = new Email[this->noEmails + 1];
		for (int i = 0; i < this->noEmails; i++) {
			newArray[i] = this->emails[i];
		}
		newArray[this->noEmails] = email;
		this->noEmails += 1;
		if (this->emails)
			delete[] this->emails;
		this->emails = newArray;
	}

	void operator+=(Email email) {
		(*this) << email;
	}

	friend void operator<<(ostream& console, Inbox& inbox);
	friend void operator<<(ofstream& console, Inbox& inbox);
};

void operator<<(ostream& console, Email& email) {
	console << endl << "Subject: " << email.subject;
	console << endl << "From: " << email.from;
	console << endl << "Content: " << email.content;
	console << endl << (email.requireConfirmation ? "*Confirmation required*" : "");
}

void operator<<(ostream& console, Inbox& inbox) {
	console << endl << " --------------------- ";
	console << endl << "The inbox for " << inbox.account;
	console << endl << "Emails: ";
	if (inbox.emails != nullptr) {
		for (int i = 0; i < inbox.noEmails; i++) {
			console << endl << inbox.emails[i];
		}
	}
}

void operator<<(ofstream& console, Inbox& inbox) {
	console << endl << " ------************************************--------------- ";
	console << endl << "The inbox for " << inbox.account;
	console << endl << "Emails: ";
	if (inbox.emails != nullptr) {
		for (int i = 0; i < inbox.noEmails; i++) {
			console << endl << inbox.emails[i];
		}
	}
}

int main(int argc, char* argv[]) {

	try {
		Email email1("Zoom link", "john@stud.ase.ro", "Here is the seminar link");
		Email email2("Assignment link", "alice@studasero", "Here is the assignment link");
	}
	catch (InvalidEmailException ex) {
		cout << endl << "The email address is wrong: " << ex.getMessage();
	}
	catch (InvalidEmailException* pEx) {
		cout << endl << "The email address is wrong: " << pEx->getMessage();
		delete pEx;
	}
	catch (...) {
		cout << endl << "Houston, we have a problem !";
	}

	while (true) {
		try {
			string email;
			cout << endl << "Give me your email: ";
			cin >> email;
			Email emailObj("none", email, "");
			break;
		}
		catch (InvalidEmailException ex) {
			cout << endl << "Wrong email: " << ex.getMessage();
		}
	}

	Inbox inbox("me@ase.ro");
	cout << inbox;

	Email email1("Zoom link", "john@stud.ase.ro", "Here is the seminar link");
	Email email2("Assignment link", "alice@stud.ase.ro", "Here is the assignment link");

	inbox += email1;
	//inbox = inbox + email1;
	inbox << email2;

	cout << inbox;

	ofstream myEmails;
	myEmails.open("MyEmails.txt", ios::out | ios::trunc);
	if (myEmails.is_open()) {
		myEmails << "This is my inbox content" << endl;
		myEmails << inbox;
		myEmails.close();
	}
	else
		cout << endl << "**************** File not opened";

}