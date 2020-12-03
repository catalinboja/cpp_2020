#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Grade {
	int value;
	string course;
public:
	Grade(int value, string course) {
		this->value = value;
		this->course = course;
	}

	Grade() {
		this->value = 0;
		this->course = "";
	}

	friend void operator<<(ostream& console, Grade& grade);
};

class Faculty {
	string name;
	string address;
public:
	Faculty(string name, string address) {
		this->name = name;
		this->address = address;
	}

	friend void operator<<(ostream& console, Faculty& faculty);
};

class Student {
	string name= "";
	int group = 0;
	Grade grades[100];
	int noGrades = 0;
	Faculty faculty;
public:
	Student():faculty("CSIE","Calea Dorobanti") {
		this->name = "John Doe";
		this->group = 0;
		this->noGrades = 0;
	}

	Student(string Name, int Group, Faculty studentFaculty):faculty(studentFaculty) {
		this->name = Name;
		this->group = Group;
		this->noGrades = 0;
	}

	static void readStudentsData(string fileName, Student* & students, int & noStudents) {
		ifstream file(fileName, ios::in);
		if (file.is_open()) {

			//the first line is the number of students
			file >> noStudents;
			if (students) {
				delete[] students;
			}
			students = new Student[noStudents];

			//for (int i = 0; i < noStudents; i++) {

			//}


			char bufferTemp[10];
			//do an empty read to move the cursor on the next line
			//>> left the file cursor on the first line before \n
			file.getline(bufferTemp, 10);

			int counter = 0;
			while (!file.eof()) {
				string name;
				int group;
				char buffer[100];

				file.getline(buffer, 100);
				name = string(buffer);
				file.getline(buffer, 100);
				group = atoi(buffer);

				//store them in the current Student
				students[counter].name = name;
				students[counter].group = group;

				int noGrades;
				//file >> noGrades;
				file.getline(buffer, 100);
				noGrades = atoi(buffer);

				students[counter].noGrades = noGrades;

				//reading the grades data
				for (int i = 0; i < noGrades; i++) {
					string courseName;
					int gradeValue;
					file.getline(buffer, 100);
					gradeValue = atoi(buffer);
					file.getline(buffer, 100);
					courseName = string(buffer);

					Grade grade(gradeValue, courseName);
					students[counter].grades[i] = grade;
				}

				//read the faculty name and the address
				string faculty;
				string address;
				file.getline(buffer, 100);
				faculty = string(buffer);
				file.getline(buffer, 100);
				address = string(buffer);

				Faculty studentFaculty(faculty, address);
				students[counter].faculty = studentFaculty;

				counter += 1;
			}

			file.close();
		}
		else
		{
			cout << endl << "******************* File not opened";
		}
	}

	friend void operator<<(ostream& console, Student& student);
};

void operator<<(ostream& console, Grade& grade) {
	console << endl << "Grade for " << grade.course << " is " << grade.value;
}

void operator<<(ostream& console, Faculty& faculty) {
	console << endl << faculty.name << " - " << faculty.address;
}

void operator<<(ostream& console, Student& student) {
	console << endl << "Name " << student.name;
	console << endl << "Group " << student.group;
	console << student.faculty;
	console << endl << "Grades: ";
	for (int i = 0; i < student.noGrades; i++) {
		console << student.grades[i];
	}
}

class StudentGroup {
	Student* students = nullptr;
	int noStudents = 0;
};

void changeNumber(int value) {
	value = 100;
}

void changeNumber2(int* addr) {
	*addr = 100;
}

void changeNumber3(int& addr) {
	addr = 100;
}

void changeArray(int* pointer) {
	pointer = new int[99];
}

void changeArray2(int** pointerToPointer) {
	*pointerToPointer = new int[99];
}

void changeArray3(int*& referenceToPointer) {
	referenceToPointer = new int[99];
}


int main(int argc, char* argv[]) {
	Faculty csie("CSIE", "Bucharest");
	Student student1;
	Student student2("Alice", 1065, csie);
	cout << student1;
	cout << student2;

	Student* students = nullptr;
	int noStudents = 0;

	//int vb = 10;
	//changeNumber(vb);
	////vb - > 10
	//changeNumber2(&vb);
	//changeNumber3(vb);
	//int* someValues = nullptr;
	//someValues = new int[10];

	//changeArray(someValues);
	//changeArray2(&someValues);
	//changeArray3(someValues);

	Student::readStudentsData("Students.txt", students, noStudents);
	cout << endl << "Number of students: " << noStudents;
	for (int i = 0; i < noStudents; i++) {
		cout << endl << students[i];
	}

}