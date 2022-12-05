/**
 * @brief Abstract CA 2D array class definition
 *
 * @file World.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <math.h>
#include <assert.h>

#include "template/Cell.h"

template<class Unit>
class World_T {
public:
    using Data = std::vector<Unit *>;

    World_T(size_t WIDTH, size_t HEIGHT);

    World_T(const World_T &copy);

    ~World_T();

    World_T &operator=(const World_T &) = delete;

    World_T(World_T &&) = delete;

    World_T &operator=(World_T &&) = delete;

    Data &getData() {
        return cells;
    };

    /// <summary>
    /// Gets cell at position (x, y),
    /// checks if cell is out of bounds, returns nullptr it that case
    /// </summary>
    Unit *get(long long int x, long long int y);;

    /// <summary>
    /// Gets cell at index,
    /// does not check if cell is out of bounds, may return nullptr
    /// </summary>
    Unit *get(size_t i);;

    /// <summary>
    /// Gets cell at position (x, y),
    /// does not check if cell is out of bounds, may return invalid pointer,
    /// use get() instead if unsure
    /// </summary>
    Unit *getUnsafe(size_t x, size_t y);;

    /// <summary>
    /// Gets cell at index,
    /// does not check if cell is out of bounds, may return invalid pointer,
    /// use get() instead if unsure
    /// </summary>
    Unit *getUnsafe(size_t i);;

    /// <summary>
    /// Calculates approximated size of the world in Bytes
    /// </summary>
    static constexpr size_t aproxSize(size_t WIDTH, size_t HEIGHT) {
        //size of elements and pointer to elements + size of this object
        return WIDTH * HEIGHT * (sizeof(Unit) + sizeof(Unit *)) + sizeof(World_T<Unit>);
    }

    const size_t W;
    const size_t H;
protected:
    Data cells;
};

template<class Unit>
World_T<Unit>::World_T(const World_T &copy) : W(copy.W), H(copy.H) {
    cells.reserve(W * H);
    for (size_t i = 0; i < W * H; i++) {
        cells.push_back(new Unit(*copy.cells[i]));
    }
}


template<class Unit>
inline World_T<Unit>::World_T(size_t WIDTH, size_t HEIGHT) : W(WIDTH), H(HEIGHT) {
    cells.reserve(W * H);
    for (size_t i = 0; i < W * H; i++) {
        cells.push_back(new Unit());
    }
}

template<class Unit>
inline World_T<Unit>::~World_T() {
    for (size_t i = 0; i < W * H; i++) {
        Unit *cell = cells.back();
        cells.pop_back();
        delete (cell);
    }
}

template<class Unit>
inline Unit *World_T<Unit>::get(long long int x, long long int y) {
    if (!((x >= 0 && x < W) && (y >= 0 && y < H)))
        return nullptr;
    Unit *cell = cells[x + y * W];
    return cell;
}

template<class Unit>
inline Unit *World_T<Unit>::get(size_t i) {
    if (i >= W * H) return nullptr;
    Unit *cell = cells[i];
    return cell;
}

template<class Unit>
inline Unit *World_T<Unit>::getUnsafe(size_t x, size_t y) {
    assert(x < W);
    assert(y < H);
    Unit *cell = cells[x + y * W];
    assert(cell != nullptr);
    return cell;
}

template<class Unit>
inline Unit *World_T<Unit>::getUnsafe(size_t i) {
    assert(i < W * H);
    Unit *cell = cells[i];
    assert(cell != nullptr);
    return cell;
}

#endif //!WORLD_H