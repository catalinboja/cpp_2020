#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"

void Student::setEmail(const char* email) {
	if (email != nullptr) {
		if (this->email) {
			delete[] this->email;
		}
		this->email = new char[strlen(email) + 1];
		strcpy(this->email, email);
	}
}

void Student::setGrades(int* grades, int noGrades) {
	if (grades != nullptr) {
		if (this->grades) {
			delete[] this->grades;
		}
		this->grades = new int[noGrades];
		memcpy(this->grades, grades, noGrades * sizeof(int));
		this->noGrades = noGrades;
	}
}