#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class InvalidEmailException {
	string message;
public:
	InvalidEmailException() {
		this->message = "";
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
	static void setEmailAddr(string email, string& emailAddr) {
		//contact@ase.ro
		int atIndex = email.find("@");
		int dotIndex = email.find_last_of(".");
		if (atIndex < 0) {
			throw InvalidEmailException("Missing @");
		}
		if (dotIndex < 0) {
			throw InvalidEmailException("Missing .");
		}
		if (atIndex > dotIndex) {
			throw InvalidEmailException("@ is after .");
		}
		emailAddr = email;
	}
};

class Email {
	string subject = "";
	string from = "";
	int priority = 0;
	char content[100] = "";
public: 
	Email(string subject, string from, const char* content, int priority) {
		this->subject = subject;
		//this->from = from;
		this->setFrom(from);
		this->priority = priority;
		//this->content = content;
		strcpy_s(this->content, 100, content);
	}

private:
	Email() {

	}

public:
	void setFrom(string email) {
		//contact@ase.ro
		int atIndex = email.find("@");
		int dotIndex = email.find_last_of(".");
		if (atIndex < 0) {
			throw (new InvalidEmailException("Missing @"));
		}
		if (dotIndex < 0) {
			throw InvalidEmailException("Missing .");
		}
		if (atIndex > dotIndex) {
			throw InvalidEmailException("@ is after .");
		}
		this->from = email;
	}

	friend void operator<<(ostream& console, const Email& email);
	friend class Inbox;

};

void operator<<(ostream& console, const Email& email) {
	console << endl << "Email from " << email.from << " with priority " << email.priority;
	console << endl << "Subject: " << email.subject;
	console << endl << "Content: " << email.content;

}

class Inbox {
	string ownerEmail;
	Email* emails = nullptr;
	int noEmails = 0;
public:
	Inbox(string email) {
		//this->ownerEmail = email;
		Utility::setEmailAddr(email, this->ownerEmail);
	}

	~Inbox() {
		if (this->emails) {
			delete[] this->emails;
		}
	}

	Inbox(const Inbox& inbox) {
		this->ownerEmail = inbox.ownerEmail;
		this->emails = new Email[inbox.noEmails];
		for (int i = 0; i < inbox.noEmails; i++) {
			this->emails[i] = inbox.emails[i];
		}
	}

	void operator+=(Email email) {
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

	void operator<<(Email email) {
		(*this) += email;
	}

	friend void operator<<(ostream& console, const Inbox& inbox);
	friend void operator<<(ofstream& file, const Inbox& inbox);
};

void printValue(int value) {
	cout << endl << value;
}

void printValue(int* pValue) {
	cout << endl << (*pValue);
}

void operator<<(ostream& console, const Inbox& inbox) {
	console << endl << "------------------------------";
	console << endl << "Inbox for " << inbox.ownerEmail;
	if (inbox.emails != nullptr) {
		console << endl << "Emails: ";
		for (int i = 0; i < inbox.noEmails; i++) {
			console << inbox.emails[i];
		}
	}
}


void operator<<(ofstream& file, const Inbox& inbox) {
	file << endl << "------------------------------";
	file << endl << "Inbox for " << inbox.ownerEmail;
	if (inbox.emails != nullptr) {
		file << endl << "Emails: ";
		for (int i = 0; i < inbox.noEmails; i++) {
			file << endl << "*----------------------------------*";
			file << inbox.emails[i]; //we use the ostream version for Email
		}
	}
}

int main(int argc, char* argv[]) {
	try {
		Email testEmail1("Zoom link", "john@stud.ase.ro", "Here is the zoom link", 1);
		Email testEmail2("Zoom link", "johns@tud", "Here is the zoom link", 1);
	}
	catch (InvalidEmailException ex) {
		cout << endl << "Invalid email: " << ex.getMessage();
	}
	catch (InvalidEmailException* pEx) {
		cout << endl << "Invalid email (by pointer): " << pEx->getMessage();
		delete pEx;
	}
	catch (...) {
		cout << endl << "Houston we have a problem !";
	}

	Email testEmail1("Zoom link", "john@stud.ase.ro", "Here is the zoom link", 1);
	Email testEmail2("Project files link", "john@stud.ase.ro", "Here is my part for project", 1);
	Email testEmail3("Project files", "alice@stud.ase.ro", "Here are my files", 1);

	Inbox myInbox("me@ase.ro");
	cout << myInbox;
	// +, +=, <<
	// myInbox << testEmail1;
	myInbox += testEmail1;
	myInbox += testEmail2;
	myInbox << testEmail3;

	cout << myInbox;

	ofstream printEmails;
	printEmails.open("MyInbox.txt", ios::out | ios::trunc);
	if (printEmails.is_open()) {
		printEmails << "My emails print" << endl;
		printEmails << myInbox;	//we are using the ofstream version of <<
	}
	else {
		cout << endl << "Error ************ File not opened !";
	}

}
