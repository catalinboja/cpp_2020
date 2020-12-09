#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Group {
	int groupNo = 0;
	string faculty = "";
	string secretaryEmail = "";
public:
	Group(int groupNo, string faculty, string email) {
		this->groupNo = groupNo;
		this->faculty = faculty;
		this->secretaryEmail = email;
	}

	friend void operator<<(ostream& console, Group& group);
};

class Grade {
	int value = 0;
	string course = "";

public:
	Grade(int value, string course) {
		this->value = value;
		this->course = course;
	}

	Grade() {

	}

	friend void operator<<(ostream& console, Grade& grade);
};

class GradeBook {
	Grade grades[100];
	int noGrades = 0;
public:

	void addGrade(Grade grade) {
		if (noGrades < 100) {
			this->grades[this->noGrades] = grade;
			this->noGrades += 1;
		}
	}

	friend void operator<<(ostream& console, GradeBook gradeBook);
};

class PersonalInfo {
	string name = "";
	int age = 0;
};

class Student {
	//PersonalInfo info;
	string name = "";
	int age = 0;
	Group group; // = Group(1001, "CSIE", "csie@ase.ro");
	GradeBook gradeBook;
public:
	Student():group(1001,"CSIE","csie@ase.ro"), gradeBook(), name("Joe Doe") {
		this->age = 18;
	}

	Student(string name, int age, Group receivedGroup):group(receivedGroup) {
		this->name = name;
		this->age = age;
	}

	Student(string name, int age, int groupNo, string faculty, string email)
		: group(groupNo, faculty, email)
	{
		this->age = age;
		this->name = name;
	}

	void takeExam(Grade grade) {
		this->gradeBook.addGrade(grade);
	}

	void takeExam(int gradeValue, string course) {
		Grade grade(gradeValue, course);
		this->gradeBook.addGrade(grade);
	}

	static void loadStudentsData(string fileName, Student*& students, int & noStudents) {
		ifstream file(fileName, ios::in);
		if (file.is_open()) {
			if (students != nullptr) {
				delete[] students;
			}

			//read the students number
			file >> noStudents;

			students = new Student[noStudents];

			//move the cursor on the next line - because of >>
			string temp;
			getline(file, temp); //read \n and moves the cursor on the next line

			int counter = 0;

			while (!file.eof()) {

				char buffer[100];

				//read the name
				string name;
				getline(file, name);
				//read age
				int age;
				file.getline(buffer, 100);
				age = atoi(buffer);

				int groupNo;
				file.getline(buffer, 100);
				groupNo = atoi(buffer);

				string faculty;
				getline(file, faculty);

				string email;
				getline(file, email);

				Group group(groupNo, faculty, email);
				Student student(name, age, group);

				int noGrades;
				file.getline(buffer, 100);
				noGrades = atoi(buffer);

				for (int i = 0; i < noGrades; i++) {
					int gradeValue;
					file.getline(buffer, 100);
					gradeValue = atoi(buffer);

					string course;
					//getline(file, course);
					file.getline(buffer, 100);
					course = string(buffer);

					Grade grade(gradeValue, course);
					student.takeExam(grade);
				}

				students[counter] = student;
				counter += 1;
			}

			file.close();
		}
		else {
			cout << endl << "**************** File not opened";
		}
	}

	friend void operator<<(ostream& console, Student& student);
};

class StudentsList {
	Student* students;
	int noStudents;
};

void operator<<(ostream& console, Group& group) {
	console << endl << " Group number " << group.groupNo << " from " << group.faculty;
	console << endl << "Secretary office contact " << group.secretaryEmail;
}

void operator<<(ostream& console, Grade& grade) {
	console << endl << "Grade " << grade.value << " for  " << grade.course;
}

void operator<<(ostream& console, GradeBook gradeBook) {
	console << endl << "Student grades: ";
	for (int i = 0; i < gradeBook.noGrades; i++) {
		console << gradeBook.grades[i];
	}
}

void operator<<(ostream& console, Student& student) {
	console << endl << "--------------------------------";
	console << endl << "Student name " << student.name;
	console << endl << "Student age " << student.age;
	console << student.group;
	console << student.gradeBook;
}

int main(int argc, char* argv[]) {
	Student student1;
	//Group group;
	Student student2("Alice", 20, 1064, "CSIE", "csie@ase.ro");
	Group g1064(1064, "CSIE", "csie@ase.ro");
	Student student3("John", 20, g1064);

	student2.takeExam(10, "OOP");
	Grade gradeMath(9, "Algebra");
	student2.takeExam(gradeMath);

	cout << student1;
	cout << student2;
	cout << student3;

	//printing the data into a text file
	ofstream report("Report.txt", ios::out | ios::trunc);
	if (report.is_open()) {
		report << student1;
		report << student2;
		report << student3;
		report.close();
	}

	//reading data from the text file 
	Student* students = nullptr;
	int noStudents = 0;

	cout << endl << "****************";
	Student::loadStudentsData("Students.txt", students, noStudents);
	for (int i = 0; i < noStudents; i++) {
		cout << students[i];
	}

}