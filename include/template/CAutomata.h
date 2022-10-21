/**
 * @brief Defines an abstract class for a Cellular Automaton
 *
 * @file CAutomata.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef CAUTOMATA_H
#define CAUTOMATA_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "template/World.h"

template <class Unit, size_t W, size_t H>
class CAutomata_T
{
public:
	using CAutomata = CAutomata_T<Unit, W, H>;
	using World = World_T<Unit, W, H>;
	using WorldUnit = Unit;

	CAutomata_T() {
		old = new World();
		next = new World();
	}
	~CAutomata_T() {
		free(old);
		free(next);
	}
	/// <summary>
	/// Updates world
	/// </summary>
	void flip() {
		std::swap(old, next);
	}
	const Unit* getOld(size_t x, size_t y) const {
		return old->get(x, y);
	}
	const Unit* getOld(size_t i) const {
		return old->get(i);
	}
	const World::Data& getOld() const {
		return old->getData();
	}
	Unit* getNext(size_t x, size_t y) const {
		return next->get(x, y);
	}
	Unit* getNext(size_t i) const {
		return next->get(i);
	}
	World::Data& getNext() {
		return next->getData();
	}
	const Unit* getOldUnsafe(size_t x, size_t y) const {
		return old->getUnsafe(x, y);
	}
	const Unit* getOldUnsafe(size_t i) const {
		return old->getUnsafe(i);
	}
	Unit* getNextUnsafe(size_t x, size_t y) const {
		return next->getUnsafe(x, y);
	}
	Unit* getNextUnsafe(size_t i) const {
		return next->getUnsafe(i);
	}

	void run(size_t cores, size_t cycles) {
		for (size_t n = 0; n < cycles; n++)
		{
			Unit::doCalc(cores, this);
		}
	}

	static constexpr size_t aproxSize() {
		return 2 * (World::aproxSize() + sizeof(World*));
	}
	
	void mirror() {
		delete old;
		old = new World(*next);
	}

	const size_t WIDTH = W;
	const size_t HEIGHT = H;
private:
	World* old;
	World* next;
};

#endif