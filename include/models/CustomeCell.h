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

class CustomeCell : public Cell {
public:
	static constexpr size_t aproxSize() { return sizeof(CustomeCell); }
	template<class T>
	static void doCalc(size_t cores, T* ca);
	double getWater() const { return 0.0; } /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */
	void fixPaperHeight();
	void setHeightGradient(double new_hx, double new_hy);
	void addWater() {};
	void addInk() {};
private:
	
public:

protected:
	/*
	template<class T>
	static void relaxDivergence(size_t x, size_t y, T* tca);
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
	virtual const Color draw() const override;
};

#endif // !CUSTOMECELL_H