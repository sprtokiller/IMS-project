/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "Field.h"
#include "MagicConstants.h"

Field::Field(size_t w, size_t h) : width(w), height(h)
{
	cells = std::vector<Cell>(w * h, Cell(DEFAULT_B, DEFAULT_C));
	generatePaper();
}

Field::~Field()
{
}

void Field::generatePaper()
{
	
}
