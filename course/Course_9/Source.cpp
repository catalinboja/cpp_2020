#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum StudentType {BACHELOR, MASTER, PHD};

/*
	Disclaimer: we have a class without dynamic fields 
*/

class NameException {
	string description = "" ;
	int errCode = 0;
public:
	NameException(string description, int errCode) {
		this->description = description;
		this->errCode = errCode;
	}

	NameException() {

	}

	string getDescription() {
		return this->description;
	}

	int getErrorCode() {
		return this->errCode;
	}
};

class AgeException {

};

class TypeException {

};

class NewException {

};

class Student {
	string name = "";
	int age = 0;
	StudentType type = StudentType::BACHELOR;
public:
	void setName(string Name) {
		if (Name.size() > 3) {
			this->name = Name;
		}
		else {
			//throw string("The name is too short");
			//throw "The name is too short";
			throw NameException();
		}
	}

	void setNameUpper(string Name) {
		if (Name.size() > 5) {
			this->name = Name;
		}
		else {
			throw NameException("In nameUpper",15);
		}
	}

	void setAge(int Age) {
		if (Age >= 14) {
			this->age = Age;
		}
		else {
			//throw "The age is too small";
			throw AgeException();
		}
	}

	void setType(StudentType Type) {
		this->type = Type;
	}

	void setType(int Type) {
		//this->type = Type;
		switch (Type)
		{
		case 0:
			this->type = StudentType::BACHELOR;
			break;
		case 1:
			this->type = StudentType::MASTER;
			break;
		case 2:
			this->type = StudentType::PHD;
			break;
		default:
			//throw "Wrong type";
			throw TypeException();
		}
	}
};

int main(int argc, char* argv[]) {
	Student s1;

	try {
		s1.setName("John");
		s1.setAge(9);
	}
	catch (string errorMsg)
	{
		cout << endl << "We got an error " << errorMsg;
	}
	catch (const char* errorMsg) {
		cout << endl << "We got another error **" << errorMsg;
	}
	catch (AgeException err) {
		cout << endl << "The age is wrong";
	}


	try {
		string name;
		cout << endl << "New name: ";
		cin >> name;
		s1.setName(name);

		cout << endl << "New name (upper): ";
		cin >> name;
		s1.setNameUpper(name);

		int age;
		cout << endl << "New age ";
		cin >> age;
		s1.setAge(age);

		int type;
		cout << endl << "New type (Bachelor - 0, Master - 1, PhD - 2)";
		cin >> type;
		s1.setType(type);

		//does not work on system exceptions
		//int* pointer = nullptr;
		//pointer[4] = 99;

		throw NewException();
	}

	catch (const char* err) {
		cout << endl << "Input value was wrong " << err;
		//how do you know the reason ??????
		if (strcmp(err, "The name is too short") == 0) {
			cout << endl << "The reason is the name";
		}
	}
	catch (AgeException err) {
		cout << endl << "Input value for age was wrong ";
	}
	catch (NameException err) {
		cout << endl << "Input value for name was wrong ";
		cout << endl << "Details: " << err.getDescription();
		cout << endl << "Error Code: " << err.getErrorCode();
	}
	catch (TypeException err) {
		cout << endl << "Input value for type was wrong ";
	}
	catch (...) {
		cout << endl << "A generic error";
	}


	cout << endl << "Getting only a correct value";
	while (true) {
		try {
			int age;
			cout << endl << "New age ";
			cin >> age;
			s1.setAge(age);
			break;
		}
		catch (AgeException err) {
			cout << endl << "Age was wrong. Give me another value";
		}
	}

	// FILE Section
	//from C in stdio.h
	//FILE* pf;
	//pf = fopen("Students.txt", "r");
	//fwrite()
	//fread()

	//in C++
	//we use the fstream library
	//for writing
	ofstream report("StudentsReport.txt",ios::out | ios::trunc ) ;
	//ofstream backup("Students.bck",ios::out | ios::app | ios::binary) ;

	if (report.is_open()) {
		int noStudents = 5;
		report << endl << "The list of all students:";
		report << endl << "The number of students is " << noStudents;
		report << endl << "John, age 23, Bachelor CSIE";
		report << endl << "Alice, age 23, Bachelor CSIE";
		report.close();
	}
	else {
		cout << endl << "We can't open the file";
	}

	//for reading
	ifstream inputReport;
	inputReport.open("StudentsReport.txt", ios::in);
	if (inputReport.is_open()) {
		string tempLine;
		//inputReport >> tempLine;		//it STOPS on 1st space
		char buffer[1000];
		inputReport.getline(buffer, 1000);
		tempLine = string(buffer);
		//const char* content = tempLine.c_str();

		cout << endl << "A line from the text file " << tempLine;

		inputReport.getline(buffer, 1000);
		tempLine = string(buffer);
		cout << endl << "A line from the text file " << tempLine;
	}
	else {
		cout << endl << "We can't open the file";
	}


	cout << endl << "The end of the app";
}