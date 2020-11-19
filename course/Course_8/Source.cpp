#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class LenghtException {

};

class Student {
	const int id;
	char* name = nullptr;
	float tuitionFee = 0;
	const int groupNumber;

	const static int MIN_LENGTH = 3;
	static float feesTotal;
	static int NO_OBJECTS;
public:
	Student(int id, const char* name, float fee, int group):id(id),groupNumber(group) {
		//this->id = id;
		this->setName(name);
		this->tuitionFee = fee;
		Student::feesTotal += fee;
		Student::NO_OBJECTS += 1;
	}

	Student(const char* name, float fee, int group):id(Student::NO_OBJECTS), groupNumber(group) {
		//this->id = id;
		this->setName(name);
		this->tuitionFee = fee;
		Student::feesTotal += fee;
		Student::NO_OBJECTS += 1;
	}

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
	Student(Student& student):id(-1), groupNumber(student.groupNumber) {
		cout << endl << "Calling copy ctor";
		//this->id = student.id;
		//this->tuitionFee = student.tuitionFee;
		//Student::feesTotal += this->tuitionFee;
		this->setTuitionFee(student.tuitionFee);
		this->setName(student.name);
	}

	static float getTotalFees() {
		cout << endl << "A static method";
		return Student::feesTotal;
	}

	float getTuition() {
		return this->tuitionFee;
	}


	Student operator+(int value) {
		//+ does not change the operands
		//this->tuitionFee += value;		//DON't

		Student result = *this;
		result.tuitionFee += value;

		return result;
	}

	//you can't
	//Student operator+(int value, Student s) {

	//}

};

int Student::NO_OBJECTS = 0;
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
	Student s(0, "John Doe", 0, 0);
	return s;
}

int sum(int a, int b) {
	return a + b;
}

int sum(int a, char* aPointer) {
	return a + 10;
}

int sum(int a, int b, int c) {
	return a + b + c;
}

//overload ==

bool operator==(Student s1, Student s2) {
	if (s1.getTuition() == s2.getTuition()) {
		return true;
	} else 
		return false;
}

bool operator>(Student s1, Student s2) {
	if (s1.getTuition() > s2.getTuition()) {
		return true;
	}
	else
		return false;
}

Student operator+(int value, Student s) {

}


int main(int argc, char* argv[]) {
	//Student s1;
	//Student students[10];

	Student s1(1, "Johny", 1000, 1064);
	Student* pS = new Student(2, "Alice", 0, 1064);

	//Student s3(3);
	//Student s4(3,"Boby");

	delete pS;

	//copy constructor
	Student s2 = s1;

	cout << endl << "The sum of tuition fees is  " << Student::getTotalFees();

	doNothing(s1);
	createObject();

	//function overloading
	int rez = sum(10, 20);

	//operator overloading
	cout << s1;				//operator <<(cout, s1)
	cout >> s1;

	s1 = s2;				//operator =(s1, s2)


	s1 = s1 + 100;		// s1.operator+(100)
	s1 = s1 + 100;		//increase tuition fee		operator +(s1, 100)
	s1 = 100 + s1;		//operator+(100, s1)
	s1 = s1 - 100;
	s1 += 100;
	s1++;				//increase group number by 1	operator ++(s1, int)
	++s1;				// operator ++(s1)

	if (!s1) {			//operator!(s1)
		cout << endl << "S1 has a scholarship";
	}

	float tuitionFee = s1;			//cast operator		// operator float(s1)

	if (s1 > s2) {					//operator > (s1, s2)
		cout << endl << "S1 has a bigger tuition fee";
	}

	if (s1 == s2) {					//operator == (s1, s2)
		cout << endl << "They have the same tuition fee";
	}

	char initial = s1[0];			//get the name initial letter		//operator [] (s1, 0)

	int vb = 10;
	//vb = vb + 10;		
	//vb = operator +(vb, 10);

}