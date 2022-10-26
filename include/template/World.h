/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file World.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef WORLD_H
#define WORLD_H

//forward declaration
class Cell_T;

#include <vector>
#include <math.h>

using Cell_Factory = Cell_T * (*)();
using Cell_vector = std::vector<Cell_T*>;

class World_T
{	
public:
	World_T(size_t WIDTH, size_t HEIGHT, Cell_Factory factory);
	~World_T() = default;

	Cell_vector& getData() {
		return cells;
	};
	
	/// <summary>
	/// Gets cell at position (x, y),
	/// checks if cell is out of bounds, returns nullptr it that case
	/// </summary>
	Cell_T* get(long long int x, long long int y);;

	/// <summary>
	/// Gets cell at index,
	/// does not check if cell is out of bounds, may return nullptr
	/// </summary>
	Cell_T* get(size_t i);;

	/// <summary>
	/// Gets cell at position (x, y),
	/// does not check if cell is out of bounds, may return invalid pointer,
	/// use get() instead if unsure
	/// </summary>
	Cell_T* getUnsafe(size_t x, size_t y);;

	/// <summary>
	/// Gets cell at index,
	/// does not check if cell is out of bounds, may return invalid pointer,
	/// use get() instead if unsure
	/// </summary>
	Cell_T* getUnsafe(size_t i);;

	/// <summary>
	/// Calculates approximated size of the world in Bytes
	/// </summary>
	template<class T>
	static constexpr size_t aproxSize(size_t WIDTH, size_t HEIGHT) {
		//size of elements and pointer to elements + size of this object 
		return WIDTH * HEIGHT * (sizeof(T) + sizeof(void*)*2) + sizeof(World_T);
	}

	const size_t W;
	const size_t H;
private:
	Cell_vector cells;
};

#endif //!WORLD_H