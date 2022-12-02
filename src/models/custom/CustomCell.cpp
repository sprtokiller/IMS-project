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
	runAsync(cores, absorbWater, ca, true);
	runAsync(cores, spreadWater, ca);
	ca->flip();
}

void CustomCell::absorbWater(size_t x, size_t y, CustomPaper* ca) {

	const auto* cell = ca->getOld(x, y);
	auto future_cell = ca->getNext(x, y);

	float water_to_absorbe = 0;
	if (cell->absorbed_water < cell->phobia) {
		water_to_absorbe = Tmin(0.05 * std::sin(M_PI * 0.5 * (cell->absorbed_water / cell->h)) + 0.001, cell->water) * 0.1;
	}
	else {
		water_to_absorbe = Tmin(0.05 * std::sin(M_PI * 0.5 * ((cell->h - cell->absorbed_water) / cell->h)) + 0.001, cell->water) * 0.1;
	}
	
	future_cell->water = cell->water - water_to_absorbe;
	future_cell->absorbed_water = cell->absorbed_water + water_to_absorbe;
}

void CustomCell::spreadWater(size_t x, size_t y, CustomPaper* ca) {
	
	const auto* cell = ca->getOld(x, y);
	const auto* cell_r = ca->getOld(x + 1, y);
	const auto* cell_d = ca->getOld(x, y + 1);

	auto future_cell = ca->getNext(x, y);
	
	float own_saturation = cell->absorbed_water / cell->h;
	float right_saturation = cell_r->absorbed_water / cell_r->h;

	//if (x == 1200 && y == 1200) {
 //		std::cout << "own_saturation: " << own_saturation * 100 << "%, which is " << cell->absorbed_water << "\n";
	//	std::cout << "right_saturation: " << right_saturation * 100 << "%, which is " << cell_r->absorbed_water << "\n";
	//	std::cout << "diff: " << (own_saturation - right_saturation) * 100 / 2 * 0.1 << "\n";
	//	std::cout << "\n";
	//}
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
	
	//Color wa = Color({ 0, 0.5, 1.0, Tmax(Tmin(water * 0.25f, 1.0), 0.0) });
	//r = BitMapWriter::mixColors(r, wa);

	Color ab = Color({ 0.0, 0.8, 0.0, absorbed_water });
	r = BitMapWriter::mixColors(r, ab);
	return r;
}
