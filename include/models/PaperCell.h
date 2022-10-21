/**
 * @brief Abstract Cell class, must be populated with a concrete implementation and rules
 *
 * @file Cell.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef PAPERCELL_H
#define PAPERCELL_H

#include <vector>
#include "MagicConstants.h"
#include "output/BitMapTypes.h"
#include "template/Cell.h"
#include <math.h>

inline int Tmax(int a, int b) { return a > b ? a : b; };
inline double Tmax(double a, double b) { return a > b ? a : b; };
inline int Tmin(int a, int b) { return a < b ? a : b; };
inline double Tmin(double a, double b) { return a < b ? a : b; };

class Cell : public Cell_T
{
public:
	void virtual addWater() = 0;
	void virtual addInk() = 0;
public://TODO @vita remove public
	double h = 0; //paper "structure"
};

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
	void addWater() { /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */ };
	void addInk() { /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */ };
	double getMaxSpeed() const {
		if (abs(u) > abs(v)) return abs(u);
		return abs(v);
	}
private:
	void relaxDivergence(); //TODO make static
	void flowOutward(); //TODO make static
public://TODO @vita remove public
	double hx = 0; //height change in x direction
	double hy = 0; //height change in y direction
	double c = 0; //water capacity
	double u = 0; //velocity in x direction
	double v = 0; //velocity in y direction
	double p = 0; //water pressure
protected:
	template<class T>
	static void clearVelocities(size_t x, size_t y, T* tca);
	template<class T>
	static void updateVelocities(size_t x, size_t y, T* tca);
public:
	// Inherited via Cell
	virtual const Color draw() const override;
};

#endif // !PAPERCELL_H