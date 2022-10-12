/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "Field.h"

Field::Field(size_t w, size_t h) : width(w), height(h)
{
	cells = std::vector<Cell>(w * h);
	generatePaper();
}

Field::~Field()
{
}

void Field::generatePaper()
{
}
