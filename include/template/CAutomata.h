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

template <class Unit>
class CAutomata_T
{
public:
	using CAutomata = CAutomata_T<Unit>;
	using World = World_T<Unit>;
	using WorldUnit = Unit;

	CAutomata_T(size_t WIDTH, size_t HEIGHT): W(WIDTH), H(HEIGHT) {
        old= std::make_unique<World>(W,H);
        next= std::make_unique<World>(W,H);
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

	virtual void run(size_t cores, size_t cycles) = 0;

	static constexpr size_t aproxSize(size_t WIDTH, size_t HEIGHT) {
		//size of worlds and size of this object
		return 2 * (World::aproxSize(WIDTH, HEIGHT) + sizeof(CAutomata_T<Unit>));
	}
	
	void mirror() {
        //creates deep copy of world
        old.reset(new World(*next));
	}

	const size_t W;
	const size_t H;
private:
    std::unique_ptr<World> old;
    std::unique_ptr<World> next;
};

#endif