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
void SimpleCell::doCalc(size_t cores, T* ca) {
	runAsync(cores, simpleFlow<T>, ca);
	ca->flip();
}

template<class T>
void SimpleCell::simpleFlow(size_t x, size_t y, T* ca) {
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

const Color SimpleCell::draw() const
{
	if (W > 0)
		return Color({0, 0, 1, 1});
	else
		return Color();
}

template<class T>
void ComplexCell::doCalc(size_t cores, T* ca) {
	// 1.	: clear velocities
	Cell_T::runAsync(cores, clearVelocities<T>, ca, true);
	// 2.	: MoveWater
	// 2.1.	: UpdateVelocities
	Cell_T::runAsync(cores, updateVelocities<T>, ca);
	// 2.2.	: RelaxDivergence
	//TODO
	// 2.3.	: FlowOutward
	//TODO
	// 3.	: MovePigment
	//TODO
	// 4.	: TransferPigment
	//TODO
	// 5.	: SimulateCapillaryFlow
	//TODO
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
void ComplexCell::clearVelocities(size_t x, size_t y, T* ca)
{
	ca->getNext(x, y)->u = 0;
	ca->getNext(x, y)->v = 0;
}

// works with M, u, v, p
template<class T>
void ComplexCell::updateVelocities(size_t x, size_t y, T* ca)
{
	ca->getNext(x, y)->u -= ca->getOld(x, y)->hx;
	ca->getNext(x, y)->v -= ca->getOld(x, y)->hy;
	
	double dt = 1 / ca->getMaxSpeed();
	for (double t = 0.0; t < 1.0; t += dt)
	{
		double A = 0.0;
		A += pow(ca->getOld(x, y)->u, 2);
		A -= pow(ca->getOld(x + 1, y)->u, 2);
		A += ((ca->getOld(x, y)->u + ca->getOld(x + 1, y - 1)->u) / 2.0) * ((ca->getOld(x, y)->v + ca->getOld(x + 1, y - 1)->v) / 2.0); // this line is fishy
		A -= ((ca->getOld(x, y)->u + ca->getOld(x + 1, y + 1)->u) / 2.0) * ((ca->getOld(x, y)->v + ca->getOld(x + 1, y + 1)->v) / 2.0); // this line is fishy
		double B = 0.0;
		B += ((ca->getOld(x + 1, y)->u + ca->getOld(x + 2, y)->u) / 2.0);
		B += ((ca->getOld(x - 1, y)->u + ca->getOld(x, y)->u) / 2.0);
		B += ((ca->getOld(x, y + 1)->u + ca->getOld(x + 1, y + 1)->u) / 2.0);
		B += ((ca->getOld(x, y - 1)->u + ca->getOld(x + 1, y - 1)->u) / 2.0);
		B -= (4.0 * ((ca->getOld(x, y)->u + ca->getOld(x + 1, y)->u) / 2.0));
		double val = 0.0;
		val += ((ca->getOld(x, y)->u + ca->getOld(x + 1, y)->u) / 2.0);
		val += dt * (A - WC_U * B + ca->getOld(x, y)->p - ca->getOld(x + 1, y)->p - WC_K * ((ca->getOld(x, y)->u - ca->getOld(x + 1, y)->u) / 2.0));
		//50% adds to my (x,y)->u, 50% adds to my next neighbor (x+1,y)->u

		// enforceBoundaryConditions();
		if (x > M_X1 && x < M_X2 && y > M_Y1 && y < M_Y2)
			ca->getNext(x, y)->u += val / 2.0;
		else
			ca->getNext(x, y)->u = 0.0;

		// enforceBoundaryConditions();
		if ((x + 1) > M_X1 && (x + 1) < M_X2 && y > M_Y1 && y < M_Y2)
			ca->getNext((x + 1), y)->u += val / 2.0;
		else
			ca->getNext((x + 1), y)->u = 0.0;

		/* ------ */
		A = 0.0;
		A += pow(ca->getOld(x, y)->v, 2);
		A -= pow(ca->getOld(x, y + 1)->v, 2);
		A += ((ca->getOld(x, y)->u + ca->getOld(x - 1, y + 1)->u) / 2.0) * ((ca->getOld(x, y)->v + ca->getOld(x - 1, y + 1)->v) / 2.0); // this line is fishy
		A -= ((ca->getOld(x, y)->u + ca->getOld(x + 1, y + 1)->u) / 2.0) * ((ca->getOld(x, y)->v + ca->getOld(x + 1, y + 1)->v) / 2.0); // this line is fishy
		B = 0.0;
		B += ((ca->getOld(x + 1, y)->v + ca->getOld(x + 1, y + 1)->v) / 2.0);
		B += ((ca->getOld(x - 1, y)->v + ca->getOld(x - 1, y + 1)->v) / 2.0);
		B += ((ca->getOld(x, y + 1)->v + ca->getOld(x + 1, y + 2)->v) / 2.0);
		B += ((ca->getOld(x, y)->v + ca->getOld(x, y - 1)->v) / 2.0);
		B -= (4.0 * ((ca->getOld(x, y)->v + ca->getOld(x, y + 1)->v) / 2.0));
		val = 0.0;
		val += ((ca->getOld(x, y)->v + ca->getOld(x, y + 1)->v) / 2.0);
		val += dt * (A - WC_U * B + ca->getOld(x, y)->p - ca->getOld(x, y + 1)->p - WC_K * ((ca->getOld(x, y)->v - ca->getOld(x, y + 1)->v) / 2.0));
		//50% adds to my (x,y)->v, 50% adds to my next neighbor (x,y+1)->v

		// enforceBoundaryConditions();
		if (x > M_X1 && x < M_X2 && y > M_Y1 && y < M_Y2)
			ca->getNext(x, y)->v += val / 2.0;
		else
			ca->getNext(x, y)->v = 0.0;

		// enforceBoundaryConditions();
		if (x > M_X1 && x < M_X2 && (y + 1) > M_Y1 && (y + 1) < M_Y2)
			ca->getNext(x, (y + 1))->v += val / 2.0;
		else
			ca->getNext(x, (y + 1))->v = 0.0;
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

const Color ComplexCell::draw() const
{
	return Color();
}

//needed for proper linking
namespace PAPERCELL {
	void Linking() {
		Paper::CAutomata ca;
		Paper::WorldUnit::doCalc<Paper::CAutomata>(0, &ca);
		exit(EXIT_FAILURE);
	}
}