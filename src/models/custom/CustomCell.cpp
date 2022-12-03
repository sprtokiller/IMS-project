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
	runAsync(cores, flowWater, ca);
	ca->flip();
}

void CustomCell::absorbWater(size_t x, size_t y, CustomPaper* ca) {
	auto future_cell = ca->getNext(x, y);
	if (!future_cell->active)
	{
		return;
	}

	const float ABSORB_COEF = 0.01;
	const auto* cell = ca->getOld(x, y);
	
	float water_to_absorbe = 0;
	if (cell->absorbed_water < cell->phobia) {
		water_to_absorbe = Tmin(0.05 * std::sin(M_PI * 0.5 * (cell->absorbed_water / cell->h)) + 0.001, cell->water) * ABSORB_COEF;
	}
	else {
		water_to_absorbe = Tmin(0.05 * std::sin(M_PI * 0.5 * ((cell->h - cell->absorbed_water) / cell->h)) + 0.001, cell->water) * ABSORB_COEF;
	}
	
	future_cell->water = cell->water - water_to_absorbe;
	future_cell->absorbed_water = cell->absorbed_water + water_to_absorbe;
}

void CustomCell::spreadWater(size_t x, size_t y, CustomPaper* ca) {
	auto future_cell = ca->getNext(x, y);
	if (!future_cell->active)
	{
		return;
	}

	const float TRANSFER_COEF = 0.1;
	const auto* cell = ca->getOld(x, y);
	const auto* cell_r = ca->getOld(x + 1, y);
	const auto* cell_u = ca->getOld(x, y + 1);
	const auto* cell_l = ca->getOld(x - 1, y);
	const auto* cell_d = ca->getOld(x, y - 1);

	float own_saturation = cell->absorbed_water / cell->h;
	float r_satuaration = cell_r->absorbed_water / cell_r->h;
	float u_satuaration = cell_u->absorbed_water / cell_u->h;
	float l_satuaration = cell_l->absorbed_water / cell_l->h;
	float d_satuaration = cell_d->absorbed_water / cell_d->h;

	float combined_r_saturation = (own_saturation + r_satuaration) / 2;
	float combined_u_saturation = (own_saturation + u_satuaration) / 2;
	float combined_l_saturation = (own_saturation + l_satuaration) / 2;
	float combined_d_saturation = (own_saturation + d_satuaration) / 2;

	float spread_r = (combined_r_saturation - r_satuaration) * cell->h;
	float spread_u = (combined_u_saturation - u_satuaration) * cell->h;
	float spread_l = (combined_l_saturation - l_satuaration) * cell->h;
	float spread_d = (combined_d_saturation - d_satuaration) * cell->h;

	future_cell->absorbed_water -= (spread_r + spread_u + spread_l + spread_d) * TRANSFER_COEF;
}

void CustomCell::flowWater(size_t x, size_t y, CustomPaper* ca) {
	auto future_cell = ca->getNext(x, y);
	if (!future_cell->active)
	{
		return;
	}

	const float FLOW_COEF = 1;
	const auto* cell = ca->getOld(x, y);
	const auto* cell_r = ca->getOld(x + 1, y);
	const auto* cell_u = ca->getOld(x, y + 1);
	const auto* cell_l = ca->getOld(x - 1, y);
	const auto* cell_d = ca->getOld(x, y - 1);

	float flow_r = (cell->water - cell_r->water) * FLOW_COEF * (1 + (cell->phobia - cell_r->phobia)) / 4.0;
	float flow_u = (cell->water - cell_u->water) * FLOW_COEF * (1 + (cell->phobia - cell_u->phobia)) / 4.0;
	float flow_l = (cell->water - cell_l->water) * FLOW_COEF * (1 + (cell->phobia - cell_l->phobia)) / 4.0;
	float flow_d = (cell->water - cell_d->water) * FLOW_COEF * (1 + (cell->phobia - cell_d->phobia)) / 4.0;

	future_cell->water -= (flow_r + flow_u + flow_l + flow_d);
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
