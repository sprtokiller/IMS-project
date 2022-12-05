/**
 * @brief ComplexCell class definition
 *
 * @file ComplexCell.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef COMPLEXCELL_H
#define COMPLEXCELL_H

#include "models/PaperCell.h"

class ComplexPaper;

class ComplexCell : public Cell {
public:
	static void doCalc(size_t cores, ComplexPaper* ca);

	void fixPaperHeight();
	void setHeightGradient(float new_hx, float new_hy);
	float getWater() const { return 0.0; } /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */
	void addWater(float w);
	void setHydrophobic(float ph) {};
	void addInk() { /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */ };
	float getMaxSpeed() const {
		if (abs(u) > abs(v)) return abs(u);
		return abs(v);
	}
private: //TODO @ilya template hell
	void flowOutward(); //TODO make static
public://TODO @vita remove public
	float hx = 0; //height change in x direction
	float hy = 0; //height change in y direction
	float c = 0; //fluid holding capacity
	float u = 0; //velocity in x direction (cells / cycle)
	float v = 0; //velocity in y direction (cells / cycle)
	float p = 0; //water pressure
	float gk = 0; //pigment in shallow-water layer
	float dk = 0; //deposited pigment
	float s = 0; //water saturation
	bool m = false; //mask
	
protected:
	static void relaxDivergence(size_t x, size_t y, ComplexPaper* tca);
	static void adjustVelocities(size_t x, size_t y, ComplexPaper* tca);
	static void copyVelocities(size_t x, size_t y, ComplexPaper* tca);
	static void updateVelocities(size_t x, size_t y, ComplexPaper* tca);
	static void enforceBoundaryConditions(size_t x, size_t y, ComplexPaper* tca);
public:
	// Inherited via Cell
	virtual const Color draw(Color base) const override;
};

#endif // !COMPLEXCELL_H