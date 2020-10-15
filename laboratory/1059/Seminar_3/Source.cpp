#include <iostream>
using namespace std;

void afisareVector(int vector[], int nr);

//int main(int argc, char** argv)
//int main(int argc, char* argv[])


int* creareSiInitializareVector(int n, int valoareInitiala) {
	int* vector = new int[n];
	for (int i = 0; i < n; i++) {
		vector[i] = valoareInitiala;
	}
	return vector;
}

void adaugaElementVector(int* & vector, int & nr, int valoareNoua) {
	int* vectorNou = new int[nr + 1];
	for (int i = 0; i < nr; i++) {
		vectorNou[i] = vector[i];
	}
	vectorNou[nr] = valoareNoua;
	nr += 1;

	//stergem vechiul vector din memorie - fara memory leak
	delete[] vector;

	vector = vectorNou;
}

void adaugaElementVector2(int* * pVector, int* pNr, int valoareNoua) {
	int* vectorNou = new int[*pNr + 1];
	for (int i = 0; i < *pNr; i++) {
		vectorNou[i] = (*pVector)[i];
	}
	vectorNou[*pNr] = valoareNoua;
	*pNr += 1;

	//stergem vechiul vector din memorie - fara memory leak
	delete[] *pVector;

	*pVector = vectorNou;
}

//Seminar_3.exe 5 10

int main(int argc, char* argv[]) {

	int* valori = nullptr;
	//int* valori = NULL;
	//int* valori = 0;
	int nrElemente = 0;

	//primeste intotdeauna un argument pe prima pozitie
	if (argc == 3) {
		//cout << endl << argv[0];
		int nr = atoi(argv[1]);
		int valoareInitiala = atoi(argv[2]);
		cout << endl << "Am primit n = " << nr << " si " <<
			"valoare initiala = " << valoareInitiala;
		valori = creareSiInitializareVector(nr, valoareInitiala);	// n = nr, valoareInitiala = valoareInitiala
		nrElemente = nr;
	}
	else
	{
		cout << endl << "Lipsa argumente: [nr elemente] [valoare initiala]";
	}

	afisareVector(valori, nrElemente);

	//adaugare elemente noi la vector
	//abordarea naiva dar gresita
	//NU ASA
	//for (int i = 0; i < 10; i += 1) {
	//	nrElemente += 1;
	//	valori[nrElemente - 1] = 100;
	//}

	adaugaElementVector(valori, nrElemente, 100);
	adaugaElementVector2(&valori, &nrElemente, 90);

	afisareVector(valori, nrElemente);

}

void afisareVector(int vector[], int nr) {

	if (vector == nullptr) {
		cout << endl << "Vectorul nu este initializat";
	}
	else {

		cout << endl << "Vectorul este: ";
		for (int i = 0; i < nr; i++) {
			cout << " " << vector[i];
		}
	}
}