#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Group {
	int group = 0;
	string faculty = "";
	string address = "";
public:
	Group(int group, string faculty, string address) {
		this->group = group;
		this->faculty = faculty;
		this->address = address;
	}

	friend void operator<<(ostream& console, Group& group);
};

class Grade {
	int value = 0;
	string courseName = "";
public:
	Grade(int grade, string course) {
		this->value = grade;
		this->courseName = course;
	}
	Grade() {

	}

	friend void operator<<(ostream& console, Grade& grade);
};

class GradeBook {
	Grade grades[100];
	int noGrades = 0;
public:
	//only for test purpose
	GradeBook(string something) {

	}

	GradeBook() {

	}

	void addGrade(Grade grade) {
		if (this->noGrades < 100) {
			this->grades[this->noGrades] = grade;	//operator = from Grade
			this->noGrades += 1;
		}
	}

	friend void operator<<(ostream& console, GradeBook& gradeBook);
};

class Student {
	string name = "";
	int age = 0;
	Group group;
	GradeBook gradeBook;

	//int grades[100];
	//int noGrades;
	//string courses[100];
	//char* courses[100];
public:
	Student():group(0,"CSIE","Bucharest"), gradeBook("Test"), age(0) {

	}
	Student(string name, int age, Group receivedGroup):group(receivedGroup) {
		this->name = name;
		this->age = age;
	}

	void takeExam(Grade grade) {
		this->gradeBook.addGrade(grade);
	}

	static void loadStudents(string fileName, Student*& students, int& noStudents) {
		ifstream inputFile(fileName, ios::in);
		if (inputFile.is_open()) {
			//read the number of students
			inputFile >> noStudents;
			if (students != nullptr) {
				delete[] students;
			}
			students = new Student[noStudents];

			int counter = 0;

			//we simulate a getline to move the cursor to the next line
			//it's on the first line because of  >>
			string temp;
			getline(inputFile, temp);

			while (!inputFile.eof()) {

				char buffer[100];

				string name;
				getline(inputFile, name);
				int age;
				inputFile.getline(buffer, 100);
				age = atoi(buffer);

				int groupNo;
				inputFile.getline(buffer, 100);
				groupNo = atoi(buffer);

				string faculty;
				getline(inputFile, faculty);
				string address;
				getline(inputFile, address);

				//create the new student
				Group group(groupNo, faculty, address);
				Student student(name, age, group);

				int noGrades;
				inputFile.getline(buffer, 100);
				noGrades = atoi(buffer);

				for (int i = 0; i < noGrades; i++) {
					int gradeValue;
					string courseName;

					inputFile.getline(buffer, 100);
					gradeValue = atoi(buffer);
					getline(inputFile, courseName);

					Grade grade(gradeValue, courseName);

					student.takeExam(grade);
				}

				students[counter] = student;
				counter += 1;
			}

			inputFile.close();
		}
		else
		{
			cout << endl << "**************** File not opened";
		}
	}

	friend void operator<<(ostream& console, Student& student);
};

void operator<<(ostream& console, Group& group) {
	console << endl << group.group << " - " << group.faculty << " from " << group.address;
}

void operator<<(ostream& console, Grade& grade) {
	console << endl << "The grade for " << grade.courseName << " is " << grade.value;
}

void operator<<(ostream& console, GradeBook& gradeBook) {
	console << endl << "Student grades: ";
	for (int i = 0; i < gradeBook.noGrades; i++) {
		console << gradeBook.grades[i];
	}
}

void operator<<(ostream& console, Student& student) {
	console << endl << "-----------------------------------";
	console << endl << "Student name: " << student.name;
	console << endl << "Student age: " << student.age;
	console << student.group;
	console << student.gradeBook;
}

int main(int argc, char* argv[]) {
	Group g1066(1066, "CSIE", "Calea Dorobanti 15");
	Student student1;
	Student student2("John", 20, g1066);

	Grade grade1(10, "OOP");
	Grade grade2(9, "Accounting");

	student2.takeExam(grade1);
	student2.takeExam(grade2);

	cout << student1;
	cout << student2;

	Student* students = nullptr;
	int noStudents;

	Student::loadStudents("Students.txt", students, noStudents);

	cout << endl << "Student data from file -----------------------";
	for (int i = 0; i < noStudents; i++) {
		cout << students[i];
	}

}