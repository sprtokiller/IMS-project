/**
 * @brief Constants defining the particle behavior
 *
 * @file MagicConstants.h
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/Paper.h"
#include <models/PaperCell.h>
#include <models/SimpleCell.h>

void Paper::setPaperType(PaperType type) {
	if (type & PaperType::PLAIN)
		setPaperPlane();

	if (type & PaperType::NOISE)
		setNoise();
	
	if (type & PaperType::SBSK)
		addFibres(SBSK);

	if (type & PaperType::SBHK)
		addFibres(SBHK);
	
	if (type & PaperType::HYDROPHOBIC)
		setHydrophobic();
}

// TODO
//void Paper::makeWaterStroke()
//{
//	for (size_t x = WATER_BRUSH_START_X; x < WATER_BRUSH_END_X; x++)
//	{
//		for (size_t y = WATER_BRUSH_START_Y; y < WATER_BRUSH_END_Y; y++)
//		{
//			getNext(x, y)->addWater(0);
//		}
//	}
//}
//
//void Paper::addWaterDrop(size_t x0, size_t y0, size_t r)
//{
//	for (size_t x = 0; x < W; x++) {
//		for (size_t y = 0; y < H; y++) {
//			float w = sqrt((float)(r * r - ((float)x - x0) * ((float)x - x0) - ((float)y - y0) * ((float)y - y0))) - (float)r / 2.0f;
//			if (w > 0)
//				getNext(x, y)->addWater(w / r);
//		}
//	}
//}
//
//void Paper::makeInkStroke()
//{
//	for (size_t x = INK_BRUSH_START_X; x < INK_BRUSH_END_X; x++)
//	{
//		for (size_t y = INK_BRUSH_START_Y; y < INK_BRUSH_END_Y; y++)
//		{
//			getNext(x, y)->addInk();
//		}
//	}	mirror();
//}
//
//void Paper::calculatePaperMaxSpeed()
//{
//	/*maxSpeed = -1.0;
//	for (auto u : getOld()) {
//		if (u.getMaxSpeed() > maxSpeed) maxSpeed = u.getMaxSpeed();
//	}*/
//}

void Paper::setPaperPlane(size_t newB, size_t newC) {
	for (size_t x = 0; x < W; x++)
		for (size_t y = 0; y < H; y++) {
			auto cell = conv<SimpleCell>(getNext(x, y));
			//TODO
			//cell->B = newB;
			//cell->C = newC;
		}
}

void Paper::setNoise() {
	PerlinNoise pn;
	for (size_t i = 0; i < W * H; i++)
	{
		float x = (float)(i % W) / ((float)W);
		float y = (float)(i / W) / ((float)H);

		// Typical Perlin noise
		float n = pn.noise(CELL_SIZE * 10 * x, CELL_SIZE * 10 * y, rand1);

		auto cell = conv<Cell>(getNext(i));
		if (cell)
		{
			cell->h = n;
		}
	}
}

void Paper::setHydrophobic() {
	PerlinNoise pn;
	for (size_t i = 0; i < W * H; i++)
	{
		float x = (float)(i % W) / ((float)W);
		float y = (float)(i / W) / ((float)H);

		// Typical Perlin noise
		float n = pow(pn.noise(x * W * 0.005, y * H * 0.005, rand2), 2.0);

		auto cell = conv<SimpleCell>(getNext(i));
		if (cell)
		{
			if (n > 0.5)
				cell->setHydrophobic((n - 0.5) * 2.0);
		}
	}
}

void Paper::addFibres(const PAPER paper) {
	for (size_t i = 0; i < W * H / paper.FIBER_INVERSE_DENSITY; i++)
	{
		//draw a random line from the selected cell of length FIBER_LEN and get all cells the line crosses using Bresenham's algorithm
		long long int x1 = rand() % W;
		long long int y1 = rand() % H;

		//the second point will be exactly FIBER_LEN away from the first
		float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 360));
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
			Cell* cell = conv<Cell>(getNext(x1, y1));
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
	float max = -1;

	for (auto &ct : getNext()) {
		auto c = conv<SimpleCell>(ct);
		if (max < c->h)
		{
			max = c->h;
		}
	}
	for (auto &ct : getNext()) {
		auto c = conv<SimpleCell>(ct);
		c->h = c->h / max;
		c->fixPaperHeight();
	}

	for (size_t x = 1; x < W - 1; x++)
	{
		for (size_t y = 1; y < H - 1; y++)
		{
			//TODO @vita decide
			// Vita: monke logic
			//float hx = (getNext(x + 1, y)->h - getNext(x - 1, y)->h) / 2;
			//float hy = (getNext(x, y + 1)->h - getNext(x, y - 1)->h) / 2;
			//getNext(x, y)->setHeightGradient(hx, hy);

			// Johanka: ((u+1,v) - (u,v), (u,v+1) - (u,v))
			float hx = conv<SimpleCell>(getNext(x + 1, y))->h - conv<SimpleCell>(getNext(x, y))->h;
			float hy = conv<SimpleCell>(getNext(x, y + 1))->h - conv<SimpleCell>(getNext(x, y))->h;
			//getNext(x, y)->setHeightGradient(hx, hy);
		}
	}	
}