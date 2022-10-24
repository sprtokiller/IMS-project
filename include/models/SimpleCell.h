/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef SIMPLECELL_H
#define SIMPLECELL_H

#include "models/PaperCell.h"
#include "MagicConstants.h"

/*
	ZHANG, Qing, et al. Simple cellular automaton‐based simulation of ink behaviour and its application to Suibokuga‐like 3D rendering of trees.
	The Journal of Visualization and Computer Animation, 1999, 10.1: 27-37.
*/
class SimpleCell : public Cell {
public:
	static constexpr size_t aproxSize() { return sizeof(SimpleCell); }
	// main simulation equations
	template<class T>
	static void doCalc(size_t cores, T* ca);

	void setHeightGradient(double new_hx, double new_hy) {};
	void fixPaperHeight();
	void addWater();
	void addInk();
	void setHydrophobic(double ph) override {};
	double getMaxSpeed() const { return 0.0; };
	double getWater() const { return W; };
	double getInk() const { return I; };
public://TODO @vita remove public
	int W = 0; //water particles
	int I = 0; //ink particles
	int B = DEFAULT_B; //height of bottom (water capacity)
	int C = DEFAULT_C; //capacity of water captured to cells
protected:
	template<class T>
	static void simpleFlow(size_t x, size_t y, T* ca);
public:
	// Inherited via Cell
	virtual const Color draw() const override;
};

#endif // !SIMPLECELL_H