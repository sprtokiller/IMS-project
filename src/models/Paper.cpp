/**
 * @brief Constants defining the particle behavior
 *
 * @file MagicConstants.h
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/Paper.h"

Paper::Paper()
{
}

Paper::~Paper()
{
}

void Paper::setPaperType(PaperType type) {
	if (type & PaperType::PLAIN)
		setPaperPlane();

	if (type & PaperType::NOISE)
		setNoise();
	
	if (type & PaperType::SBSK)
		addFibres(SBSK);

	if (type & PaperType::SBHK)
		addFibres(SBHK);
}

void Paper::makeWaterStroke()
{
	for (size_t x = WATER_BRUSH_START_X; x < WATER_BRUSH_END_X; x++)
	{
		for (size_t y = WATER_BRUSH_START_Y; y < WATER_BRUSH_END_Y; y++)
		{
			getNext(x, y)->addWater();
		}
	}
}

void Paper::makeInkStroke()
{
	for (size_t x = INK_BRUSH_START_X; x < INK_BRUSH_END_X; x++)
	{
		for (size_t y = INK_BRUSH_START_Y; y < INK_BRUSH_END_Y; y++)
		{
			getNext(x, y)->addInk();
		}
	}	mirror();
}

void Paper::calculateMaxSpeed()
{
	maxSpeed = -1.0;
	for (auto u : getOld()) {
		if (u.getMaxSpeed() > maxSpeed) maxSpeed = u.getMaxSpeed();
	}
}



void Paper::setPaperPlane(size_t newB, size_t newC) {
	for (size_t x = 0; x < WIDTH; x++)
		for (size_t y = 0; y < HEIGHT; y++) {
			auto cell = getNext(x, y);
			//cell->B = newB;
			//cell->C = newC;
		}
}

void Paper::setNoise() {
	PerlinNoise pn;
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		double x = (double)(i % WIDTH) / ((double)WIDTH);
		double y = (double)(i / WIDTH) / ((double)HEIGHT);

		// Typical Perlin noise
		double n = pn.noise(CELL_SIZE * 10 * x, CELL_SIZE * 10 * y, 0.42);

		auto cell = getNext(i);
		if (cell)
		{
			cell->h = n;
		}
	}
}

void Paper::addFibres(const PAPER paper) {
	for (size_t i = 0; i < WIDTH * HEIGHT / paper.FIBER_INVERSE_DENSITY; i++)
	{
		//draw a random line from the selected cell of length FIBER_LEN and get all cells the line crosses using Bresenham's algorithm
		long long int x1 = rand() % WIDTH;
		long long int y1 = rand() % HEIGHT;

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
			Cell* cell = getNext(x1, y1);
			if (cell)
			{
				if (i % 30 == 0)
				{
					cell->h += 0.6;
				}
				else
				{
					cell->h += 0.2;
				}
			}

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

	normalize();
}

void Paper::normalize()
{
	double max = -1;

	for (auto &c : getNext()) {
		if (max < c.h)
		{
			max = c.h;
		}
	}
	for (auto &c : getNext()) {
		c.h = c.h / max;
		c.fixPaperHeight();
	}

	for (size_t x = 1; x < DEFAULT_WIDTH - 1; x++)
	{
		for (size_t y = 1; y < DEFAULT_HEIGHT - 1; y++)
		{
			double hx = (getNext(x + 1, y)->h - getNext(x - 1, y)->h) / 2;
			double hy = (getNext(x, y + 1)->h - getNext(x, y - 1)->h) / 2;
			getNext(x, y)->setHeightGradient(hx, hy);
		}
	}	
}
 