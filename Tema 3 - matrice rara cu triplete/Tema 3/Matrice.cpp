#include "Matrice.h"
#include <exception>

using namespace std;


Matrice::Matrice(int m, int n) {
	//	Complexitate timp: Θ(1)
	if (m < 1 || n < 1) {
		throw std::exception("Invalid dimensions of the matrix");
	}

	cp = 1;
	rows = m;
	cols = n;
	vals = 0;

	elem = new TMatriceElem[cp];
	urm = new int[cp];
	prec = new int[cp];

	for (unsigned i = 0; i < cp - 1; i++) {
		urm[i] = i + 1;
		prec[i] = i + 1;
	}
	urm[cp - 1] = -1;
	prec[cp - 1] = -1;

	prim = -1;
	ultim = -1;
	primLiber = 0;
}


int Matrice::aloca() {
	//	Complexitate timp: Θ(1)
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}


void Matrice::dealoca(int i) {
	//	Complexitate timp: Θ(1)
	urm[i] = primLiber;
	prec[i] = primLiber;
	primLiber = i;
}


int Matrice::creeazaNod(TMatriceElem e) {
	//	 Complexitate timp: Θ(1)
	int i = aloca();
	if (i != -1) {
		elem[i] = e;
		prec[i] = -1;
		urm[i] = -1;
	}
	return i;
}


void Matrice::redim() {
	//	Complexitate timp: Θ(n)
	primLiber = cp - 1;
	int newCp = cp * 2;
	TMatriceElem* newElem = new TMatriceElem[newCp];
	int* newUrm = new int[newCp];
	int* newPrec = new int[newCp];
	for (int i = 0; i < vals; ++i) {
		newElem[i] = elem[i];
		newUrm[i] = urm[i];
		newPrec[i] = prec[i];
	}

	for (int i = vals; i < newCp - 1; i++) {
		newUrm[i] = i + 1;
		newPrec[i] = i + 1;
	}
	newUrm[newCp - 1] = -1;
	newPrec[newCp - 1] = -1;

	delete[] elem;
	delete[] urm;
	delete[] prec;

	this->elem = newElem;
	this->urm = newUrm;
	this->prec = newPrec;
	this->cp = newCp;
}


int Matrice::nrLinii() const{
	//	Complexitate timp: Θ(1)
	return rows;
}


int Matrice::nrColoane() const{
	//	Complexitate timp: Θ(1)
	return cols;
}


TElem Matrice::element(int i, int j) const{
	//	Complexitate timp:
	//		Caz favorabil: Se cere primul element, T(n) = 1, T(n) ∈ Θ(1)
	//		Caz defavorabil: Se cere ultimul element, T(n) = n, T(n) ∈ Θ(n)
	//		Caz mediu: T(n) = 1/n * (1 + 2 + ... + n) = (n + 1) / 2, T(n) ∈ Θ(n)
	//	Complexitate generala: T(n) ∈ O(n)
	if (i < 0 || j < 0 || i > rows || j > cols) {
		throw exception("Invalid positions");
	}
	int k = prim;
	while (k != -1) {
		if (elem[k].row == i && elem[k].col == j) {
			return elem[k].val;
		}
		k = urm[k];
	}
	return NULL_TELEMENT;
}



TElem Matrice::modifica(int i, int j, TElem e) {
	//	Complexitate timp:
	//		Caz favorabil: Se modifica primul element, T(n) = 1, T(n) ∈ Θ(1)
	//		Caz defavorabil: Se modifica ultimul element, T(n) = n, T(n) ∈ Θ(n)
	//		Caz mediu: T(n) = 1/n * (1 + 2 + ... + n) = (n + 1) / 2, T(n) ∈ Θ(n)
	//	Complexitate generala: T(n) ∈ O(n)
	if (i < 0 || j < 0 || i > rows || j > cols) {
		throw exception("Invalid positions");
	}

	int ind = prim;
	while (ind != -1) {
		
		if (elem[ind].row > i || (elem[ind].row == i && elem[ind].col >= j)) {
			break;
		}
		ind = urm[ind];
	}
	

	if (ind != -1 && elem[ind].row == i && elem[ind].col == j) {
		TElem old = elem[ind].val;
		if (e == NULL_TELEMENT) {
			// caz stergere element
			if (ind == prim) {
				prec[urm[prim]] = -1;
				prim = urm[prim];
			}
			else if (ind == ultim) {
				urm[prec[ultim]] = -1;
				ultim = prec[ultim];
			}
			else {
				int aux = prec[ind];
				prec[urm[ind]] = prec[ind];
				urm[aux] = urm[ind];
			}
			dealoca(ind);
			--vals;
		}
		else {
			// caz inlocuire element
			elem[ind].val = e;
		}
		return old;
	}

	if (e != NULL_TELEMENT) {
		int poz = creeazaNod({ i, j, e });
		++vals;

		if (primLiber == -1) {
			// nu mai exista spatiu, dublam capacitatea
			redim();
			primLiber = vals;
		}

		if (prim == -1) {
			// lista este vida
			prim = poz;
			ultim = poz;
		}
		else {
			if (ind == prim) {
				// cazul in care elementul trebuie inserat pe prima pozitie
				prec[prim] = poz;
				urm[poz] = prim;
				prim = poz;
			}
			else if (ind == -1) {
				// cazul in care elementul trebuie inserat pe ultima pozitie
				urm[ultim] = poz;
				prec[poz] = ultim;
				ultim = poz;
			}
			else {
				// cazul in care elementul trebuie inserat inaintea lui ind
				int aux = prec[ind];
				urm[aux] = poz;
				prec[ind] = poz;
				prec[poz] = aux;
				urm[poz] = ind;
			}
		}
	}

	return NULL_TELEMENT;
}

Matrice::~Matrice() {
	//	Complexitate timp: Θ(1)
	delete[] elem;
	delete[] urm;
	delete[] prec;
}
