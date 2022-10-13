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

#include "template/Field.h"

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

	void run(size_t cycles, size_t cores, void (*RunCell)(size_t, size_t, CAutomata_T)) {
		vector<thread> threads;
		int i;

		for (size_t n = 0; n < cycles; n++)
		{
			//if (n % 16 == 0) cout << n * 100 / cycles << "%\n";

			for (size_t id = 0; id < cores; id++)
				threads.push_back(thread(RunCell, id, cores, *this));

			for (auto& th : threads) th.join();
			threads.clear();

			flip();
		}
	}
	
	const size_t WIDTH = W;
	const size_t HEIGHT = H;
private:
	Field<T, W, H>* old;
	Field<T, W, H>* next;
};

#include "Cell.h"
typedef CAutomata_T<Cell, 100, 100> CAutomata;