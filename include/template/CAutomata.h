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
#include <thread>
#include <iostream>

#include "template/World.h"

using namespace std;

template <class Cell, size_t W, size_t H>
class CAutomata_T
{
	using CAutomata = CAutomata_T<Cell, W, H>;
	using World = World_T<Cell, W, H>;
	
	using UpdateFunc = void(*)(size_t id, size_t cores, CAutomata* ca);
	
public:
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
	const Cell* getOld(size_t x, size_t y) {
		return old->get(x, y);
	}

	/// <summary>
	/// Gets cell (recommended for writing)
	/// </summary>
	Cell* getNext(size_t x, size_t y) {
		return next->get(x, y);
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

	static constexpr size_t aproxSize() {
		return 2 * (World::aproxSize() + sizeof(World*));
	}

	const size_t WIDTH = W;
	const size_t HEIGHT = H;
private:
	World* old;
	World* next;
};