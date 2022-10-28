#pragma once

//forward declaration
class Cell_T;
class CAutomata_T;

#include "output/BitMapTypes.h"
#include <vector>
#include <cassert>

using Cell_Function = void (*)(size_t x, size_t y, CAutomata_T* ca);

class Cell_T
{
public:
	Cell_T() {};
	~Cell_T() {};

	//returns pixel value of cell
	const Color virtual draw(Color base) const = 0;

	//runs all calculations for all cells
	static void doCalc(size_t cores, CAutomata_T* ca) {
		assert(false);//Derived class is missing its doCalc implementation
	}
protected:
	//Runs Cell update functions on separate threads
	static void runAsync(std::size_t cores, Cell_Function __f, CAutomata_T* ca, bool all = false);
};

//abstract factory

template <class T>
Cell_T* abstracFactory() {
	return (Cell_T*) new T();
}

//conversion functions:

template<class T>
inline std::vector<const T*>& conv(std::vector<const Cell_T*>& vec) {
	return *((std::vector<const T*>*) & vec);
}

template<class T>
inline std::vector<T*>& conv(std::vector<Cell_T*>& vec) {
	return *((std::vector<const T*>*) & vec);
}

template<class T>
inline const T* conv(const Cell_T* cell) {
	return ((const T*) cell);
}

template<class T>
inline T* conv(Cell_T* cell) {
	return ((T*) cell);
}
