#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct Student {
	unsigned short int age;
	char gender;
	bool isMinority;
	char name[100];
};

class SuperStudent {
//you always get a default private: here
//access specifiers: private, public ........protected

	unsigned short int age;
	char gender;
	bool isMinority;

public:
	char name[100];
	void printStudent() {
		cout << endl << "----------------------------------";
		cout << endl << "Age = " << this->age;
		cout << endl << "Gender = " << this->gender;
		cout << endl << "Is minority = " << (this->isMinority ? "yes" : "no");
		cout << endl << "Name = " << this->name;
	}

	//accessor methods
	// this - SuperStudent *
	void setAge(int newAge) {
		if (newAge >= 14) {
			this->age = newAge;
		}
		else
		{
			//cout << endl << "The value is not ok";
			throw "The value is wrong";
		}
	}

	int getAge() {
		return this->age;
	}
};

void printStudent(Student stud) {
	cout << endl << "Age = " << stud.age;
	cout << endl << "Gender = " << stud.gender;
	//if (stud.isMinority) {
	//	cout << endl << "Is minority = " << "yes";
	//}
	//else
	//{
	//	cout << endl << "Is minority = " << "no";
	//}

	cout << endl << "Is minority = " << (stud.isMinority ? "yes" : "no");
	cout << endl << "Name = " << stud.name;
}

int main(int ragc, char* argv[]) {

	Student student;	//article
	student.age = 23;
	student.gender = 'M';
	student.isMinority = false;
	strcpy(student.name, "John");

	Student* pStudent = &student;
	pStudent->age = 24;

	/*
	
	1000 lines of code

	*/
	student.age = 99;

	Student students[100];
	int noStudents;

	printStudent(student);

	//class perspective
	SuperStudent superStudent;		//object
	SuperStudent superSuperStudent;		//object

	//are private
	//superStudent.age = 25;
	//superStudent.isMinority = true;



	//are public
	strcpy(superStudent.name, "Alice");
	//superStudent.setAge(superStudent, 0);	//will generate a runtime exception because of throw
	
	superStudent.setAge(23);
	superSuperStudent.setAge(34);

	int age = superStudent.getAge();

	superStudent.printStudent();

	superSuperStudent.printStudent();

}