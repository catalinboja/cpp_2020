#include <iostream>
#include <string>
using namespace std;

class AbstractAuto {
protected:
	string model;
	int maxSpeed;
public:
	int getMAxSpeed() {
		return this->maxSpeed;
	}
	
	virtual void getDescription() = 0;
	//virtual float doSomethingComplex(int a, double b, char* t) = 0;
};

class Tesla : public AbstractAuto {
	void getDescription() {
		cout << endl << "This is a Tesla";
	}

	void getDescripion(string details) {

	}
};

class Hybrid : public AbstractAuto {
	void getDescription() {
		cout << endl << "This is a Toyota";
	}
};


template<typename type> type sum(type a, type b) {
	return a + b;
}

template<typename X, typename Y> string concatenate(X vb1, Y vb2) {
	//
}

template<typename X, typename Y, typename Z> 
Z concatenate2(X vb1, Y vb2) {
	//
}


class AbstractEngine {

};

enum Types {Electric, Gas};

template<typename T, typename X> class VehicleTemplate {
	string model;
	T color;
	X engineType;
	int maxSpeed;
public:
	T getColor() {
		return this->color;
	}

	void setColor(T value) {
		if(value > 0)
			this->color = value;
	}

	VehicleTemplate(string Model, T color, X Engine, int Speed) {
		//
	}

	VehicleTemplate(){}
};

template<> void VehicleTemplate<string, AbstractEngine>::setColor(string value) {
	if (!value.empty())
		this->color = value;
}



int main() {


	VehicleTemplate<string, AbstractEngine> vehicle1;
	vehicle1.setColor("Red");
	VehicleTemplate<int, Types> vehicle2;

	//AbstractAuto aa;
	//we use it as a reference/pointer type
	AbstractAuto* pAuto;

	Tesla tesla;
	Hybrid hybrid;

	AbstractAuto* vehicleFleet[3];
	vehicleFleet[0] = &tesla;
	vehicleFleet[1] = &hybrid;
	vehicleFleet[2] = new Tesla();

	for (int i = 0; i < 3; i++) {
		vehicleFleet[i]->getDescription();
	}


	int rezult = sum<int>(2, 4);
	string message = sum<string>("Hello ", "C++");
}