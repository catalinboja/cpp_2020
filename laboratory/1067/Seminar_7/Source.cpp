#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

// 13/11/2020

enum Month {JAN = 1, FEB = 2, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
enum Priority {NORMAL = 100, IMPORTANT = 200, URGENT = 300};

class CalendarDate {
	int day;
	//int month;
	Month month;
	int year;
};

class MinLengthException {

};

class Event {

	//int day;
	////int month;
	//Month month;
	//int year;

	//CalendarDate date;
	
	//char* date;		// 13/11/2020		1/1/2020
	//char date[11];

	//string date;

	string name = "";
	char* date = nullptr;
	Priority priority = Priority::NORMAL;

	static int NO_URGENT_EVENTS;
	const static int DATE_MIN_SIZE = 8;
public:
	void setDate(const char* newDate) {
		if (newDate != nullptr && strlen(newDate) >= DATE_MIN_SIZE) {
			if (this->date != nullptr) {
				delete[] this->date;
			}
			this->date = new char[strlen(newDate) + 1];
			strcpy(this->date, newDate);
		}
		else
		{
			throw MinLengthException();
		}
	}

	Priority getPriority() {
		return this->priority;
	}

	void setPriority(Priority priority) {
		this->priority = priority;
	}

	Event(string name, const char* date, Priority priority) {
		this->name = name;
		this->setDate(date);
		this->setPriority(priority);

		if (this->priority == Priority::URGENT) {
			Event::NO_URGENT_EVENTS += 1;
		}
	}

	static int getNoUrgentEvents() {
		//this does not exist here
		//string test = this->name;
		return Event::NO_URGENT_EVENTS;

	}

	~Event() {
		if (this->date != nullptr) {
			delete[] this->date;
		}
		if (this->priority == Priority::URGENT) {
			Event::NO_URGENT_EVENTS -= 1;
		}
	}

	Event(const Event& ev) {
		//ev.name = this->name;
		this->name = ev.name;
		this->priority = ev.priority;
		this->setDate(ev.date);
	}

};

int Event::NO_URGENT_EVENTS = 0;

void doNothing(Event ev) {

}

Event anotherFunction() {
	Event temp("OOP Laboratory", "13/11/2020", Priority::NORMAL);
	return temp;
}

int main(int argc, char* argv[]) {
	Event ev1("OOP Laboratory", "13/11/2020", Priority::NORMAL);
	Event ev2("OOP Quiz", "18/11/2020", Priority::URGENT);
	Event* pEv = new Event("OOP Project", "24/11/2020", Priority::URGENT);

	cout << endl << "Number of urgent events = " << Event::getNoUrgentEvents();

	delete pEv;

	cout << endl << "Number of urgent events = " << Event::getNoUrgentEvents();

	doNothing(ev1);
	anotherFunction();

	//calling the copy constructor
	Event ev3 = ev1;
	//Event ev4(ev1);
}