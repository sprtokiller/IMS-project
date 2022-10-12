/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once
#include <vector>

class Cell
{
public:
	Cell() {};
	Cell(size_t initB, size_t initC) : B(initB), C(initC) {}
	~Cell() {};
	inline size_t getW() const { return W; }
	inline size_t getI() const { return I; }
	inline size_t getB() const { return B; }
	inline size_t getC() const { return C; }
private:
	size_t W = 0; //water particles
	size_t I = 0; //ink particles
	size_t B = 0; //height of bottom (water capacity)
	size_t C = 0; //capacity of water captured to cells
};