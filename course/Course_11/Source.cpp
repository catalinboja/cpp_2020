#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>

#include "Student.h"

using namespace std;

int main(int argc, char* argv[]) {
	Student student1;
	Student student2("John", 20, "CSIE", "john@stud.ase.ro");

	student1.printInfo(cout);
	student2.printInfo(cout);

	ofstream report("Report.txt", ios::out | ios::trunc);	//ios::app for appending
	student2.printInfo(report);

	//binary files
	ofstream backup("Students.bin", ios::out | ios::trunc | ios::binary);
	if (backup.is_open()) {
		int aNumber = 1;
		string aWrongNumber = "100";
		//backup << aNumber;

		backup.write((char*)&aNumber, sizeof(int));
		//avoid writing entire objects
		//backup.write((char*)&aWrongNumber, sizeof(string));

		//we need to write the size of the string - we need it for reading
		int size = aWrongNumber.size();
		backup.write((char*)&size, sizeof(int));
		backup.write(aWrongNumber.c_str(), aWrongNumber.size() * sizeof(char));

		backup.close();
	}

	//reopen the file and write some Students
	backup.open("Students.bin", ios::out | ios::app | ios::binary);
	if (backup.is_open()) {

		//144 for me
		cout << endl << "Size of a Student " << sizeof(Student);
		
		
		//DON't - this is wrong
		//backup.write((char*)&student2, sizeof(Student));

		backup.close();
	}
	
	ifstream input("Students.bin", ios::in | ios::binary);
	if (input.is_open()) {
		//read the int
		int number;
		input.read((char*)&number, sizeof(int));

		//read the string size
		int size;
		input.read((char*)&size, sizeof(int));
		
		//read the string
		string text = "";
		char buffer[100];
		input.read(buffer, size * sizeof(char));

		//read the Student
		Student student;
		input.read((char*)&student, sizeof(Student));

		cout << endl << "-----------------";
		student.printInfo(cout);

		input.close();
	}
	else
		cout << endl << "No file to open";
}