#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Student {
	string name = "";
	int age = 0;
	char faculty[100];
	char* email = nullptr;
	int* grades = nullptr;
	int noGrades = 0;
public:
	Student() {

	}
	Student(string name, int age, const char* faculty, const char* email):age(age) {
		this->name = name;
		//this->age = age;
		strcpy(this->faculty, faculty);
		this->setEmail(email);
	}

	Student(const Student& stud) {
		this->name = stud.name;
		this->age = stud.age;
		strcpy(this->faculty, stud.faculty);
		this->setEmail(stud.email);
		this->setGrades(stud.grades, stud.noGrades);
	}

	//TO DO
	//~Student();

	void operator=(Student& stud) {
		if (this != &stud) {
			this->name = stud.name;
			this->age = stud.age;
			strcpy(this->faculty, stud.faculty);
			this->setEmail(stud.email);
			this->setGrades(stud.grades, stud.noGrades);
		}
	}

	void printInfo(ostream& console) {
		console << endl << "------------------";
		console << endl << "Name: " << this->name;
		console << endl << "Age: " << this->age;
		console << endl << "Faculty: " << this->faculty;
		console << endl << "Email: " << (this->email != nullptr ? this->email : "no email");
		if (this->grades) {
			console << endl << "Grades: ";
			for (int i = 0; i < this->noGrades; i++) {
				console << this->grades[i] << " ";
			}
		}
	}

	void writeObjectToFile(ofstream& file) {
		int size;
		size = this->name.size();
		//writing the name size
		file.write((char*)&size, sizeof(int));
		//write the name
		file.write(this->name.c_str(), size);

		//write age
		file.write((char*)&this->age, sizeof(int));

		//write the faculty
		//we write the entire static array - we don't need the size anymore
		file.write(this->faculty, sizeof(this->faculty));

		//write email
		size = strlen(this->email);
		file.write((char*)&size, sizeof(int));
		file.write(this->email, size);

		//write the number of grades
		file.write((char*)&this->noGrades, sizeof(int));
		//write the grades
		for (int i = 0; i < this->noGrades; i++) {
			file.write((char*)&this->grades[i], sizeof(int));
		}
	}

	void readObjectFromFile(ifstream& file) {

		char buffer[100];

		int size;
		//read the name size
		file.read((char*)&size, sizeof(int));
		//read the name - we don't have the \0 in the file
		file.read(buffer, size);
		buffer[size] = '\0';
		string name = string(buffer);

		this->name = name;

		//read age
		int age;
		file.read((char*)&age, sizeof(int));
		this->age = age;

		//read the faculty
		//we read the entire static array - we don't need the size anymore
		file.read(this->faculty, sizeof(this->faculty));

		//read email
		file.read((char*)&size, sizeof(int));
		if (this->email) {
			delete[] this->email;
		}
		this->email = new char[size + 1];
		file.read(this->email, size);
		//we don't have the '\0'
		this->email[size] = '\0';

		//write the number of grades
		file.read((char*)&this->noGrades, sizeof(int));
		if (this->grades) {
			delete[] this->grades;
		}
		this->grades = new int[this->noGrades];
		//read the grades
		for (int i = 0; i < this->noGrades; i++) {
			file.read((char*)&this->grades[i], sizeof(int));
		}
	}

	void setEmail(const char* email);
	void setGrades(int* grades, int noGrades);

};