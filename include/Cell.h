/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once
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
private:
};