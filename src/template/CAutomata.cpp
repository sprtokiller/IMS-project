#include "template/CAutomata.h"

CAutomata_T::CAutomata_T(size_t WIDTH, size_t HEIGHT, Cell_Factory factory) : W(WIDTH), H(HEIGHT) {
	old = new World_T(W, H, factory);
	next = new World_T(W, H, factory);
}

CAutomata_T::~CAutomata_T() {
	free(old);
	free(next);
}

void CAutomata_T::mirror() {
	delete old;
	old = new World_T(*next);
}
