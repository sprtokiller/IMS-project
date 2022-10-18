/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef CELL_H
#define CELL_H

#include <vector>
#include "MagicConstants.h"

class Cell
{
public:
	Cell() {};
	~Cell() {};

	template<class T>
	static void doCalc(size_t id, size_t cores, T* ca){}
	void virtual fixPaperHeight() = 0;
	double virtual getWater() const = 0;
	void virtual addWater() = 0;
	void virtual addInk() = 0;
public:
	double h = 0; //paper "structure"
private:
};

/*
	ZHANG, Qing, et al. Simple cellular automaton‐based simulation of ink behaviour and its application to Suibokuga‐like 3D rendering of trees.
	The Journal of Visualization and Computer Animation, 1999, 10.1: 27-37.
*/
class SimpleCell : public Cell {
public:
	static constexpr size_t aproxSize() {
		return sizeof(SimpleCell);
	}
	template<class T>
	static void doCalc(size_t id, size_t cores, T* ca);
	
	void fixPaperHeight();
	void addWater();
	void addInk();
	double getWater() const {
		return W;
	}
public:
	uint W = 0; //water particles
	uint I = 0; //ink particles
	uint B = DEFAULT_B; //height of bottom (water capacity)
	uint C = DEFAULT_C; //capacity of water captured to cells
};

/*
	CURTIS, Cassidy J., et al. Computer-generated watercolor.
	In: Proceedings of the 24th annual conference on Computer graphics and interactive techniques. 1997. p. 421-430.
*/
class ComplexCell : public Cell {
public:
	static constexpr size_t aproxSize() {
		return sizeof(ComplexCell);
	}
	template<class T>
	static void doCalc(size_t id, size_t cores, T* ca);
public:
	double u = 0; //velocity in x direction
	double v = 0; //velocity in y direction
};

#endif