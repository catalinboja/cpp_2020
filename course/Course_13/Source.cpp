//Evaluation
//1st DO - don't it
//2nd DO - keep doing it
//3rd DO - you should do it

#include <iostream>
#include <string>
using namespace std;


class Person {
protected:
	string name = "";
public:
	Person(string Name, string msg, string dbName): name(Name) {
		cout << endl << msg;
		cout << endl << "Connecting to the database " << dbName;
	}

	Person(string Name) : name(Name) {
		this->name = Name;
	}

	Person() {

	}

	virtual void getDescription() {
		cout << endl << "The person name is " << this->name;
	}
};

class Student: public Person {
protected:
	string faculty = "CSIE";
public:
	Student(): Person("John Doe") {

	}

	Student(string Name, string Faculty): Person(Name), faculty(Faculty) {

	}

	void getStudentDescription() {
		cout << endl << "The student name is " << this->name;
		cout << endl << "The student faculty is " << this->faculty;

	}

	void getDescription() {
		this->Person::getDescription();
		cout << endl << "The student faculty is " << this->faculty;
	}

};

class MasterStudent : public Student {
	float bachelorExamGrade = 6;
public:
	void getDescription() {
		this->Person::getDescription();
		cout << endl << "The student faculty is " << this->faculty;
		cout << endl << "The exam grade is " << this->bachelorExamGrade;
	}

	void doSomething() {

	}
};

int main() {
	Person person("Alice");
	Student student;
	MasterStudent master;

	person.getDescription();
	student.getDescription();

	Person persons[5];
	Student students[5];
	MasterStudent masterStudents[5];

	Person everything[5];
	//master = person;		//DOWN-CASTING - doesn't work by default

	//person = master;  //UP-CASTING - works by default at object level and pointer level

	everything[0] = person;
	everything[1] = student;
	everything[2] = master;

	for (int i = 0; i < 3; i++) {
		everything[i].getDescription();
	}

	Person* all[5];
	all[0] = &person;
	all[1] = &student;
	all[2] = &master;

	for (int i = 0; i < 3; i++) {
		all[i]->getDescription();		//early binding - decision at compile time
	}

	//all[i]->_vtptr[0];				//late binding - processor decides which function to call based on the address in the vtptr

	//MasterStudent* pMaster;
	//pMaster = &person;		//DOWN CAST - not working

	//we know this
	MasterStudent* pMaster = (MasterStudent*)all[2];
	pMaster->doSomething();


 
	//student.getStudentDescription();
}