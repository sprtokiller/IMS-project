/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file World.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <math.h>
#include <assert.h>

template <class Unit, size_t W, size_t H>
class World_T
{
public:
	World_T() = default;
	~World_T() = default;

	const std::array<Unit, W * H>& getData() const {
		return cells;
	};
	
	/// <summary>
	/// Gets cell at position (x, y),
	/// checks if cell is out of bounds, returns nullptr it that case
	/// </summary>
	Unit* get(long long int x, long long int y) {
		if (!((x >= 0 && x < W) && (y >= 0 && y < H)))
			return nullptr;
		Unit* cell = &cells[x + y * W];
		return cell;
	};

	/// <summary>
	/// Gets cell at index,
	/// does not check if cell is out of bounds, may return nullptr
	/// </summary>
	Unit* get(size_t i) {
		if (i >= W * H) return nullptr;
		Unit* cell = &cells[i];
		return cell;
	};

	/// <summary>
	/// Gets cell at position (x, y),
	/// does not check if cell is out of bounds, may return invalid pointer,
	/// use get() instead if unsure
	/// </summary>
	Unit* getUnsafe(size_t x, size_t y) {
		assert(x < W);
		assert(y < H);
		Unit* cell = &cells[x + y * W];
		assert(cell != nullptr);
		return cell;
	};

	/// <summary>
	/// Gets cell at index,
	/// does not check if cell is out of bounds, may return invalid pointer,
	/// use get() instead if unsure
	/// </summary>
	Unit* getUnsafe(size_t i) {
		assert(i < W * H);
		Unit* cell = &cells[i];
		assert(cell != nullptr);
		return cell;
	};

	/// <summary>
	/// Calculates approximated size of the world in Bytes
	/// </summary>
	static constexpr size_t aproxSize() {
		return W * H * Unit::aproxSize();
	}
protected:
	std::array<Unit, W*H> cells;
};

#endif