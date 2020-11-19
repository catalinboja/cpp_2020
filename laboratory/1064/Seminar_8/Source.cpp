#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

enum EventType {NORMAL, IMPORTANT = 100, URGENT = 200};
enum Month {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

class CalendarDate {
	int day;
	//int month;
	Month month;
	int year;
};

class DateException {

};

class Event {
	string name = "";
	//int type;
	//string type;
	EventType type = EventType::NORMAL;

	//18/11/2020
	//1/1/2020
	//CalendarDate date;
	//char date[11];
	char* date = nullptr;

	static int const MIN_DATE_SIZE = 8;
	static int NO_IMPORTANT_EVENTS;

public:
	void setDate(const char* newDate) {
		if (strlen(newDate) >= MIN_DATE_SIZE) {
			if (this->date != nullptr) {
				delete[] this->date;
			}
			this->date = new char[strlen(newDate) + 1];
			strcpy(this->date, newDate);
		}
		else {
			throw DateException();
		}
	}

	Event(string name, EventType type, const char* date) {
		this->name = name;
		this->type = type;
		if (this->type == EventType::IMPORTANT) {
			Event::NO_IMPORTANT_EVENTS += 1;
		}
		this->setDate(date);
	}

	~Event() {
		if (this->date != nullptr) {
			delete[] this->date;
		}
		if (this->type == EventType::IMPORTANT) {
			Event::NO_IMPORTANT_EVENTS -= 1;
		}
	}

	static int getNoImportantEvents() {
		return Event::NO_IMPORTANT_EVENTS;
	}

	//copy ctor
	Event(Event& event) {
		//event.name = this->name;
		this->name = event.name;
		this->type = event.type;
		this->setDate(event.date);
	}

	string getName() {
		return this->name;
	}

	EventType getType() {
		return this->type;
	}

	char* getDate() {
		return this->date;
	}
};

int Event::NO_IMPORTANT_EVENTS = 0;

void operator<<(std::ostream& console, Event ev) {
	console << endl << "------------------------";
	console << endl << "Name : " << ev.getName();
	console << endl << "Type : " << ev.getType();
	console << endl << "Date : " << ev.getDate();

}

int main(int argc, char* argv[]) {
	Event ev1("OOP Laboratory", EventType::NORMAL, "18/11/2020");
	Event ev2("OOP Course", EventType::IMPORTANT, "18/11/2020");
	Event *pEv = new Event("OOP Assignment", EventType::IMPORTANT, "21/11/2020");

	ev2.setDate("19/11/2020");


	cout << endl << "We have " << Event::getNoImportantEvents() << " important events";

	delete pEv;

	cout << endl << "We have " << Event::getNoImportantEvents() << " important events";

	Event ev3 = ev2;

	cout << ev2;
}