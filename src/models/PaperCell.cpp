/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/PaperCell.h"
#include "models/Paper.h"

#include <thread>

template<class T>
void SimpleCell::doCalc(size_t cores, T* ca) {
	std::vector<std::thread> threads;
	for (size_t id = 0; id < cores; id++) {
		for (size_t y = id * ca->HEIGHT / cores; y < (id + 1) * ca->HEIGHT / cores; y++) {
			if (y == 0) continue;
			if (y >= ca->HEIGHT - 1) break;
			for (size_t x = 1; x < ca->WIDTH - 1; x++) {
				//get current cell
				const SimpleCell* o = ca->getOld(x, y);

				//create a list of 4 cells
				std::vector<const SimpleCell*> neighbours = { ca->getOld(x, y - 1), ca->getOld(x, y + 1), ca->getOld(x - 1, y), ca->getOld(x + 1, y) };

				// 1: water diffusion
				int water_sum = o->W;
				for (const SimpleCell* k : neighbours)
				{
					//water height in neighbor cell
					int k_WH = k->B + k->W;
					//water height in cell
					int o_WH = o->B + o->W;
					//water height difference 
					int ko_WH = k_WH - o_WH;
					int ok_WH = -ko_WH;

					//water pipe height of neighbor cell
					int PH_ko = k->B + k->C;
					//water pipe height of cell
					int PH_ok = o->B + o->C;

					//water flow to cell
					int dW_ko = Tmax(0.0, WATER_DIFUSION_ALPHA * Tmin(ko_WH, k_WH - PH_ko) / 4);
					//water flow from cell
					int dW_ok = Tmax(0.0, WATER_DIFUSION_ALPHA * Tmin(ok_WH, o_WH - PH_ok) / 4);

					water_sum += dW_ko - dW_ok;
				}
				// 4: water evaporation
				water_sum -= WATER_EVAPORATION_RATE;
				water_sum = Tmax(water_sum, 0);
				ca->getNext(x, y)->W = water_sum;
			}
		}
	}
	
	for (auto& th : threads) th.join();
	threads.clear();

	ca->flip();
}

void SimpleCell::fixPaperHeight()
{
	B += floor(h * B_CHANGE);
	C -= floor(h * C_CHANGE);
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
void ComplexCell::doCalc(size_t cores, T* ca) {
	std::vector<std::thread> threads;
	for (size_t id = 0; id < cores; id++) {
		for (size_t y = id * ca->HEIGHT / cores; y < (id + 1) * ca->HEIGHT / cores; y++) {
			if (y == 0) continue;
			if (y >= ca->HEIGHT - 1) break;
			for (size_t x = 1; x < ca->WIDTH - 1; x++) {
				//MoveWater();
				//MovePigment();
				//TransferPigment();
				//SimulateCapillaryFlow();
			}
		}
	}
	for (auto& th : threads) th.join();
	threads.clear();

	ca->flip();
}

void ComplexCell::fixPaperHeight()
{
	c = h * (C_MAX - C_MIN) + C_MIN;
}

void ComplexCell::setHeightGradient()
{
	//hx = 
}

// works with M, u, v, p
void ComplexCell::moveWater()
{
	updateVelocities();
	relaxDivergence();
	flowOutward();
}

// works with M, u, v, p
void ComplexCell::updateVelocities()
{
	
}

// works with M, u, v, p
void ComplexCell::relaxDivergence()
{
	
}

// works with M, p
void ComplexCell::flowOutward()
{
	
}

namespace CXX {
	void Linking() {
		Paper::WorldUnit c;
		Paper::CAutomata ca;
		c.doCalc(0, &ca);

		exit(EXIT_FAILURE);
	}
}