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
#include "template/CAutomata.h"

class Cell : public Cell_T
{
public:
	using CA = CAutomata_T<Cell>;

	void virtual addWater(float w) = 0;
	void virtual addInk() = 0;
	void virtual setHydrophobic(float ph) = 0;
public://TODO @vita remove public
	float h = 0; //paper "structure"
};

#endif // !PAPERCELL_H