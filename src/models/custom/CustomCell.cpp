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

void CustomCell::doCalc(size_t cores, CustomPaper *ca) {
    runAsync(cores, activateNearby, ca);
    runAsync(cores, absorbWater, ca, true);
    runAsync(cores, spreadWater, ca);
    runAsync(cores, flowWater, ca);

    runAsync(cores, vaporizeWater, ca);
    ca->flip();
}

void CustomCell::activateNearby(size_t x, size_t y, CustomPaper *ca) {
    const auto *old_cell = ca->getOld(x, y);
    if (!old_cell->active) {
        return;
    }
    ca->getNext(x + 1, y)->active = true;
    ca->getNext(x, y + 1)->active = true;
    ca->getNext(x - 1, y)->active = true;
    ca->getNext(x, y - 1)->active = true;
}

void CustomCell::absorbWater(size_t x, size_t y, CustomPaper *ca) {
    auto future_cell = ca->getNext(x, y);
    if (!future_cell->active) {
        return;
    }

    const auto *cell = ca->getOld(x, y);
    const float ABSORB_COEF = 0.01 + cell->water / 50;

    float water_to_absorbe = 0;
    if (cell->absorbed_water < cell->phobia) {
        water_to_absorbe =
                Tmin(0.05 * std::sin(M_PI * 0.5 * (cell->absorbed_water / cell->h)) + 0.001, cell->water) * ABSORB_COEF;
    } else {
        water_to_absorbe =
                Tmin(0.05 * std::sin(M_PI * 0.5 * ((cell->h - cell->absorbed_water) / cell->h)) + 0.001, cell->water) *
                ABSORB_COEF;
    }

    future_cell->water = cell->water - water_to_absorbe;
    future_cell->absorbed_water = cell->absorbed_water + water_to_absorbe;
}

void CustomCell::spreadWater(size_t x, size_t y, CustomPaper *ca) {
    auto future_cell = ca->getNext(x, y);
    if (!future_cell->active) {
        return;
    }

    const float TRANSFER_COEF = 0.1;
    const auto *cell = ca->getOld(x, y);
    const auto *cell_r = ca->getOld(x + 1, y);
    const auto *cell_u = ca->getOld(x, y + 1);
    const auto *cell_l = ca->getOld(x - 1, y);
    const auto *cell_d = ca->getOld(x, y - 1);

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

void CustomCell::flowWater(size_t x, size_t y, CustomPaper *ca) {
    const float SPREAD_C = (sqrt(2.0) - 1) / 4.0;
    auto future_cell = ca->getNext(x, y);
    if (!future_cell->active) {
        return;
    }

    const float FLOW_COEF = 0.25;
    const auto *cell = ca->getOld(x, y);
    const auto *cell_r = ca->getOld(x + 1, y);
    const auto *cell_u = ca->getOld(x, y + 1);
    const auto *cell_l = ca->getOld(x - 1, y);
    const auto *cell_d = ca->getOld(x, y - 1);

    float flow_r = (cell->water - cell_r->water) / 2.0 * FLOW_COEF * (1 + (cell->phobia - cell_r->phobia));
    float flow_u = (cell->water - cell_u->water) / 2.0 * FLOW_COEF * (1 + (cell->phobia - cell_u->phobia));
    float flow_l = (cell->water - cell_l->water) / 2.0 * FLOW_COEF * (1 + (cell->phobia - cell_l->phobia));
    float flow_d = (cell->water - cell_d->water) / 2.0 * FLOW_COEF * (1 + (cell->phobia - cell_d->phobia));

    future_cell->water -= (flow_r + flow_u + flow_l + flow_d);
}

void CustomCell::vaporizeWater(size_t x, size_t y, CustomPaper *ca) {
    auto future_cell = ca->getNext(x, y);
    if (!future_cell->active) {
        return;
    }

    float to_vaporize = 0.0001;

    if (future_cell->water > to_vaporize) {
        future_cell->water -= to_vaporize;
        to_vaporize = 0;
    } else {
        to_vaporize -= future_cell->water;
        future_cell->water = 0;
    }

    to_vaporize *= 0.01;

    // slow evaporation of stored water
    if (future_cell->absorbed_water > to_vaporize) {
        future_cell->absorbed_water -= to_vaporize;
    } else {
        future_cell->absorbed_water = 0;
    }
}

const Color CustomCell::draw(Color base) const {
    Color r = base;
    Color ph = Color({0.8, 0.12, 0.0, phobia});
    r = BitMapWriter::mixColors(r, ph);

    Color wa = Color({0, 0.5, 1.0, Tmax(Tmin(water * 1.0f, 1.0), 0.0)});
    r = BitMapWriter::mixColors(r, wa);

    Color ab = Color({0.0, 0.8, 0.0, absorbed_water});
    r = BitMapWriter::mixColors(r, ab);
    return r;
}
