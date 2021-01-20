#include<iostream>
#include<string>


class UniversityInterface {
public:
	virtual void getDescription() = 0;		//virtual pure methods
};

class Student: public UniversityInterface {
public:
	Student() {

	}

	virtual void getDescription() {

	}
};

class MasterStudent : public Student {
	virtual void getDescription() {

	}
};

class PhDStudent : public Student {
	virtual void getDescription() {

	}
};

void doSomething() {

}

//int sum(int a, int b) {
//	return a + b;
//}
//
//float sum(float a, float b) {
//	return a + b;
//}
//
//std::string sum(std::string a, std::string b) {
//	return a + b;
//}

template<typename X> X sum(X a, X b) {
	return a + b;
}

template<typename Z, typename Y,typename W> Z doSomething(Y a, int b, W c) 
{
	//use them
}


template<typename T> class Box {
	float weight;
	T content;
public:
	Box(float Weight, T Content) {
		this->weight = Weight;
		this->content = Content;
	}

	Box() {

	}

	T getContent() {
		return this->content;
	}
};



int main() {

	Box<int> intBox;
	Box<std::string> stringBox;
	Box<Student> studentBox;

	char* msg = new char[] {"test"};
	Box<char*> string2Box(0, msg);

	//int rez = sum(2, 3);
	int rez = sum<int>(2, 3);
	float rez2 = sum<float>(2.9, 3.0);
	std::string message = sum<std::string>("Hello ", "C++");

	std::cout << std::endl << "The message is " << message;

	UniversityInterface* pointer;


	//int vb = doSomething();
	//int vb2 = Student();

	//Student student;
	Student* pStudent;

	Student** students = new Student*[3];
	students[0] = new MasterStudent();
	students[1] = new PhDStudent();
	students[2] = new MasterStudent();

	for (int i = 0; i < 3; i++) {
		students[i]->getDescription();
	}

}