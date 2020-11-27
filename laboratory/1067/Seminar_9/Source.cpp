#include <iostream>
#include <string>
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
	static void setEmail(string email, string& emailAddress) {
		//test@ase.ro  test@csie.ase.ro    test.test@csie.ase.ro
		//test.test@ase
		int indexAt = email.find("@");
		int indexDot = email.find_last_of(".");
		if (indexAt < 0) {
			throw new InvalidEmailException("Missing @");
		}
		if (indexDot < 0) {
			throw InvalidEmailException("Missing .");
		}
		if (indexAt > indexDot) {
			throw InvalidEmailException("Invalid email. Missing domain");
		}
		emailAddress = email;
	}
};

class Email {
	string from = "";
	string subject = "";
	char content[1000] = "";
	bool requireReceiveConfirmation = false;
public:
	Email(string from, string subject, const char* content) {
		//this->from = from;
		this->setFrom(from);
		//this->content = content;
		strcpy_s(this->content, 1000, content);
		this->subject = subject;
	}
private:
	Email() {

	}
public:
	void setFrom(string email) {
		//test@ase.ro  test@csie.ase.ro    test.test@csie.ase.ro
		//test.test@ase
		int indexAt = email.find("@");
		int indexDot = email.find_last_of(".");
		if(indexAt < 0) {
			throw new InvalidEmailException("Missing @");
		}
		if(indexDot < 0) {
			throw InvalidEmailException("Missing .");
		}
		if (indexAt > indexDot) {
			throw InvalidEmailException("Invalid email. Missing domain");
		}
		this->from = email;
	}

	bool operator!=(string spamText) {
		if (this->subject.find(spamText) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	friend class Inbox;
	friend void operator<<(ostream& console, Email email);
};

class Inbox {
	string account = "";
	Email* emails = nullptr;			//composition - "has a" relation
	int noEmails = 0;
public:
	Inbox(string account) {
		//this->account = account;
		Util::setEmail(account, this->account);
	}

	~Inbox() {
		if (this->emails) {
			delete[] this->emails;
		}
	}

	Inbox(const Inbox& inbox) {
		this->account = inbox.account;
		this->emails = new Email[inbox.noEmails];
		for (int i = 0; i < inbox.noEmails; i++) {
			this->emails[i] = inbox.emails[i]; //operator = from Email
		}
		this->noEmails = inbox.noEmails;
	}

	void operator<<(Email& email) {
		Email* newArray = new Email[this->noEmails + 1];
		for (int i = 0; i < this->noEmails; i++) {
			newArray[i] = this->emails[i];
		}
		newArray[this->noEmails] = email;
		this->noEmails += 1;
		if (this->emails) {
			delete[] this->emails;
		}
		this->emails = newArray;
	}

	void operator+=(Email& email) {
		(*this) << email;
	}

	friend void operator<<(ostream& console, Inbox& inbox);
};

void operator<<(ostream& console, Inbox& inbox) {
	console << endl << "--------------------------";
	console << endl << "Inbox for " << inbox.account;
	if (inbox.emails) {
		cout << endl << "Received emails: ";
		for (int i = 0; i < inbox.noEmails; i++) {
			console << inbox.emails[i];
		}
	}
}

void operator<<(ostream& console, Email email) {
	console << endl << "Message from " << email.from;
	console << endl << "Subject: " << email.subject;
	console << endl << "Content: " << email.content;
	console << endl <<
		(email.requireReceiveConfirmation ? "* Requires confirmation *" : "");
}

int main(int argc, char* argv[]) {

	Email email1("john@stud.ase.ro", "Zoom link for seminar", "Here is the Zoom link");

	while (true) {
		try {
			string emailAddress;
			cout << endl << "Give me your email address: ";
			cin >> emailAddress;
			Email temp(emailAddress, "New email", "John");
			break;
		}
		catch (InvalidEmailException ex) {
			cout << endl << "Wrong email: " << ex.getMessage();
		}
		catch (InvalidEmailException* pEx) {
			cout << endl << "Wrong email**: " << pEx->getMessage();
			delete pEx;
		}
		catch (...) {
			cout << endl << "Houston, we have a problem !";
		}
	}

	Email email2("john@stud.ase.ro", "Zoom link for seminar", "Here is the Zoom link");
	Email email3("alice@stud.ase.ro", "My part for the project", "Here is archive");
	Email spam("scam@scam.com", "You won the lottery", "Give me your account");
	Inbox inbox("me@ase.ro");
	cout << inbox;

	//inbox  = inbox + email1;
	inbox += email1;
	inbox << email2;
	inbox << email3;

	cout << inbox;

	string spamSubject = "You won the lottery";
	if (email1 != spamSubject) {
		cout << endl << "Is not spam";
	}
	else
	{
		cout << endl << "Is spam";
	}

	if (spam != spamSubject) {
		cout << endl << "Is not spam";
	}
	else
	{
		cout << endl << "Is spam";
	}
}