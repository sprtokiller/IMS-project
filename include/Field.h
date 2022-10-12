/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file Field.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once
#include <string>
#include <vector>

#include "Cell.h"

class Field
{
public:
	Field(size_t w, size_t h);
	~Field();

private:
	const size_t width;
	const size_t height;
	std::vector<Cell> cells;
};