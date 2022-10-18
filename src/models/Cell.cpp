/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "template/CAutomata.h"
#include "models/Cell.h"

void SimpleCell::fixPaperHeight()
{
	B += floor(h * 300);
	C -= floor(h * 300);
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