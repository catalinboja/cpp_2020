#pragma once
#include "Source.cpp"

class PhdStudent: public Student {
	void doSomethingExtra() {
		this->extra = 23;
	}
};