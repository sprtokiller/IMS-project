/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/ComplexCell.h"
#include "models/Paper.h"

inline int Tmax(int a, int b) { return a > b ? a : b; };
inline double Tmax(double a, double b) { return a > b ? a : b; };
inline int Tmin(int a, int b) { return a < b ? a : b; };
inline double Tmin(double a, double b) { return a < b ? a : b; };

template<class T>
void ComplexCell::doCalc(size_t cores, T* ca) {
	// 1.	: clear velocities
	Cell_T::runAsync(cores, clearVelocities<T>, ca, true);
	// 2.	: MoveWater
	// 2.1.	: UpdateVelocities
	Cell_T::runAsync(cores, updateVelocities<T>, ca);
	// 2.2.	: RelaxDivergence
	ca->div_max = 0.0;
	size_t n = 0;
	while (ca->div_max <= REL_TOL && n < REL_MAX)
	{
		n++;
		Cell_T::runAsync(cores, relaxDivergence<T>, ca);
	}
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
template<class T>
void ComplexCell::relaxDivergence(size_t x, size_t y, T* tca)
{
	Paper* ca = static_cast<Paper*>(tca);
	double div = 0.0;
	div += (ca->getOld(x, y)->u + ca->getOld(x + 1, y)->u) / 2.0;
	div -= (ca->getOld(x, y)->u + ca->getOld(x - 1, y)->u) / 2.0;
	div += (ca->getOld(x, y)->v + ca->getOld(x, y + 1)->v) / 2.0;
	div -= (ca->getOld(x, y)->v + ca->getOld(x, y - 1)->v) / 2.0;
	div *= REL_DAMP;

	ca->getNext(x, y)->p += div;
	
	ca->getNext(x + 1, y)->u += (div / 2.0);
	ca->getNext(x - 1, y)->u -= (div / 2.0);
	ca->getNext(x, y + 1)->v += (div / 2.0);
	ca->getNext(x, y - 1)->v -= (div / 2.0);

	ca->div_max = Tmax(ca->div_max, abs(div));
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
namespace COMPLEXCELL {
	void Linking() {
		Paper ca;
		Paper::WorldUnit::doCalc<Paper>(0, &ca);
		exit(EXIT_FAILURE);
	}
}