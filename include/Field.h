/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file Field.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once
#include <string>
#include <array>

#include "Cell.h"
#include <util.h>

#define WIDTH 100
#define HEIGHT 100

class Field
{
public:
	Field();
	~Field();
private:
	void generatePaper();
private:
	const size_t width = WIDTH;
	const size_t height = HEIGHT;
	
	std::array<Cell,WIDTH*HEIGHT> cells;
};