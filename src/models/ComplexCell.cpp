/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/ComplexCell.h"
#include "models/Paper.h"
#include <iomanip>

inline int Tmax(int a, int b) { return a > b ? a : b; };
inline double Tmax(double a, double b) { return a > b ? a : b; };
inline int Tmin(int a, int b) { return a < b ? a : b; };
inline double Tmin(double a, double b) { return a < b ? a : b; };

template<class T>
void printDebug(T* ca) {
	std::cout << "[u, v]: \n" << std::setprecision(2) << std::fixed;
	for (size_t y = 0; y < ca->HEIGHT; y++) {
		for (size_t x = 0; x < ca->WIDTH; x++) {
			std::cout << "[" << ca->getNext(x, y)->u << ", " << ca->getNext(x, y)->v << "] ";
		}
		std::cout << "\n";
	}
}

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

template<class T>
void ComplexCell::doCalc(size_t cores, T* tca) {
	Paper* ca = static_cast<Paper*>(tca);

	// 1.	: adjust velocities
	Cell_T::runAsync(cores, adjustVelocities<T>, ca, true);
	ca->flip();
	Cell_T::runAsync(cores, copyVelocities<T>, ca, true);
	// 2.	: MoveWater
	// 2.1.	: UpdateVelocities
	ca->calculatePaperMaxSpeed();
	ca->adjustDt();
	for (double t = 0.0; t < 1.0; t += ca->getDt())
	{
		Cell_T::runAsync(cores, updateVelocities<T>, ca);
	}
	printDebug(ca);
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

void ComplexCell::addWater()
{
	u = fRand(3.0, 3.4);
	v = fRand(-0.5, 0.8);
	m = true;
}

template<class T>
/// (u, v) = (u, v) - Nabla (h)
void ComplexCell::adjustVelocities(size_t x, size_t y, T* tca)
{
	Paper* ca = static_cast<Paper*>(tca);
	ca->getNext(x, y)->u = ca->getOld(x, y)->u - ca->getOld(x, y)->hx;
	ca->getNext(x, y)->v = ca->getOld(x, y)->u - ca->getOld(x, y)->hy;
}

template<class T>
void ComplexCell::copyVelocities(size_t x, size_t y, T* tca)
{
	Paper* ca = static_cast<Paper*>(tca);
	ca->getNext(x, y)->u = ca->getOld(x, y)->u;
	ca->getNext(x, y)->v = ca->getOld(x, y)->v;
}

// works with M, u, v, p
template<class T>
void ComplexCell::updateVelocities(size_t x, size_t y, T* tca)
{
	Paper* ca = static_cast<Paper*>(tca); // 0.5index as own value
	auto* cc = ca->getOld(x, y);
	auto* cu = ca->getOld(x, y + 1);
	auto* cd = ca->getOld(x, y - 1);
	auto* cr = ca->getOld(x + 1, y);
	auto* cl = ca->getOld(x - 1, y);

	double A = 0.0;
	A += pow((cc->u + cl->u) / 2.0, 2.0);
	A -= pow((cc->u + cr->u) / 2.0, 2.0);
	A += (cc->u + cd->u) * (cd->v + ca->getOld(x + 1, y - 1)->v) / 4.0;
	A -= (cc->u + cu->u) * (cc->v + cr->v) / 4.0;
	double B = 0.0;
	B += cr->u;
	B += cl->u;
	B += cu->u;
	B += cd->u;
	B -= 4.0 * (cc->u);
	//auto calc = cc->u + ca->getDt() * (A - WC_U * B + cc->p - cr->p - WC_K * cc->u);
	ca->getNext(x, y)->u = cc->u + ca->getDt() * (A - WC_U * B + cc->p - cr->p - WC_K * cc->u);
	/* ------ */

	A = 0.0;
	A += pow((cc->v + cd->v) / 2.0, 2.0);
	A -= pow((cc->v + cu->v) / 2.0, 2.0);
	A += (cc->v + cl->v) * (cl->u + ca->getOld(x - 1, y + 1)->u) / 4.0;
	A -= (cc->v + cr->v) * (cc->u + cu->u) / 4.0;
	B = 0.0;
	B += cr->v;
	B += cl->v;
	B += cu->v;
	B += cd->v;
	B -= 4.0 * (cc->v);

	ca->getNext(x, y)->v = cc->v + ca->getDt() * (A - WC_U * B + cc->p - cu->p - WC_K * cc->v);
	/*
	Paper* ca = static_cast<Paper*>(tca); // try fixing with 0.5index as "own" value
	double A = 0.0;
	A += pow(ca->getOld(x, y)->u, 2);
	A -= pow(cr->u, 2);
	A += ((ca->getOld(x, y)->u + ca->getOld(x + 1, y - 1)->u) / 2.0) * ((ca->getOld(x, y)->v + ca->getOld(x + 1, y - 1)->v) / 2.0); // this line is fishy
	A -= ((ca->getOld(x, y)->u + ca->getOld(x + 1, y + 1)->u) / 2.0) * ((ca->getOld(x, y)->v + ca->getOld(x + 1, y + 1)->v) / 2.0); // this line is fishy
	double B = 0.0;
	B += ((cr->u + ca->getOld(x + 2, y)->u) / 2.0);
	B += ((cl->u + ca->getOld(x, y)->u) / 2.0);
	B += ((cu->u + ca->getOld(x + 1, y + 1)->u) / 2.0);
	B += ((cd->u + ca->getOld(x + 1, y - 1)->u) / 2.0);
	B -= (4.0 * ((ca->getOld(x, y)->u + cr->u) / 2.0));
	double val = 0.0;
	val += ((ca->getOld(x, y)->u + cr->u) / 2.0);
	val += ca->getDt() * (A - WC_U * B + ca->getOld(x, y)->p - cr->p - WC_K * ((ca->getOld(x, y)->u - cr->u) / 2.0));
	//50% adds to my (x,y)->u, 50% adds to my next neighbor (x+1,y)->u

	// enforceBoundaryConditions();
	if (ca->getOld(x, y)->m)
		ca->getNext(x, y)->u += val / 2.0;
	else
		ca->getNext(x, y)->u = 0.0;

	// enforceBoundaryConditions();
	if (ca->getOld(x, y)->m)
		ca->getNext((x + 1), y)->u += val / 2.0;
	else
		ca->getNext((x + 1), y)->u = 0.0;

	A = 0.0;
	A += pow(ca->getOld(x, y)->v, 2);
	A -= pow(cu->v, 2);
	A += ((ca->getOld(x, y)->u + ca->getOld(x - 1, y + 1)->u) / 2.0) * ((ca->getOld(x, y)->v + ca->getOld(x - 1, y + 1)->v) / 2.0); // this line is fishy
	A -= ((ca->getOld(x, y)->u + ca->getOld(x + 1, y + 1)->u) / 2.0) * ((ca->getOld(x, y)->v + ca->getOld(x + 1, y + 1)->v) / 2.0); // this line is fishy
	B = 0.0;
	B += ((cr->v + ca->getOld(x + 1, y + 1)->v) / 2.0);
	B += ((cl->v + ca->getOld(x - 1, y + 1)->v) / 2.0);
	B += ((cu->v + ca->getOld(x + 1, y + 2)->v) / 2.0);
	B += ((ca->getOld(x, y)->v + cd->v) / 2.0);
	B -= (4.0 * ((ca->getOld(x, y)->v + cu->v) / 2.0));
	val = 0.0;
	val += ((ca->getOld(x, y)->v + cu->v) / 2.0);
	val += ca->getDt() * (A - WC_U * B + ca->getOld(x, y)->p - cu->p - WC_K * ((ca->getOld(x, y)->v - cu->v) / 2.0));
	//50% adds to my (x,y)->v, 50% adds to my next neighbor (x,y+1)->v

	// enforceBoundaryConditions();
	if (ca->getOld(x, y)->m)
		ca->getNext(x, y)->v += val / 2.0;
	else
		ca->getNext(x, y)->v = 0.0;

	// enforceBoundaryConditions();
	if (ca->getOld(x, y)->m)
		ca->getNext(x, (y + 1))->v += val / 2.0;
	else
		ca->getNext(x, (y + 1))->v = 0.0;*/
}

// works with M, u, v, p
template<class T>
void ComplexCell::relaxDivergence(size_t x, size_t y, T* tca)
{
	Paper* ca = static_cast<Paper*>(tca);
	auto* cc = ca->getOld(x, y);
	auto* cu = ca->getOld(x, y + 1);
	auto* cd = ca->getOld(x, y - 1);
	auto* cr = ca->getOld(x + 1, y);
	auto* cl = ca->getOld(x - 1, y);
	double div = 0.0;
	div += (ca->getOld(x, y)->u + ca->getOld(x + 1, y)->u) / 2.0;
	div -= (ca->getOld(x, y)->u + ca->getOld(x - 1, y)->u) / 2.0;
	div += (ca->getOld(x, y)->v + ca->getOld(x, y + 1)->v) / 2.0;
	div -= (ca->getOld(x, y)->v + ca->getOld(x, y - 1)->v) / 2.0;
	div *= REL_DAMP;

	ca->getNext(x, y)->p += div;

	if (isinf(ca->getNext(x, y)->p))
	{
		std::cout << "Bruh";
	}

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
	if (p > 1)
		std::cout << p << "\n";
	return Color({ 1.0 - p, 0, 0, 1.0 });
}

//needed for proper linking
namespace COMPLEXCELL {
	void Linking() {
		Paper ca;
		Paper::WorldUnit::doCalc<Paper>(0, &ca);
		exit(EXIT_FAILURE);
	}
}