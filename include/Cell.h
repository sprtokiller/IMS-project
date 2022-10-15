/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef CELL_H
#define CELL_H

#include <vector>
#include "MagicConstants.h"

class Cell
{
public:
	Cell() {};
	~Cell() {};
	
	static constexpr size_t aproxSize() {
		return sizeof(Cell);
	}
public:
	uint W = 0; //water particles
	uint I = 0; //ink particles
	uint B = DEFAULT_B; //height of bottom (water capacity)
	uint C = DEFAULT_C; //capacity of water captured to cells
	//publikace 2
	float u = 0; //velocity in x direction
	float v = 0; //velocity in y direction
private:
};

#endif