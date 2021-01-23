#include <iostream>
#include <string>

#include <vector>
#include <set>
#include <map>

using namespace std;

class AbstractVehicle {
protected:
	int maxSpeed = 0;
	int mileage = 0 ;
	string model = "";
public:
	int getSpeed() {
		return this->maxSpeed;
	}
	AbstractVehicle() {

	}

	virtual string getModel() = 0;
	virtual float getPricePerDay() = 0;
};

class PrintingInterface {
public:
	virtual void print() = 0;
};

class EVehicle : public AbstractVehicle, public PrintingInterface {
public:
	float accLevel;
	virtual string getModel() {
		return "TESLA Model S";
	}

	float getPricePerDay() {
		return 50;
	}

	virtual void print() {
		cout << endl << "Print an EV";
	}
};

class HybridVehicle : public AbstractVehicle {
	float accLevel;
	string engineType;
	virtual string getModel() {
		return "Toyota Prius";
	}

	float getPricePerDay() {
		return 35;
	}
};

ostream& operator<<(ostream& out, EVehicle& ev) {
	out << endl << "EV";
	return out;
}

class Puppy: public PrintingInterface {
	virtual void print() {
		cout << endl << "This is Puppy";
	}
};

//void printAnything(int value) {
//	cout << endl << "The value is " << value;
//}
//
//void printAnything(string value) {
//	cout << endl << "The value is " << value;
//}
//
//void printAnything(EVehicle value) {
//	cout << endl << "The value is " << value;
//}

template <typename X> void printAnything(X value) {
	cout << endl << "The value is " << value;
}

template<typename X, typename Y> class LeaseContract {
	X object;
	string owner;
	Y duration;
public:
	Y getDuration() {
		return this->duration;
	}

	void setDuration(Y value) {
		if(value > 0 )
			this->duration = value;
	}
};

template<> void LeaseContract<EVehicle, string>::setDuration(string deadline) {
	cout << endl << "The special version";
	this->duration = deadline;
}

int main() {

	//an abstract class can be used as a "reference type"/"pointer type"

	//AbstractVehicle vehicle;
	AbstractVehicle* pVehicle = nullptr;
	//pVehicle = new AbstractVehicle();


	//manage everything by a single array - an array of pointers + virtual methods
	AbstractVehicle* vechicles[5];

	EVehicle ev;
	vechicles[0] = &ev;
	vechicles[1] = new EVehicle();
	vechicles[2] = new HybridVehicle();
	vechicles[3] = new HybridVehicle();
	vechicles[4] = new HybridVehicle();

	for (int i = 0; i < 5; i++) {
		vechicles[i]->getPricePerDay();
	}

	PrintingInterface* thingsToPrint[2];
	thingsToPrint[0] = new Puppy();
	thingsToPrint[1] = new EVehicle();

	for (int i = 0; i < 2; i++) {
		thingsToPrint[i]->print();
	}

	EVehicle electrics[100];
	HybridVehicle hybrids[200];

	cout << endl << "---------------------";
	printAnything<int>(5);
	printAnything<string>("message");
	printAnything<EVehicle>(ev);

	LeaseContract<EVehicle, int> eVehicleContract;
	eVehicleContract.setDuration(100);
	LeaseContract<string, int> messageContract;
	messageContract.setDuration(23);

	LeaseContract<EVehicle, string> eVContract;
	eVContract.setDuration("December 2021");

	//STL
	//vector

	vector<int> integers;
	vector<string> messages;
	vector<EVehicle> eVehicles;
	vector<AbstractVehicle*> fleet;

	integers.push_back(10);
	integers.push_back(20);
	integers.push_back(30);

	messages.push_back("Hello");
	messages.push_back("C++");

	for (int i = 0; i < messages.size(); i++) {
		cout << endl << messages[i];
	}

	messages.pop_back();

	for (int i = 0; i < messages.size(); i++) {
		cout << endl << messages[i];
	}

	fleet.push_back(new EVehicle());

	//set

	set<string> names;
	names.insert("John");
	names.insert("Alice");
	names.insert("Bob");
	names.insert("John");

	set<string>::iterator it;
	for (it = names.begin(); it != names.end(); it++) {
		cout << endl << "Name is " << *it;
	}

	//map
	map<int, string> students;
	//students.insert(1, "John");
	students[100] = "John";
	students[202] = "Alice";
	students[300] = "Bob";

	cout << endl << "The name of the student with id  = 300 is " << students[300];


}
