/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file Cell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include <math.h>

#include "Field.h"
#include "MagicConstants.h"

Field::Field(size_t w, size_t h) : width(w), height(h)
{
	cells = std::vector<Cell>(w * h);
	generatePaper();
}

Field::~Field()
{
}

void Field::generatePaper()
{
	for (size_t i = 0; i < width * height * FIBERS_PER_CELL; i++)
	{
		//draw a random line from the selected cell of length FIBER_LEN and get all cells the line crosses using Bresenham's algorithm
		size_t x1 = rand() % width;
		size_t y1 = rand() % height;

		//the second point will be exactly FIBER_LEN away from the first
		double angle = rand() % 360;
		size_t x2 = x1 + FIBER_LEN * cos(angle);
		size_t y2 = y1 + FIBER_LEN * sin(angle);
		
		size_t dx = abs(static_cast<int>(x2 - x1));
		size_t dy = abs(static_cast<int>(y2 - y1));
		size_t sx = x1 < x2 ? 1 : -1;
		size_t sy = y1 < y2 ? 1 : -1;
		size_t err = (dx > dy ? dx : -dy) / 2;
		size_t e2;
		
		while (true)
		{
			//get cell at (x1, y1)
			Cell& cell = cells[y1 * width + x1];
			cell.B += FIBER_LEN;
			cell.C += FIBER_LEN;

			if (x1 == x2 && y1 == y2)
				break;

			e2 = err;
			if (e2 > -dx)
			{
				err -= dy;
				x1 += sx;
			}
			if (e2 < dy)
			{
				err += dx;
				y1 += sy;
			}
		}

		
	}
}
