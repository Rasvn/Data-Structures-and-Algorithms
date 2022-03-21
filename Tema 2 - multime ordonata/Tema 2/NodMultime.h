#pragma once
#include "Multime.h"

class Nod;

typedef int TElem;
typedef Nod* PNod;

class Nod {
private:
	TElem elem;
	PNod next;

public:
	friend class Multime;
	// constructor
	Nod(TElem e, PNod next);
	TElem element();
	PNod urmator();
};
