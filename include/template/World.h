/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file World.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once
#include <array>

using namespace std;

template <class Cell, size_t W, size_t H>
class World_T
{
public:
	Cell* get(size_t x, size_t y) {
		return &cells[x + y * W];
	};
private:
	array< Cell, W* H> cells;
};
