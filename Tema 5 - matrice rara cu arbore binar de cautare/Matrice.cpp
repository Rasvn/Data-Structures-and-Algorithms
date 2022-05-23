#pragma warning (disable: 6386)
#include "Matrice.h"

#include <exception>
#include <iostream>

using namespace std;

bool Matrice::rel(const Triplet& t1, const Triplet& t2) const {
	if (t1.lin < t2.lin) {
		return true;
	}
	if (t1.lin == t2.lin && t1.col < t2.col) {
		return true;
	}
	return false;
}

void Matrice::actPrimLiber() {
	while (el[primLiber] != NULL_TRIPLET) {
		primLiber++;
	}
}

int Matrice::creeazaNod(Triplet e) {
	int i = primLiber;
	el[i] = e;
	actPrimLiber();
	if (primLiber >= cap) {
		throw exception("Spatiu insuficient!");
	}
	return i;
}

int Matrice::adaugaRec(int p, Triplet e) {
	if (p == -1) {
		p = creeazaNod(e);
	}
	else {
		if (rel(e, el[p])) {
			st[p] = adaugaRec(st[p], e);
		}
		else {
			dr[p] = adaugaRec(dr[p], e);
		}
	}
	return p;
}

int Matrice::minim(int p) {
	while (st[p] != -1) {
		p = st[p];
	}
	return p;
}

int Matrice::stergeRec(int p, Triplet e) {
	if (p == -1) {
		return -1;
	}
	if (rel(e, el[p])) {
		// se sterge din subarborele stang
		st[p] = stergeRec(st[p], e);
		return p;
	}
	if (e == el[p]) {
		// am ajuns la nodul care trebuie sters
		if (st[p] != -1 && dr[p] != -1) {
			// nodul are si subarbore stang si drept
			int temp = minim(dr[p]);
			// se muta cheia minima in p
			el[p] = el[temp];
			// se sterge nodul cu cheia minima din subarborele drept
			dr[p] = stergeRec(dr[p], el[p]);
			return p;
		}
		else {
			int temp = p, repl;
			if (st[p] == -1) {
				// nu exista subarbore stang
				repl = dr[p];
			}
			else {
				// nu exista subarbore drept
				repl = st[p];
			}
			st[temp] = -1;
			dr[temp] = -1;
			el[temp] = NULL_TRIPLET;

			if (p < primLiber) {
				primLiber = p;
			}

			return repl;
		}
	}
	// se sterge din subarborele drept
	dr[p] = stergeRec(dr[p], e);
	return p;
}

Matrice::Matrice(int m, int n) {
	if (m <= 0 || n <= 0) {
		throw exception("Dimensiuni invalide!");
	}

	nrLin = m;
	nrCol = n;
	cap = m * n;

	el = new Triplet[cap];
	st = new int[cap];
	dr = new int[cap];

	nrElem = 0;
	root = -1;
	primLiber = 0;

	for (int i = 0; i < cap; ++i) {
		el[i] = NULL_TRIPLET;
		st[i] = -1;
		dr[i] = -1;
	}
}



int Matrice::nrLinii() const{
	return nrLin;
}


int Matrice::nrColoane() const{
	return nrCol;
}


TElem Matrice::element(int i, int j) const{
	if (i < 0 || j < 0 || i >= nrLin || j >= nrCol) {
		throw exception("Pozitie invalida!");
	}
	Triplet toFind = { i, j, NULL_TELEMENT };
	int curent = root;
	while (curent != -1) {
		if (rel(toFind, el[curent])) {
			curent = st[curent];
			continue;
		}
		if (toFind == el[curent]) {
			return el[curent].elem;
		}
		curent = dr[curent];
	}
	return NULL_TELEMENT;
}



TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= nrLin || j >= nrCol) {
		throw exception("Pozitie invalida!");
	}
	Triplet toFind = { i, j, e };
	int curent = root;
	while (curent != -1) {
		if (rel(toFind, el[curent])) {
			
			curent = st[curent];
			continue;
		}
		if (toFind == el[curent]) {
			break;
		}
		curent = dr[curent];
	}
	if (curent == -1) {
		// Cazul in care adaugam in matrice
		root = adaugaRec(root, toFind);
		nrElem++;
		return NULL_TELEMENT;
	}
	if (e == NULL_TELEMENT) {
		// Cazul in care stergem din matrice
		TElem old = el[curent].elem;
		root = stergeRec(root, el[curent]);
		nrElem--;
		return old;
	}
	// Cazul in care trebuie sa modificam in matrice
	TElem old = el[curent].elem;
	root = stergeRec(root, el[curent]);
	root = adaugaRec(root, toFind);
	return old;
}

