#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

class AbstractVehicle {
protected:
	string model = "";
	int maxSpeed = 0;
public:
	virtual string getModel() {
		return this->model;
	}
	virtual void getDescription() = 0;

};

class Tesla : public AbstractVehicle {
public:
	string getModel() {
		return "Tesla";
	}

	void getDescription() {
		cout << endl << "This is a Tesla";
	}
};

class Toyota : public AbstractVehicle {
	void getDescription() {
		cout << endl << "This is a Toyota";
	}
};

//int sum(int a, int b) {
//	return a + b;
//}

//float sum(float a, float b) {
//	return a + b;
//}

template<typename myType> myType sum(myType a, myType b) {
	return a + b;
}

template<typename Z, typename X, typename Y> 
Z doSomething(X vb1, Y vb2, int vb3) {
	//...

	return "";
}

template <typename T, typename X> class Vehicle {
	string model;
	T color;
	X engineType;
public:
	T getColor() {
		return this->color;
	}

	void setColor(T value) {
		if (value > 0) {
			this->color = value;
		}
	}

	Vehicle(){}

	Vehicle(string Model, T Color, X Engine): model(Model) {
		this->setColor(Color);
		this->engineType = Engine;
	}
};

template<> void Vehicle<string, int>::setColor(string value) {
	if (!value.empty()) {
		this->color = value;
	}
}

//template<typename string, typename X> void Vehicle<string, X>::setColor(string value) {
//	if (!value.empty()) {
//		this->color = value;
//	}
//}


int main() {

	Tesla tesla;

	//test template methods
	int rez = sum<int>(2, 3);
	string message = sum<string>(" Hello ", " C++ ");

	doSomething<string, int, Tesla>(5, tesla, 10);

	Vehicle<string, int> v1;
	Vehicle<int, int> v2;
	Vehicle<int, int> v3;

	v3.setColor(100);
	cout << endl << "The color of v3 is " << v3.getColor();


	v1.setColor("red");
	cout << endl << "The color of v3 is " << v1.getColor();

	//AbstractVehicle vehicle;

	//the abstract class is used as a reference/pointer type
	AbstractVehicle* pVehicle;

	AbstractVehicle* fleet[3];
	fleet[0] = new Tesla();
	fleet[1] = new Toyota();
	fleet[2] = new Tesla();

	for (int i = 0; i < 3; i++) {
		//cout << endl << fleet[i]->getModel();
		fleet[i]->getDescription();
	}

	//use vector
	vector<int> numbers;
	vector<string> names;

	numbers.push_back(10);
	numbers.push_back(5);
	numbers.push_back(3);

	numbers.pop_back();

	names.push_back("John");
	names.push_back("Alice");
	names.push_back("John");

	for (int i = 0; i < numbers.size(); i ++ ) {
		cout << endl << "-> " << numbers[i];
	}

	for (int i = 0; i < names.size(); i++) {
		cout << endl << "Name: " << names[i];
	}

	set<string> names2;
	names2.insert("John");
	names2.insert("John");
	names2.insert("John");
	names2.insert("Alice");

	set<string>::iterator it;
	for (it = names2.begin(); it != names2.end(); it++) {
		cout << endl << "Unique name " << *it;
	}

	map<int, string> students;
	students[100] = "John";
	students[201] = "Alice";
	students[300] = "Bob";

	cout << endl << "The name of the student with id  201 is " << students[201];

}