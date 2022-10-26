#include "template/Cell.h"
#include "template/CAutomata.h"

#include <thread>
#include <vector>

void Cell_T::runAsync(std::size_t cores, Cell_Function __f, CAutomata_T* ca, bool all) {
	std::vector<std::thread> threads;
	auto cell_caller = [&](size_t id) {
		for (size_t y = id * ca->H / cores; y < (id + 1) * ca->H / cores; y++) {
			if (!all) {
				if (y < 2) continue;
				if (y >= ca->H - 2) break;

				for (size_t x = 2; x < ca->W - 2; x++) {
					__f(x, y, ca);
				}
			}
			else
			{
				for (size_t x = 0; x < ca->W; x++) {
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