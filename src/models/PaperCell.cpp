/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/PaperCell.h"
#include "models/Paper.h"

template<class T>
void SimpleCell::doCalc(size_t id, size_t cores, T* ca) {
	for (size_t y = id * ca->HEIGHT / cores; y < (id + 1) * ca->HEIGHT / cores; y++) {
		if (y == 0) continue;
		if (y >= ca->HEIGHT - 1) break;
		for (size_t x = 1; x < ca->WIDTH - 1; x++) {
			//get current cell
			SimpleCell* cell = ca->getNext(x, y);

			//create a list of 4 cells
			std::vector<const SimpleCell*> cells = { ca->getOld(x, y - 1), ca->getOld(x, y + 1), ca->getOld(x - 1, y), ca->getOld(x + 1, y) };

			// 1: water diffusion
			int water_sum = cell->W;
			for (const SimpleCell* n : cells)
			{
				int PipeHeight_ko = Tmax(cell->B, n->B + n->C);
				int PipeHeight_ok = Tmax(n->B, cell->B + cell->C);
				int d_W_ko = (int)Tmax(0.0, floor(WATER_DIFUSION_ALPHA * Tmin(n->B + n->W - cell->B - cell->W, n->B + n->W - PipeHeight_ko) / 4.0));
				int d_W_ok = (int)Tmax(0.0, floor(WATER_DIFUSION_ALPHA * Tmin(cell->B + cell->W - n->B - n->W, cell->B + cell->W - PipeHeight_ok) / 4.0));
				water_sum += (d_W_ko - d_W_ok);
			}

			water_sum = Tmax(water_sum, 0);
			cell->W = water_sum;
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