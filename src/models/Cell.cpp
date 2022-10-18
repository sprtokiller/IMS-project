/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/Cell.h"
#include "models/Paper.h"

template<class T>
void SimpleCell::doCalc(size_t id, size_t cores, T* ca) {
	for (size_t y = id * ca->HEIGHT / cores; y < (id + 1) * ca->HEIGHT / cores; y++) {
		if (y == 0) continue;
		if (y >= ca->HEIGHT - 1) break;
		for (size_t x = 1; x < ca->WIDTH - 1; x++) {
			SimpleCell* cell = ca->getNext(x, y);
			const SimpleCell* oldCellUp = ca->getOld(x, y - 1);
			const SimpleCell* oldCellDown = ca->getOld(x, y + 1);
			const SimpleCell* oldCellLeft = ca->getOld(x - 1, y);
			const SimpleCell* oldCellRight = ca->getOld(x + 1, y);
		}
	}
}

void SimpleCell::fixPaperHeight()
{
	B += floor(h * 300);
	C -= floor(h * 300);
}

void SimpleCell::addWater()
{
	W += WATER_BRUSH_WATER_ADD;
}

void SimpleCell::addInk()
{
	W += INK_BRUSH_WATER_ADD;
	I += INK_BRUSH_WATER_ADD;
}

template<class T>
void ComplexCell::doCalc(size_t id, size_t cores, T* ca) {
	
}

namespace CXX {
	void Linking() {
		Paper::WorldUnit c;
		Paper::CAutomata ca;
		c.doCalc(0, 0, &ca);

		exit(EXIT_FAILURE);
	}
}