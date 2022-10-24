/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef PAPERCELL_H
#define PAPERCELL_H

#include <vector>
#include "template/Cell.h"

class Cell : public Cell_T
{
public:
	void virtual addWater(double w) = 0;
	void virtual addInk() = 0;
	void virtual setHydrophobic(double ph) = 0;
public://TODO @vita remove public
	double h = 0; //paper "structure"
};

#endif // !PAPERCELL_H