/**
 * @brief Simple cell class definition
 *
 * @file SimpleCell.h
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
class SimplePaper;

class SimpleCell : public Cell {
public:
	static constexpr size_t aproxSize() { return sizeof(SimpleCell); }
	// main simulation equations
	static void doCalc(size_t cores, SimplePaper* ca);

	void setHeightGradient(float new_hx, float new_hy) {};
	void fixPaperHeight();
	void addWater(float w);
	void addInk();
	void setHydrophobic(float ph) {};
	float getMaxSpeed() const { return 0.0; };
	float getWater() const { return W; };
	float getInk() const { return I; };
public://TODO @vita remove public
	int W = 0; //water particles
	int I = 0; //ink particles
	int B = DEFAULT_B; //height of bottom (water capacity)
	int C = DEFAULT_C; //capacity of water captured to cells
protected:
	static void simpleFlow(size_t x, size_t y, SimplePaper* ca);
public:
	// Inherited via Cell
	virtual const Color draw(Color base) const override;
};

#endif // !SIMPLECELL_H