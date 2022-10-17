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
#include <thread>
#include <iostream>

#include "template/World.h"

using namespace std;

template <class Unit, size_t W, size_t H>
class CAutomata_T
{
public:
	using CAutomata = CAutomata_T<Unit, W, H>;
	using World = World_T<Unit, W, H>;

	using UpdateFunc = void(*)(size_t id, size_t cores, CAutomata* ca);

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
		swap(old, next);
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

	void run(size_t cycles, size_t cores, UpdateFunc func, bool print = false) {
		vector<thread> threads;
		int i;

		for (size_t n = 0; n < cycles; n++)
		{
			if (print)
				if (n % cores == 0) cout << n * 100 / cycles << "%\n";

			for (size_t id = 0; id < cores; id++)
				threads.push_back(thread(func, id, cores, this));

			for (auto& th : threads) th.join();
			threads.clear();

			flip();
		}
	}

	const size_t WIDTH = W;
	const size_t HEIGHT = H;

	static constexpr size_t aproxSize() {
		return 2 * (World::aproxSize() + sizeof(World*));
	}
protected:
	void mirror() {
		delete old;
		old = new World(*next);
	}

private:
	World* old;
	World* next;
};

#endif