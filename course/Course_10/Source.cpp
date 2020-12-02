#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Grade {
public:
	int value = 0;
	string courseName = "";

	Grade(int Value, string Course) {
		this->value = Value;
		this->courseName = Course;
	}


	Grade() {

	}
};

class Faculty {
public:
	string address = "";
	char name[100] = "";

	Faculty(string Addr, const char* Name) {
		this->address = Addr;
		//this->name = Name;
		strcpy_s(this->name, sizeof(name), Name);
		this->name[sizeof(name) - 1] = '\0';
	}

	Faculty() {

	}
//
//	friend class Student;
};


//the relation between Student and Faculty/Grade is a "has a" relation
class Student {

	string name = "";
	int age = 0;

	Faculty faculty;

	Grade* grades = nullptr;			//pointer to a grade or multiple grades
	//Grade grades[20];
	int noGrades = 0;

	//char faculty[100];
	//char address[100];
	//int* grades;
	//int noGrades;
	//char** courseNames;
	//string* courseNames;

public:
	//calling the Faculty ctor for the faculty attr
	Student(string name, int age):faculty("CSIE","Calea Dorobanti 15-17") {
		this->name = name;
		this->age = age;
	}

	//the compiler calls by default the default ctor from Faculty for faculty attr
	Student(string name, int age, Grade* grades, int noGrades) {
		this->name = name;
		this->age = age;
		this->setGrades(grades, noGrades);
	}

	Student(string name, int age, Grade* grades, int noGrades, Faculty faculty) {
		this->name = name;
		this->age = age;
		this->setGrades(grades, noGrades);
		this->faculty = faculty;		//using opertor = from Faculty
	}

	void setGrades(Grade* grades, int noGrades) {
		if (grades) {
			if (this->grades)
				delete[] this->grades;
			this->grades = new Grade[noGrades];
			for (int i = 0; i < noGrades; i++) {
				this->grades[i] = grades[i];
			}
			this->noGrades = noGrades;
		}
	}

	Student(const Student& s) {
		this->name = s.name;
		this->age = s.age;
		this->faculty = s.faculty;
		this->setGrades(s.grades, s.noGrades);
	}

	~Student() {
		if (this->grades)
			delete[] this->grades;
	}

	void operator=(const Student& s) {
		if (this != &s) {
			this->name = s.name;
			this->age = s.age;
			this->faculty = s.faculty;
			this->setGrades(s.grades, s.noGrades);
		}
	}

	friend void operator<<(ostream& console, Student& student);
	friend void operator<<(ofstream& file, Student& student);
};

void operator<<(ostream& console, Grade& grade) {
	console << endl << " Grade for " << grade.courseName << " is " << grade.value;
}

void operator<<(ostream& console, Faculty& faculty) {
	console << endl << " Faculty " << faculty.name << "( " << faculty.address << " )";
}

void operator<<(ostream& console, Student& student) {
	console << endl << " Name " << student.name << " has the age  " << student.age;
	console << endl << student.faculty;
	if (student.noGrades > 0) {
		for (int i = 0; i < student.noGrades; i++) {
			console << student.grades[i];
		}
	}
}


void operator<<(ofstream& file, Student& student) {
	file << endl << " Name " << student.name;
	file << endl << " Age " << student.age;
	file << endl << student.faculty;
	if (student.noGrades > 0) {
		file << endl << " Grades: ";
		for (int i = 0; i < student.noGrades; i++) {
			file << student.grades[i];
		}
	}
}


int main(int argc, char* argv[]) {
	Grade grades[3];
	grades[0] = Grade(9, "OOP");
	grades[1] = Grade(10, "C#");
	grades[2] = Grade(10, "Java");
	Faculty csie("CSIE", "Bucharest");
	Student student1("John", 21, grades, 3, csie);
	cout << student1;

	ofstream report("Students.txt", ios::out | ios::trunc);
	if (report.is_open()) {
		report << student1;
		report.close();
	}
}
