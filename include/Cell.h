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
public:
private:
public:
	size_t W = 0; //water particles
	size_t I = 0; //ink particles
	size_t B = DEFAULT_B; //height of bottom (water capacity)
	size_t C = DEFAULT_C; //capacity of water captured to cells
private:
};