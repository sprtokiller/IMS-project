/**
 * @brief Defines an abstract class for a Cellular Automaton
 *
 * @file CAutomata.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef CAUTOMATA_H
#define CAUTOMATA_H

//foward declaration
class CAutomata_T;

#include <vector>
#include <memory>

#include "template/World.h"

using Cell_Rule = void (*)(size_t cores, CAutomata_T* ca);

class CAutomata_T
{
public:
	CAutomata_T(size_t WIDTH, size_t HEIGHT, Cell_Factory factory);
	~CAutomata_T();
	/// <summary>
	/// Updates world
	/// </summary>
	void flip() {
		std::swap(old, next);
	}
	const Cell_T* getOld(size_t x, size_t y) const {
		return old->get(x, y);
	}
	const Cell_T* getOld(size_t i) const {
		return old->get(i);
	}
	const Cell_vector& getOld() const {
		return old->getData();
	}
	Cell_T* getNext(size_t x, size_t y) const {
		return next->get(x, y);
	}
	Cell_T* getNext(size_t i) const {
		return next->get(i);
	}
	Cell_vector& getNext() {
		return next->getData();
	}
	const Cell_T* getOldUnsafe(size_t x, size_t y) const {
		return old->getUnsafe(x, y);
	}
	const Cell_T* getOldUnsafe(size_t i) const {
		return old->getUnsafe(i);
	}
	Cell_T* getNextUnsafe(size_t x, size_t y) const {
		return next->getUnsafe(x, y);
	}
	Cell_T* getNextUnsafe(size_t i) const {
		return next->getUnsafe(i);
	}

	void run(size_t cores, size_t cycles, Cell_Rule func){
		for (size_t i = 0; i < cycles; i++) {
			func(cores, this);
		}
	};

	template<class T>
	static constexpr size_t aproxSize(size_t WIDTH, size_t HEIGHT) {
			//size of worlds and size of this object
	return 2 * (World_T::aproxSize<T>(WIDTH, HEIGHT) + sizeof(CAutomata_T));
	}
	
	void mirror();

	const size_t W;
	const size_t H;
private:
	World_T* old;
	World_T* next;
};

#endif