/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file World.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <math.h>
#include "MagicConstants.h"

 // define enum for paper types
enum class PaperType
{
	DEFAULT, //Plain paper-like surface
	SBSK, //Southern Bleached Softwood Kraft
	SBHK, //Southern Bleached Hardwood Kraft
	CF //Cotton Fabric
};
using namespace std;

template <class Cell, size_t W, size_t H>
class World_T
{
public:
	World_T() {};
	~World_T() {};

	std::array<Cell, W * H> getData() {
		return cells;
	};
	
	Cell* getSafe(long long int x, long long int y) {
		// make sure the cell is always in the scope by applying positive modulo formula
		return &cells[(x % W + W) % W + (y % H + H) % H * W];
	};

	Cell* get(size_t x, size_t y) {
		return &cells[x + y * W];
	};

	static constexpr size_t aproxSize() {
		return W * H * Cell::aproxSize();
	}

	void setPaperType(PaperType type) {
		switch (type)
		{
		case PaperType::DEFAULT:
			setPaperPlane();
			break;
		case PaperType::SBSK:
			setPaperPlane();
			addFibres(SBSK);
			break;
		case PaperType::SBHK:
			break;
		case PaperType::CF:
			break;
		default:
			break;
		}
	}
private:
	void setPaperPlane(size_t newB = DEFAULT_B, size_t newC = DEFAULT_C) {
		for (auto& c : cells) {
			c.B = newB;
			c.C = newC;
		}
	}
	void addFibres(const Paper paper) {

		for (size_t i = 0; i < W * H / paper.FIBER_INVERSE_DENSITY; i++)
		{
			//draw a random line from the selected cell of length FIBER_LEN and get all cells the line crosses using Bresenham's algorithm
			long long int x1 = rand() % W;
			long long int y1 = rand() % H;

			//the second point will be exactly FIBER_LEN away from the first
			double angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 360));
			long long int x2 = x1 + paper.FIBER_LEN * cos(angle);
			long long int y2 = y1 + paper.FIBER_LEN * sin(angle);

			signed short dx = abs(x2 - x1);
			signed short dy = abs(y2 - y1);
			signed char sx = x1 < x2 ? 1 : -1;
			signed char sy = y1 < y2 ? 1 : -1;
			signed short err = (dx > dy ? dx : -dy) / 2;
			signed short e2;

			while (true)
			{
				Cell* cell = getSafe(x1, y1);
				cell->B += 10;
				cell->C = cell->C > 10 ? cell->C - 10 : 0;

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
private:
	array<Cell, W*H> cells;
};

#endif