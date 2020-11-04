#include <iostream>
#include <string>
using namespace std;

class Student {
	string name = "John Doe";
	int* grades = nullptr;
	int noGrades = 0;
public:
	//default constructor
	//create the object - needed space and initial attributes with default value
	//Student() {
	//	cout << endl << "The default ctor";
	//}

	//contructor with arguments
	Student(string name) {
		this->setName(name);

		//if you didn't init them at the definition you should do it now
		this->grades = nullptr;
		this->noGrades = 0;
	}

	Student(string name, int* grades, int noGrades) {
		this->setName(name);
		this->setGrades(grades, noGrades);
	}

	//the destructor
	~Student() {
		cout << endl << "The class destructor";
		//release the space created in HEAP
		if (this->grades != nullptr) {
			delete[] this->grades;
		}
	}

	void setName(string newName) {
		//sorry without validations
		this->name = newName;
	}

	void setGrades(int*grades, int no) {
		this->noGrades = no;

		//it's a mistake
		//this->grades = grades;	//shallow-copy

		//deep-copy

		//avoid the memory leak
		if (this->grades != nullptr) {
			delete[] this->grades;
		}

		this->grades = new int[no];
		for (int i = 0; i < no; i++) {
			this->grades[i] = grades[i];
		}
	}

	void printStudent() {
		cout << endl << "---------------------------";
		cout << endl << "Name: " << this->name;
		cout << endl << "Grades: ";
		for (int i = 0; i < this->noGrades; i++) {
			cout << " " << this->grades[i];
		}
	}

	void failExam(int index) {
		if (index >= 0 && index < this->noGrades) {
			this->grades[index] = 4;
		}
		else {
			throw "Wrong inedx";
		}
	}

};

void someFunction() {
	int someGrades[3] = { 10,10,9 };
	int noGrades = 3;
	Student student4("Bob", someGrades, noGrades);
}

int main(int argc, char* argv[]) {

	//without default constructor you can't do this
	//Student student1;			//on the main() stack
	//Student student2;			//on the main() stack

	//TO DO init the objects

	int someGrades[3] = { 10,10,9 };
	int noGrades = 3;

	//student1.setName("Alice");
	//student1.setGrades(someGrades, noGrades);
	//student1.printStudent();

	//call another function
	someFunction();

	//use the other constructors
	Student student3("John");
	Student student4("Bob", someGrades, noGrades);
	Student student5("Vader", someGrades, noGrades);

	student3.printStudent();
	student4.printStudent();
	student5.printStudent();

	student5.failExam(0);
	student5.printStudent();
	student4.printStudent();

	//for (;;) {
		//int otherGrades[3] = { 8,8,9 };
		//int noGrades = 3;
		//student4.setGrades(otherGrades, noGrades);
	//}

	cout << endl << "Cloning Bob";

	//The Copy Constructor
	Student BobsClone = student4;

	BobsClone.printStudent();

	//for (;;) {
	//	Student* temp = new Student("John", someGrades, noGrades);
	//	delete temp;
	//}

	//Student* pStudent = new Student();		//in HEAP

	////array of objects
	//Student group[30];			//on the main() stack
	//Student* pGroup = new Student[30];		//in HEAP

	////delete
	//delete[] pGroup;
	//delete pStudent;
}