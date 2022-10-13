/**
 * @brief Abstract Field class, must be populated with a concrete implementation and rules
 *
 * @file Field.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once
#include <array>

using namespace std;

template <class T,size_t W, size_t H>
class Field
{
public:
	T* get(size_t x, size_t y) {
		return &cells[x + y*W];
	};
private:
	array< T, W*H> cells;
};
