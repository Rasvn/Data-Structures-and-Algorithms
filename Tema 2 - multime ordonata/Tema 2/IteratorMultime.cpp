#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m): mult(m) {
	/* de adaugat */
	curent = m.prim;
}

TElem IteratorMultime::element() const {
	/* de adaugat */
	if (this->valid() == false) {
		throw std::exception("");
	}
	return curent->element();
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	return curent != nullptr;
}

void IteratorMultime::urmator() {
	/* de adaugat */
	curent = curent->urmator();
}

void IteratorMultime::prim() {
	/* de adaugat */
	curent = mult.prim;
}
