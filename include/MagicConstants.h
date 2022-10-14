/**
 * @brief Constants defining the particle behavior
 *
 * @file MagicConstants.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef MAGICCONSTANTS_H
#define MAGICCONSTANTS_H

#define um *1
#define mm *1000
#define cm *1000*10
#define m  *1000*1000

struct Paper {
	uint FIBER_LEN;
	uint FIBER_DENSITY;
};

constexpr uint CELL_SIZE = 20 um;

constexpr Paper SBSK = { 30 mm / CELL_SIZE, 50 };
constexpr Paper SBHK = { 15 mm / CELL_SIZE, 50 };

constexpr uint DEFAULT_B = 100 um;
constexpr uint DEFAULT_C = 100 um;

#undef um
#undef mm
#undef cm
#undef m

#endif