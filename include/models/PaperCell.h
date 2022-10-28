﻿/**
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
#include "models/PaperMath.h"

class Cell : public Cell_T
{
public:
	using CA = CAutomata_T<Cell>;

	virtual const Color draw(Color base) const = 0;

	float h = 0; //paper "structure"
};

#endif // !PAPERCELL_H