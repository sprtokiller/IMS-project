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

	/// <summary>
	/// Gets cell (read only)
	/// </summary>
	const Unit* getOld(size_t x, size_t y) {
		return old->get(x, y);
	}

	/// <summary>
	/// Gets cell (read only)
	/// </summary>
	const Unit* getOld(size_t i) {
		return old->get(i);
	}
	
	/// <summary>
	/// Gets cell (read only)
	/// </summary>
	std::array<Unit, W* H>& getOld() {
		return old->getData();
	}

	/// <summary>
	/// Gets cell (for writing)
	/// </summary>
	Unit* getNext(size_t x, size_t y) {
		return next->get(x, y);
	}

	/// <summary>
	/// Gets cell (for writing)
	/// </summary>
	Unit* getNext(size_t i) {
		return next->get(i);
	}

	/// <summary>
	/// Gets cell (for writing)
	/// </summary>
	std::array<Unit, W* H>& getNext() {
		return next->getData();
	}
	
	void run(size_t cycles, size_t cores, UpdateFunc func, bool print = false) {
		vector<thread> threads;
		int i;

		for (size_t n = 0; n < cycles; n++)
		{
			if(print)
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