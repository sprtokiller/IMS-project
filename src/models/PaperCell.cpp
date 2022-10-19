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

void ComplexCell::setHeightGradient(double new_hx, double new_hy)
{
	hx = new_hx;
	hy = new_hy;
}

// works with M, u, v, p
template<class T>
void ComplexCell::moveWater(T* ca, size_t x, size_t y)
{
	updateVelocities(ca, x, y);
	relaxDivergence();
	flowOutward();
}

// works with M, u, v, p
template<class T>
void ComplexCell::updateVelocities(T* ca, size_t x, size_t y)
{
	// TODO: must clear all u/v after flip
	u -= hx;
	v -= hy;
	double dt = 1 / ca->getMaxSpeed();
	for (double t = 0.0; t < 1.0; t += dt)
	{
		double A = 0.0;
		A += pow(ca->getOld(x, y)->u, 2);
		A -= pow(ca->getOld(x + 1, y)->u, 2);
		A += ((ca->getOld(x, y)->u - ca->getOld(x + 1, y - 1)->u) / 2.0) * ((ca->getOld(x, y)->v - ca->getOld(x + 1, y - 1)->v) / 2.0); // this line is fishy
		A -= ((ca->getOld(x, y)->u - ca->getOld(x + 1, y + 1)->u) / 2.0) * ((ca->getOld(x, y)->v - ca->getOld(x + 1, y + 1)->v) / 2.0); // this line is fishy
		double B = 0.0;
		B += ((ca->getOld(x + 1, y)->u + ca->getOld(x + 2, y)->u) / 2.0);
		B += ((ca->getOld(x - 1, y)->u + ca->getOld(x, y)->u) / 2.0);
		B += ((ca->getOld(x, y + 1)->u + ca->getOld(x + 1, y + 1)->u) / 2.0);
		B += ((ca->getOld(x, y - 1)->u + ca->getOld(x + 1, y - 1)->u) / 2.0);
		B -= (4.0 * ((ca->getOld(x, y)->u + ca->getOld(x + 1, y)->u) / 2.0));
		double U = 0.0;
		U += (ca->getOld(x, y)->u + ca->getOld(x + 1, y)->u);
		U += dt * (A - WC_U * B + ca->getOld(x, y)->p - ca->getOld(x + 1, y)->p - WC_K * ((ca->getOld(x, y)->u - ca->getOld(x + 1, y)->u) / 2.0));
		//50% adds to my (x,y)->u, 50% adds to my next neighbor (x+y,y)->u
		ca->getNext(x, y)->u += U / 2.0;
		ca->getNext(x + 1, y)->u += U / 2.0;
	}
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