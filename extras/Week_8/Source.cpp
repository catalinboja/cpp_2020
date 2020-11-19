#include <iostream>
#include <string>
#include <vector>
using namespace std;

class A {

};

class B {
public:
	A createSomething() {
		return A();
	}
};

class C{
	A a;
};

int main() {

	vector<int> values;

	string msg = "This is a test. Another This";

	cout << endl << msg.find("This");
	cout << endl << msg.find("This", 1);
	cout << endl << msg.find(" ");
	cout << endl << msg.find(" ",5);
	cout << endl << msg.find("test");
	cout << endl << msg.find("dddddd");

	cout << endl << msg.substr(0, 4);
	//msg.compare();

	B b;
	A a = b.createSomething();

}