#include "Matrice.h"
#include "VectorDinamic.h"
#include <exception>
using namespace std;

Matrice::Matrice(int n, int m)
		: Linie(1), Valoare(1) {
	if (m < 0 || n < 0) {
		throw exception("");
	}
	nrLin = n;
	nrCol = m;
	Coloana = new int[nrCol + 1];
	for (int i = 0; i <= nrCol; ++i) {
		Coloana[i] = 0;
	}
}

Matrice::~Matrice() {
	delete[] Coloana;
}

int Matrice::nrLinii() const{
	return nrLin;
}

int Matrice::nrColoane() const{
	return nrCol;
}

TElem Matrice::element(int i, int j) const {
	if (i < 0 || i > nrLin || j < 0 || j > nrCol) {
		throw exception("");
	}
	for (int k = Coloana[i]; k < Coloana[i + 1]; ++k) {
		if (Linie.element(k) == j) {
			return Valoare.element(k);
		}
	}
	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || i > nrLin || j < 0 || j > nrCol) {
		throw exception("");
	}
	int k;
	bool passed = false;
	for (k = Coloana[i]; k < Coloana[i + 1]; ++k) {
		passed = true;
		if (Linie.element(k) >= j) {
			break;
		}
	}
	if (passed && Linie.element(k) == j) {
		TElem valoareVeche = Valoare.element(k);
		Valoare.modifica(k, e);
		return valoareVeche;
	}

	Linie.adauga(k, j);
	Valoare.adauga(k, e);
	
	for (int p = i + 1; p <= nrLin; ++p) {
		Coloana[p]++;
	}
	return NULL_TELEMENT;
}
