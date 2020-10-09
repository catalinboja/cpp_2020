
#include <iostream>
using namespace std;

#define NR 5
#define TESTARE

void oFunctie();

int main() {

#ifdef TESTARE
	int vector[NR];
	for (int i = 0; i < NR; i++)
		cout << " " << vector[i];
#endif // TESTARE

	char oVariabilaChar = 'A';
	int oVariabilaInt;

	std::cout << std::endl << "Valoare char este " << oVariabilaChar;
	//std::cout << std::endl << "Valoare int este " << oVariabilaInt;

	//cout << endl << "Noua valoare pentru caracter :";
	//cin >> oVariabilaChar;
	//std::cout << std::endl << "Valoare char este " << oVariabilaChar;

	//vector definit static
	const int NR_VALORI = 10;

	//int valori[NR_VALORI] = { 0 };
	//int valori[NR_VALORI] = { 1,2,3,4,5,6,7,8,9,10 };

	int valori[NR_VALORI];
	for (int i = 0; i < NR_VALORI; i++) {
		valori[i] = i + 1;
	}

	cout << endl << "Vectorul este: ";
	for (int i = 0; i < NR_VALORI; i++) {
		cout << " " << valori[i];
	}


	oFunctie();

	//return 0;
}

void oFunctie() {
	char oVariabilaChar = 'B';
	int oVariabilaInt;
}