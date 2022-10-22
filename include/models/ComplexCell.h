/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef COMPLEXCELL_H
#define COMPLEXCELL_H

#include "models/PaperCell.h"

/*
	CURTIS, Cassidy J., et al. Computer-generated watercolor.
	In: Proceedings of the 24th annual conference on Computer graphics and interactive techniques. 1997. p. 421-430.
*/
class ComplexCell : public Cell {
public:
	static constexpr size_t aproxSize() { return sizeof(ComplexCell); }
	template<class T>
	static void doCalc(size_t cores, T* ca);

	void fixPaperHeight();
	void setHeightGradient(double new_hx, double new_hy);
	double getWater() const { return 0.0; } /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */
	void addWater();
	void addInk() { /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */ };
	double getMaxSpeed() const {
		if (abs(u) > abs(v)) return abs(u);
		return abs(v);
	}
private:
	void flowOutward(); //TODO make static
public://TODO @vita remove public
	double hx = 0; //height change in x direction
	double hy = 0; //height change in y direction
	double c = 0; //fluid holding capacity
	double u = 0; //velocity in x direction (cells / cycle)
	double v = 0; //velocity in y direction (cells / cycle)
	double p = 0; //water pressure
	double gk = 0; //pigment in shallow-water layer
	double dk = 0; //deposited pigment
	double s = 0; //water saturation
	bool m = false; //mask
	
protected:
	template<class T>
	static void relaxDivergence(size_t x, size_t y, T* tca);
	template<class T>
	static void clearVelocities(size_t x, size_t y, T* tca);
	template<class T>
	static void updateVelocities(size_t x, size_t y, T* tca);
public:
	// Inherited via Cell
	virtual const Color draw() const override;
};

#endif // !COMPLEXCELL_H