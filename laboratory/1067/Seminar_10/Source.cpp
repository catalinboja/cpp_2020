#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Grade {
	int value = 0;
	string courseName = "";
public:
	Grade(int grade, string course):value(grade), courseName(course) {

	}
	Grade() {

	}

	friend void operator<<(ostream& console, Grade& grade);
};

class GradeBook {
	Grade grades[100];
	int noCourses = 0;

public:
	void addGrade(Grade grade) {
		if (this->noCourses < 100) {
			this->grades[this->noCourses] = grade;	//operator = from Grade
			this->noCourses += 1;
		}
	}

	friend void operator<<(ostream& console, GradeBook& gradeBook);
};

class Group {
	int groupNo = 0;
	string faculty = "";
	string address = "";
public:
	Group(int group, string faculty, string address) {
		this->groupNo = group;
		this->faculty = faculty;
		this->address = address;
	}

	friend void operator<<(ostream& console, Group& group);
};

//Student has a "has-a" relation with Group and GradeBook
class Student {
	string name = "";
	int age = 0;
	Group group = Group(1001,"CSIE","Bucharest");
	GradeBook gradeBook;
public:
	Student():group(1000,"CSIE","Bucharest"), age(0), name("John Doe"), gradeBook() {
		this->age = 0;
	}

	Student(string name, int age, Group receivedGroup):group(receivedGroup), name(name) {
		this->age = age;
	}

	Student(string name, int age, int groupNo, string faculty, string address)
		:group(groupNo, faculty, address)
	{
		this->name = name;
		this->age = age;
	}

	void takeExam(Grade grade) {
		this->gradeBook.addGrade(grade);
	}

	static void loadStudentsFromFile(string fileName, Student* & students, 
		int & noStudents ) {

		ifstream file(fileName, ios::in);
		if (file.is_open()) {

			//read the number of students
			file >> noStudents;

			if (students) {
				delete[] students;
			}
			students = new Student[noStudents];
			int index = 0;

			//move the cursor to the next line for getline
			string temp;
			getline(file, temp);

			while (!file.eof()) {

				char buffer[100];

				string name;
				getline(file, name);

				int age;
				file.getline(buffer, 100);
				age = atoi(buffer);

				int groupNo;
				file.getline(buffer, 100);
				groupNo = atoi(buffer);
				string faculty;
				getline(file, faculty);
				string adress;
				getline(file, adress);

				Group group(groupNo, faculty, adress);
				Student student(name, age, group);

				int noGrades;
				file.getline(buffer, 100);
				noGrades = atoi(buffer);

				for (int i = 0; i < noGrades; i++) {
					int gradeValue;
					file.getline(buffer, 100);
					gradeValue = atoi(buffer);

					string course;
					getline(file, course);

					Grade grade(gradeValue, course);
					student.takeExam(grade);
				}

				students[index] = student;
				index += 1;
			}
			file.close();
		}
		else {
			cout << endl << "***************** The file is not opened";
		}

	}

	friend void operator<<(ostream& console, Student& student);
};

void operator<<(ostream& console, Grade& grade) {
	console << endl << "The grade for " << grade.courseName << " is  " << grade.value;
}

void operator<<(ostream& console, GradeBook& gradeBook) {
	console << endl << "Student grades: ";
	for (int i = 0; i < gradeBook.noCourses; i++) {
		console << gradeBook.grades[i];
	}
}

void operator<<(ostream& console, Group& group) {
	console << endl << "Group number: " << group.groupNo;
	console << endl << "Faculty: " << group.faculty;
	console << endl << "Office address: " << group.address;
}

void operator<<(ostream& console, Student& student) {
	console << endl << "----------------------------------------";
	console << endl << "Student name: " << student.name;
	console << endl << "Student age: " << student.age;
	console << student.group;
	console << student.gradeBook;
}

class StudentsList {
	Student* students = nullptr;
	int noStudents = 0;
};

int main(int argc, char* argv[]) {

	Group g1067(1067, "CSIE", "Calea Dorobanti 15-17");

	Student student1;
	Student student2("Alice", 20, g1067);

	Grade oopGrade(9, "OOP in C++");
	Grade accGrade(10, "Accounting");

	student2.takeExam(oopGrade);
	student2.takeExam(accGrade);

	cout << student1;
	cout << student2;

	Student* students = nullptr;
	int noStudents = 0;

	Student::loadStudentsFromFile("Students.txt", students, noStudents);

	for (int i = 0; i < noStudents; i ++ ) {
		cout << students[i];
	}
}