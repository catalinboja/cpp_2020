
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
	string name;
	int age;

	int grades[50];
	int noGrades;

	string bachelorProgram;
	string groupeName;


	Student(string name, int age) : name(name), age(age) {

	}

	Student() {

	}

	void print() {
		//printing a Student;
		cout << endl << "Print from Student";
	}


protected:
	int extra;
	void doNothing() {

	}
private:
	void onlyForStudent() {

	}

public:
	//1000+ functions that process Student data
};

class Employee {
protected:
	string position;
	string name;
	float salary;
};

class Intern : public Employee, public Student {
	string company;

public:
	void changeName() {
		this->Employee::name = "New name";
		this->Student::name = "Student name";
	}
};



class MasterStudent: public Student {

public:
	string bachelorDegree = "";
	string masterProgram = "";

	void playWithProtectedAttr() {
		this->extra = 25;
		this->doNothing();
	}

	void tryToCallPrivateStuff() {
		//this->onlyForStudent();
	}

	MasterStudent():Student() {
	}

	MasterStudent(string name, int age, string masterProgram)
		:Student(name, age), masterProgram(masterProgram) {
		this->masterProgram = masterProgram;
	}

	//we can change the implementation of inherited functions
	//overriding the Student version
	void print() {
		//print from a Master student perspective;
		cout << endl << "Print from Master";
	}

};

int main() {
	//Student student;

	//student.extra = 23;;

	MasterStudent master;
	master.age = 23;
	//master.extra = 23;

	cout << endl << "Student " << sizeof(Student);
	cout << endl << "Master Student " << sizeof(MasterStudent);


	Intern intern;

	intern.print();
	master.print();
}