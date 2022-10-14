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
		//algo
	}
private:
	array< Cell, W* H> cells;
};

#endif