/**
 * @brief CustomCell class, with our final custom implementation
 *
 * @file CustomCell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/custom/CustomCell.h"
#include "models/custom/CustomPaper.h"
#include <iomanip>
#include <output/BitMapWriter.h>

void CustomCell::doCalc(size_t cores, CustomPaper* ca) {
	runAsync(cores, spreadWater, ca, true);
	ca->flip();
}

void CustomCell::spreadWater(size_t x, size_t y, CustomPaper* ca) {
	
	const auto* cell = ca->getOld(x, y);
	auto future_cell = ca->getNext(x, y);
	
	float water_to_absorb = 0.0;
	/*
	if (cell->absorbed_water < 1)
	{
		float water_to_absorb = Tmin(1 - cell->absorbed_water) * 0.01 * cell->water, 0);
	}
	future_cell->absorbed_water = cell->absorbed_water + water_to_absorb;
	future_cell->water = cell->water - water_to_absorb;*/
}

void CustomCell::fixPaperHeight()
{
	//c = h * (C_MAX - C_MIN) + C_MIN;
}

void CustomCell::setHeightGradient(float new_hx, float new_hy)
{
	//hx = new_hx;
	//hy = new_hy;
}

const Color CustomCell::draw(Color base) const
{
	Color r = base;
	Color ph = Color({ 0.8, 0.12, 0.0, phobia });
	r = BitMapWriter::mixColors(r, ph);
	
	Color wa = Color({ 0, 0.5, 1.0, Tmax(Tmin(water, 1.0), 0.0) });
	r = BitMapWriter::mixColors(r, wa);

	Color ab = Color({ 0.8, 0.0, 0.0, absorbed_water });
	r = BitMapWriter::mixColors(r, ab);
	return r;
}
