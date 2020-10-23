#pragma once


#include <iostream>
using namespace std;

/*
	Sa se implementeze functia withdraw ce accepta doi parametri:
	- balance - reprezinta balanta contului curent
	- amount - reprezinta suma pe care dorim sa o extragem din cont
	Functia trebuie sa respecte urmatoarele cerinte:
	- La apelul functiei withdraw se va extrage din balanta suma dorita
	(Exemplu: In urma apelului withdraw(2000, 1000), balanta va avea valoarea 1000)
	- Daca balanta este negativa si se incearca efectuarea unei tranzactii
	se va aplica o penalizare de 10% asupra balantei, fara a efectua tranzactia
	(Exemplu: pentru o balanta de -1000, la incercarea efectuarii unei tranzactii
	balanta va avea valoarea de -1100).
	- Daca suma pe care dorim sa o extragem este negativa, se va efectua operatia de
	depunere. (pentru o balanta de 1000, la apelul functiei cu un amount de -200, vom
	obtine balanta cu valoarae 1200)
	- Daca suma dorita este mai mare decat valoarea balantei, nu se va efectua nicio operatie
	- Daca se va efectua operatia de withdraw cu amount 0, se va aplica o penalizare de 5% asupra balantei
*/

/*

	Implement the withdraw function that accepts two parameters:
	- balance - represents the balance of the current account
	- amount - represents the amount we want to withdraw from the account
	The function must meet the following requirements:
	- When calling the withdraw function, the desired amount will be extracted from the balance
	(Example: Following the withdraw call (2000, 1000), the balance will have the value 1000)
	- If the balance is negative and an attempt is made to make a transaction
	a 10% penalty will be applied on the balance, without making the transaction
	(Example: for a balance of -1000, when trying to make a transaction
	the balance will have the value of -1100).
	- If the amount we want to withdraw is negative, the operation will be performed
	deposit. (for a balance of 1000, at the call of the function with an amount of -200, we
	get the balance with values ??1200)
	- If the desired amount is greater than the balance value, no operation will be performed
	- If the withdrawal operation is performed with amount 0, a penalty of 5% will be applied on the balance
*/

void withdraw(double* balance, double amount) {

}

/*
	Aceeasi cerinta si pentru withdraw2
	Same requirement for withdraw2
*/

void withdraw2(double& balance, double amount) {

}

/*
	Sa se implementeze metoda toTitleCase(char* text) care transforma un text primit in formatul Title Case
	- toate cuvintele incep cu majuscula
	- ex: "salut. acesta este un test" devine "Salut. Acesta Este Un Test"

	Implement the toTitleCase (char * text) method that converts received text to Title Case format
	- all words start with a capital letter
	- ex: "hello. this is a test" becomes "Hello. This Is A Test"
*/

char* toTitleCase(char* text) {
	return nullptr;
}


/*
	Sa se implementeze metoda removeSpaces(char* text) care elimina toate spatiile dintr-un text primit
	- se iau in considerare toate spatiile (la inceput, la final si in interior)
	- ex: " salut.   acesta este un test " devine "salut.acestaesteuntest"


	Implement the removeSpaces (char * text) method which removes all spaces from a received text
	- all spaces are taken into account (at the beginning, at the end and inside)
	- ex: "hello. this is a test" becomes "hello.thisisatest"
*/

char* removeSpaces(char* text) {
	return nullptr;
}

