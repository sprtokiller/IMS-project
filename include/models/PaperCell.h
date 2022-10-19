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
#include <math.h>

inline int Tmax(int a, int b) { return a > b ? a : b; }
inline double Tmax(double a, double b) { return a > b ? a : b; }
inline int Tmin(int a, int b) { return a < b ? a : b; }
inline double Tmin(double a, double b) { return a < b ? a : b; }

class Cell
{
public:
	Cell() {};
	~Cell() {};
	template<typename _Callable, class T>
	static void runAsync(size_t cores, _Callable&& __f, T ca);
	void virtual fixPaperHeight() = 0;
	void virtual setHeightGradient(double new_hx, double new_hy) = 0;
	double virtual getWater() const = 0;
	void virtual addWater() = 0;
	void virtual addInk() = 0;
	double virtual getMaxSpeed() const = 0;
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
	// main simulation equations
	template<class T>
	static void doCalc(size_t cores, T* ca);
	template<class T>
	static void SimpleFlow(size_t x, size_t y, T* ca);

	void setHeightGradient(double new_hx, double new_hy) {};
	void fixPaperHeight();
	void addWater();
	void addInk();
	double getMaxSpeed() const {
		return 0.0;
	}
	double getWater() const {
		return W;
	}
	double getInk() const {
		return I;
	}
public:
	int W = 0; //water particles
	int I = 0; //ink particles
	int B = DEFAULT_B; //height of bottom (water capacity)
	int C = DEFAULT_C; //capacity of water captured to cells
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
	static void doCalc(size_t cores, T* ca);
	template<class T>
	static void ComplexFlow(size_t x, size_t y, T* ca);
	
    void fixPaperHeight();
	void setHeightGradient(double new_hx, double new_hy);
	template<class T>
	void moveWater(T* ca, size_t x, size_t y);
	double getWater() const {
		return 0.0;  /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */
	}
	void addWater() { /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */ };
	void addInk() { /* NOT TODO THIS FUNCTION IS NOT NEEDED.EVER. */ };
	double getMaxSpeed() const {
		if (abs(u) > abs(v)) return abs(u);
		return abs(v);
	}
private:
	template<class T>
	void updateVelocities(T* ca, size_t x, size_t y);
	void relaxDivergence();
	void flowOutward();
public:
	double hx = 0; //height change in x direction
	double hy = 0; //height change in y direction
	double c = 0; //water capacity
	double u = 0; //velocity in x direction
	double v = 0; //velocity in y direction
	double p = 0; //water pressure
};

#endif