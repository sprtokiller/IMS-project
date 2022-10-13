/**
 * @brief Defines an abstract class for a Cellular Automaton
 *
 * @file CAutomata.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "template/Field.h"

template <class T, size_t W, size_t H>
class CAutomata_T;

#include "Cell.h"
typedef CAutomata_T<Cell, 100, 100> CAutomata;
typedef void (*RunCell)(CAutomata);

using namespace std;

template <class T, size_t W, size_t H>
class CAutomata_T
{
public:
	CAutomata_T(){
		old = new Field<T, W, H>();
		next = new Field<T, W, H>();
	}
	/// <summary>
	/// Updates world
	/// </summary>
	void flip() {
		swap(old, next);
	}

	/// <summary>
	/// Gets cell (read only)
	/// </summary>
	const T* getOld(size_t x, size_t y) const {
		return old->get(x, y);
	}

	/// <summary>
	/// Gets cell (recommended for writing)
	/// </summary>
	T* getNext(size_t x, size_t y) const {
		return next->get(x, y);
	}

	void run(size_t cycles, size_t cores, RunCell f) {
		
	}
	
	const size_t WIDTH = W;
	const size_t HEIGHT = H;
private:
	Field<T, W, H>* old;
	Field<T, W, H>* next;
};
