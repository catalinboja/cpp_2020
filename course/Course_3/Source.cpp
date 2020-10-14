#include <iostream>
using namespace std;

void printMsg(const char* msg);
int add(int a, int b);
void interchange(int vb1, int vb2);
void interchange2(int* pVb1, int* pVb2);
void interchange3(int& vb1, int& vb2);

//int main(int argc, char* * argv)
//int main(int no, char* values[])
int main(int argc, char* argv[]) {

	cout << endl << "The default argument is " << argv[0];

	if (argc == 3) {
		cout << endl << "Current user: " << argv[1];
		cout << endl << "Loading file  " << argv[2];
	}

	int vb1 = 10;
	int vb2 = 20;

	cout << endl << "The sum is " << add(vb1, vb2);	// a = vb1, b = vb2

	//interchange(vb1, vb2);	// interchange.vb1 = vb1, inter.vb2 = vb2
	interchange2(&vb1, &vb2);	// interchange2.pVb1 = &vb1,

	interchange3(vb1, vb2);

	cout << endl << "vb1 = " << vb1 << ", vb2 = " << vb2;

	printMsg("The end of the app");

}


// char* msg <-> char msg[] != char msg[10]
void printMsg(const char* msg) {
	cout << endl << msg;
}

int add(int a, int b) {
	int result = a + b;
	return result;
}

void interchange(int vb1, int vb2) {
	int temp = vb1;
	vb1 = vb2;
	vb2 = temp;
}

void interchange2(int* pVb1, int* pVb2) {
	int temp = *pVb1;
	*pVb1 = *pVb2;
	*pVb2 = temp;
}

void interchange3(int& vb1, int& vb2) {
	int temp = vb1;
	vb1 = vb2;
	vb2 = temp;
}