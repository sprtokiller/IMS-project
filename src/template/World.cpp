#include "template/World.h"
#include "template/Cell.h"

#include <assert.h>

World_T::World_T(size_t WIDTH, size_t HEIGHT, Cell_Factory factory) : W(WIDTH), H(HEIGHT) {
	cells.reserve(W * H);
	for (size_t i = 0; i < W * H; i++) {
		cells.push_back(factory());
	}
}

Cell_T* World_T::get(long long int x, long long int y) {
	if (!((x >= 0 && x < W) && (y >= 0 && y < H)))
		return nullptr;
	Cell_T* cell = cells[x + y * W];
	return cell;
}

Cell_T* World_T::get(size_t i) {
	if (i >= W * H) return nullptr;
	Cell_T* cell = cells[i];
	return cell;
}

Cell_T* World_T::getUnsafe(size_t x, size_t y) {
	assert(x < W);
	assert(y < H);
	Cell_T* cell = cells[x + y * W];
	assert(cell != nullptr);
	return cell;
}

Cell_T* World_T::getUnsafe(size_t i) {
	assert(i < W* H);
	Cell_T* cell = cells[i];
	assert(cell != nullptr);
	return cell;
}

