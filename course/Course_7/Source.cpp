#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class LenghtException {

};

class Student {
	int id = 0;
	char* name = nullptr;
	float tuitionFee = 0;

	const static int MIN_LENGTH = 3;
	static float feesTotal;
public:
	Student(int id, const char* name, float fee) {
		this->id = id;
		this->setName(name);
		this->tuitionFee = fee;
		Student::feesTotal += fee;
	}

	//Student(int id = 0, const char* name = "John Doe", float fee = 0) {
	//	this->id = id;
	//	this->setName(name);
	//	this->tuitionFee = fee;
	//	Student::feesTotal += fee;
	//}

	void setName(const char* newName) {

		//validate input
		if (strlen(newName) < MIN_LENGTH) {
			throw LenghtException();
		}
		if (this->name != nullptr) {
			delete[] this->name;
		}
		this->name = new char[strlen(newName) + 1];
		strcpy(this->name, newName);
	}

	void setTuitionFee(int newValue) {
		Student::feesTotal -= this->tuitionFee;
		this->tuitionFee = newValue;
		Student::feesTotal += newValue;
	}

	~Student() {
		if (this->name) {
			delete[] this->name;
		}
		//this->feesTotal  -= this->tuitionFee;
		Student::feesTotal -= this->tuitionFee;
	}

	//copy constructor
	Student(Student& student) {
		cout << endl << "Calling copy ctor";
		this->id = student.id;
		//this->tuitionFee = student.tuitionFee;
		//Student::feesTotal += this->tuitionFee;
		this->setTuitionFee(student.tuitionFee);
		this->setName(student.name);
	}

	static float getTotalFees() {
		cout << endl << "A static method";
		return Student::feesTotal;
	}
};

float Student::feesTotal = 0;

//is calling the copy constructor
void doNothing(Student s) {
	s.setName("Joker");
}

void doNothing2(const Student& s) {
	//s.setName("Joker");
}

//calls copy constructor
Student createObject() {
	Student s(0, "John Doe", 0);
	return s;
}


int main(int argc, char* argv[]) {
	//Student s1;
	//Student students[10];

	Student s1(1, "Johny", 1000);
	Student* pS = new Student(2, "Alice", 0);

	//Student s3(3);
	//Student s4(3,"Boby");

	delete pS;

	//copy constructor
	Student s2 = s1;

	cout << endl << "The sum of tuition fees is  " << Student::getTotalFees();

	doNothing(s1);
	createObject();
}