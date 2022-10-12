/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file Field.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once
#include <array>
#include <util.h>

template <class T,csize_t WIDTH, csize_t HEIGHT>
class Field
{
public:
	Field();
	T get(size_t x, size_t y) const;
private:
	std::array<T, WIDTH* HEIGHT> cells;
};

template<class T, csize_t WIDTH, csize_t HEIGHT>
inline Field<T, WIDTH, HEIGHT>::Field()
{
	cells = std::array<T, WIDTH* HEIGHT>();
}

template<class T, csize_t WIDTH, csize_t HEIGHT>
inline T Field<T, WIDTH, HEIGHT>::get(size_t x, size_t y) const
{
	return cells[x + y * WIDTH];
}
