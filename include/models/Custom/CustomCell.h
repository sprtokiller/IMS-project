/**
 * @brief Custom cell class definition
 *
 * @file CustomCell.h
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
	void addWater(float w) { water += w; };
	void addInk() {};
	void setHydrophobic(float ph) { phobia = ph; };
private:

public:
	bool active = false;
	float phobia = 0;
	float water = 0;
	float absorbed_water = 0;
protected:
	static void activateNearby(size_t x, size_t y, CustomPaper* tca);

	static void spreadWater(size_t x, size_t y, CustomPaper* tca);
	static void absorbWater(size_t x, size_t y, CustomPaper* tca);
    static void flowWater(size_t x, size_t y, CustomPaper* tca);

	static void vaporizeWater(size_t x, size_t y, CustomPaper* tca);

    /*
	static void adjustVelocities(size_t x, size_t y, CustomPaper* tca);
	static void copyVelocities(size_t x, size_t y, CustomPaper* tca);
	static void updateVelocities(size_t x, size_t y, CustomPaper* tca);
	static void enforceBoundaryConditions(size_t x, size_t y, CustomPaper* tca);
     */
public:
	// Inherited via Cell
	virtual const Color draw(Color base) const override;
};

#endif // !CUSTOMECELL_H