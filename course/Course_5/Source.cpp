#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;


class ExceptionFacultyName {
	int errorCode = 0;
};

class ExceptionGroupNumber {
	int errorCode = 0;
};

class ExceptionGradeValue {
	int errorCode = 0;
};


//encapsulation
class Student{
	unsigned int id = 0;
	char* name = nullptr;
	int groupNumber = 0;
	char faculty[100] = { "CSIE" };
	int* grades = nullptr;
	int noGrades = 0;
	string address = "";

	// a static variable is not include in the object memory area
	static const int maxSizeFaculty = 99;
	static const int MIN_GRADE = 1;
	static const int MAX_GRADE = 10;

//the class public interface
public:
	//accessor methods - for reading
	unsigned int getId() {
		return this->id;
	}

	char* getName() {
		return this->name;
	}

	char* getFaculty() {
		return this->faculty;
	}

	int getGroup() {
		return this->groupNumber;
	}

	int getNoGrades() {
		return this->noGrades;
	}

	int* getGrades() {
		return this->grades;
	}

	//for writing
	void setFaculty(char* newFaculty) {
		//this->faculty = newFaculty;

		//without /0
		if (strlen(newFaculty) <= maxSizeFaculty) {
			strcpy_s(this->faculty, this->maxSizeFaculty + 1, newFaculty);
		}
		else {
			//throw "error";
			ExceptionFacultyName exception;
			throw exception;

			//or
			//throw ExceptionFacultyName();
		}
	}

	void setGroupNumber(int groupNumber) {
		//shadowing 
		//groupNumber = groupNumber;

		if (groupNumber > 0 && groupNumber < 9999) {

			this->groupNumber = groupNumber;
		}
		else {
			ExceptionGroupNumber error;
			//throw "wrong number";
			throw error;
		}
	}

	//changes the grade at the given index
	void setGrade(int newGrade, int index) {
		if (newGrade < MIN_GRADE || newGrade > MAX_GRADE) {
			throw ExceptionGradeValue();
		}

		if (index > (this->noGrades - 1) || index < 0) {
			throw ExceptionGradeValue();
		}

		this->grades[index] = newGrade;
	}

	//constructor methods
	//create an object
	//default constructor
	//Student() {

	//}

	Student() {
		this->id = 90;
		this->groupNumber = 200;
		strcpy(this->faculty, "MAN");
		//init all your arguments
	}

	//ctor with arguments
	Student(char* faculty, int groupNo, int id) {
		this->id = id;
		//this->groupNumber = groupNo;
		this->setGroupNumber(groupNo);
		strcpy(this->faculty, faculty);


	}
};

int main(int argc, char* argv[]) {
	Student student;
	student.getId();

	//this is on the stack - the pointer must be constant
	const char* faculty_0 = "CSIE";

	//the next ones are in HEAP
	//create the space in Heap
	char* faculty = new char[strlen("CSIE") + 1];
	//copy the value
	strcpy(faculty, "CSIE");

	//the alternative
	char* faculty_2 = new char[] {"CSIE"};

	student.setFaculty(faculty);

	string name;
	name = "John";
	name = name + " and Alice";
	string newName = name;
	cout << endl << "the name is " << name;

	//change group number
	student.setGroupNumber(1064);
	cout << endl << " The  group number is " << student.getGroup();

	//student.setGroupNumber(-23);

	//what was the reason for the error ?

	//using the default ctor
	Student student2;
	Student student4;
	cout << endl << "Student 2 faculty is " << student2.getFaculty();
	cout << endl << "Student 2 group is " << student2.getGroup();

	//using the ctor with arguments
	Student student3(faculty_2, 1066, 2);
	cout << endl << "Student 3 faculty is " << student3.getFaculty();
	cout << endl << "Student 3 group is " << student3.getGroup();
	cout << endl << "Student 3 id is " << student3.getId();

}