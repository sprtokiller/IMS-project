#pragma once

#include "output/BitMapTypes.h"
#include <cstddef>
#include <vector>
#include <thread>

template<typename T>
//Cell update function
using Cell_Function = void(*)(size_t, size_t, T*);

class Cell_T
{
public:
	Cell_T() {};
	~Cell_T() {};

	//returns pixel value of cell
	const Color virtual draw() const = 0;

	template<class T>
	//runs all calculations for all cells
	static void doCalc(size_t cores, T* ca) {};
	
	//doc used to create this lamba function
	//https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
	
	template<class T>
	//Runs Cell update functions on separate threads
	static void runAsync(std::size_t cores, Cell_Function<T> __f, T* ca, bool all = false) {
		std::vector<std::thread> threads;
		auto cell_caller = [&](size_t id) {
			for (size_t y = id * ca->HEIGHT / cores; y < (id + 1) * ca->HEIGHT / cores; y++) {
				if (!all) {
					if (y < 2) continue;
					if (y >= ca->HEIGHT - 2) break;

					for (size_t x = 2; x < ca->WIDTH - 2; x++) {
						__f(x, y, ca);
					}
				}
				else
				{
					for (size_t x = 0; x < ca->WIDTH; x++) {
						__f(x, y, ca);
					}
				}
			}
		};

		for (size_t id = 0; id < cores; id++)
			threads.push_back(std::thread(cell_caller, id));

		for (auto& th : threads)
			th.join();

		threads.clear();
	}
};