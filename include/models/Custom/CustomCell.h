/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef CUSTOMECELL_H
#define CUSTOMECELL_H

#include "models/PaperCell.h"

class CustomPaper;

class CustomCell : public Cell {
public:
	static void doCalc(size_t cores, CustomPaper* ca);

	float getWater() const { return 0.0; }
	void fixPaperHeight();
	void setHeightGradient(float new_hx, float new_hy);
	void addWater(float w) { water += w; };
	void addInk() {};
	void setHydrophobic(float ph) { phobia = ph; };
private:

public:
	bool active = false; // is cell active (for optimization)
	float phobia = 0;
	float water = 0;
	float absorbed_water = 0;
protected:
	
	static void spreadWater(size_t x, size_t y, CustomPaper* tca);
	static void absorbWater(size_t x, size_t y, CustomPaper* tca);

	/*
	template<class T>
	static void adjustVelocities(size_t x, size_t y, T* tca);
	template<class T>
	static void copyVelocities(size_t x, size_t y, T* tca);
	template<class T>
	static void updateVelocities(size_t x, size_t y, T* tca);
	template<class T>
	static void enforceBoundaryConditions(size_t x, size_t y, T* tca);
	*/
public:
	// Inherited via Cell
	virtual const Color draw(Color base) const override;
};

#endif // !CUSTOMECELL_H