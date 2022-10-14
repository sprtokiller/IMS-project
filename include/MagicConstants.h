/**
 * @brief Constants defining the particle behavior
 *
 * @file MagicConstants.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once

#define um *1
#define mm *1000
#define cm *1000*10
#define m  *1000*1000

constexpr uint CELL_SIZE = 20 um;
constexpr uint FIBER_LEN = 3 cm / CELL_SIZE;
constexpr uint DEFAULT_B = 100 um;
constexpr uint DEFAULT_C = 100 um;
// for every 50 cells, generate a random fiber
constexpr uint C_PER_FIBER = 50;

#undef um
#undef mm
#undef cm
#undef m