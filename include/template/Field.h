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

using namespace std;

template <class T,csize_t WIDTH, csize_t HEIGHT>
class Field
{
public:
	T* get(size_t x, size_t y) {
		return &cells[x + y*WIDTH];
	};
private:
	array< T, WIDTH*HEIGHT> cells;
};

#if DEBUG
//force template init
class bar {};
template class Field<bar, 1, 1>;
#endif // DEBUG
