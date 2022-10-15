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
#define mm um*1000
#define cm mm*10
#define m  mm*1000

struct Paper {
	uint FIBER_LEN;
	uint FIBER_INVERSE_DENSITY;
};

constexpr uint CELL_SIZE = 20 um;

constexpr Paper SBSK = { 30 mm / CELL_SIZE, 5 };
constexpr Paper SBHK = { 15 mm / CELL_SIZE, 5 };

constexpr uint DEFAULT_B = 10 mm; //100 um;
constexpr uint DEFAULT_C = 10 mm; //100 um;

constexpr size_t DEFAULT_WIDTH = 1 cm / CELL_SIZE;
constexpr size_t DEFAULT_HEIGHT = 1 cm / CELL_SIZE;

#undef um
#undef mm
#undef cm
#undef m

#endif