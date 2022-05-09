#include "IteratorMD.h"
#include "MD.h"

using namespace std;

void IteratorMD::deplasare() {
	while ((curentTD < md.m) && md.e[curentTD].first == NIL)
		curentTD++;
}

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	/* de adaugat */
	curentTD = 0;
	deplasare();
	curentVECT = 0;
}

TElem IteratorMD::element() const{
	/* de adaugat */
	return { md.e[curentTD].first, md.e[curentTD].second.at(curentVECT) };
}

bool IteratorMD::valid() const {
	/* de adaugat */
	return curentTD < md.m;
}

void IteratorMD::urmator() {
	/* de adaugat */
	if (curentVECT + 1 < md.e[curentTD].second.size()) {
		curentVECT++;
		return;
	}
	curentTD++;
	deplasare();
	curentVECT = 0;
}

void IteratorMD::prim() {
	/* de adaugat */
	curentTD = 0;
	deplasare();
	curentVECT = 0;
}

