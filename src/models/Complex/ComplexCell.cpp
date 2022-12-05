/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/complex/ComplexCell.h"
#include "models/complex/ComplexPaper.h"
#include "models/Paper.h"
#include <iomanip>

void ComplexCell::doCalc(size_t cores, ComplexPaper* ca) {

	// 1.	: adjust velocities
	runAsync(cores, adjustVelocities, ca, true);
	ca->flip();
	runAsync(cores, copyVelocities, ca, true);
	// 2.	: MoveWater
	// 2.1.	: UpdateVelocities
	ca->calculatePaperMaxSpeed();
	ca->adjustDt();
	for (float t = 0.0; t < 1.0; t += ca->getDt())
	{
		runAsync(cores, updateVelocities, ca);
		// 2.1.1 : EnforceBoundaryConditions
		runAsync(cores, enforceBoundaryConditions, ca, true);
        ca->flip();
	}
	ca->flip();

	// 2.2.	: RelaxDivergence
	size_t n = 0;
	do
	{
		ca->div_max = 0.0;
		runAsync(cores, copyVelocities, ca, true);
		runAsync(cores, relaxDivergence, ca, true);
		std::cout << n << " : " << ca->div_max << "\n";
		ca->flip();
		n++;
	} while (!(ca->div_max <= REL_TOL || n > REL_MAX));

	// 2.3.	: FlowOutward
	//TODO
	// 3.	: MovePigment
	//TODO
	// 4.	: TransferPigment
	//TODO
	// 5.	: SimulateCapillaryFlow
	//TODO
	//printDebug(ca);
}

void ComplexCell::fixPaperHeight()
{
	c = this->h * (C_MAX - C_MIN) + C_MIN;
}

void ComplexCell::setHeightGradient(float new_hx, float new_hy)
{
	hx = new_hx;
	hy = new_hy;
}

void ComplexCell::addWater(float w)
{
	u = fRand(3.0, 3.4);
	v = fRand(-0.5, 0.8);
	m = true;
}

/// (u, v) = (u, v) - Nabla (h)
void ComplexCell::adjustVelocities(size_t x, size_t y, ComplexPaper* ca)
{
	ca->getNext(x, y)->u = ca->getOld(x, y)->u - ca->getOld(x, y)->hx;
	ca->getNext(x, y)->v = ca->getOld(x, y)->u - ca->getOld(x, y)->hy;
}

void ComplexCell::copyVelocities(size_t x, size_t y, ComplexPaper* ca)
{
	ca->getNext(x, y)->u = ca->getOld(x, y)->u;
	ca->getNext(x, y)->v = ca->getOld(x, y)->v;
}

// works with M, u, v, p
void ComplexCell::updateVelocities(size_t x, size_t y, ComplexPaper* ca)
{
	auto* cc = ca->getOld(x, y);
	auto* cu = ca->getOld(x, y + 1);
	auto* cd = ca->getOld(x, y - 1);
	auto* cr = ca->getOld(x + 1, y);
	auto* cl = ca->getOld(x - 1, y);

    float A,B;

	A = 0.0;
	A += pow((cc->u + cl->u) / 2.0, 2.0);
	A -= pow((cc->u + cr->u) / 2.0, 2.0);
	A += (cc->u + cd->u) * (cd->v + ca->getOld(x + 1, y - 1)->v) / 4.0;
	A -= (cc->u + cu->u) * (cc->v + cr->v) / 4.0;
	B = 0.0;
	B += cr->u;
	B += cl->u;
	B += cu->u;
	B += cd->u;
	B -= 4.0 * (cc->u);

	ca->getNext(x, y)->u += ca->getDt() * (A - WC_U * B + cc->p - cr->p - WC_K * cc->u);
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

	ca->getNext(x, y)->v += ca->getDt() * (A - WC_U * B + cc->p - cu->p - WC_K * cc->v);
}

void ComplexCell::enforceBoundaryConditions(size_t x, size_t y, ComplexPaper* ca)
{
	if (!ca->getNext(x, y)->m)
	{
		ca->getNext(x, y)->u = 0.0;
		ca->getNext(x, y)->v = 0.0;
		return;
	}
}

// works with M, u, v, p
void ComplexCell::relaxDivergence(size_t x, size_t y, ComplexPaper* ca)
{
	auto* o_cc = ca->getOld(x, y);
	auto* o_cd = ca->getOld(x, y - 1) ? ca->getOld(x, y - 1) : o_cc;
	auto* o_cl = ca->getOld(x - 1, y) ? ca->getOld(x - 1, y) : o_cc;
	
	auto* n_cc = ca->getNext(x, y);
	auto* n_cd = ca->getNext(x, y - 1) ? ca->getNext(x, y - 1) : n_cc;
	auto* n_cl = ca->getNext(x - 1, y) ? ca->getNext(x - 1, y) : n_cc;
	
	float div = 0.0;
	div -= o_cc->u;
	div += o_cl->u;
	div -= o_cc->v;
	div += o_cd->v;
	div *= REL_DAMP;

	n_cc->p = o_cc->p + div;

	n_cc->u += div;
	n_cl->u -= div;
	n_cc->v += div;
	n_cd->v -= div;

	ca->div_max = Tmax(ca->div_max, abs(div));
}

// works with M, p
void ComplexCell::flowOutward()
{

}

const Color ComplexCell::draw(Color base) const
{
    float b = m ? 0 : 1;
	return Color({ 1/(p+1), 1, b, 1.0 });
}
