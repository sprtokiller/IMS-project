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

#include "template/Field.h"
#include <util.h>

using namespace std;

template <class T, size_t WIDTH, size_t HEIGHT>
class CAutomata
{
public:
	CAutomata() {
		old = new Field<T, WIDTH, HEIGHT>();
		next = new Field<T, WIDTH, HEIGHT>();
	}
	/// <summary>
	/// 
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
private:
	Field<T, WIDTH, HEIGHT>* old;
	Field<T, WIDTH, HEIGHT>* next;
};

#ifdef DEBUG
//force template init
class foo {};
template class CAutomata<foo, 1, 1>;
#endif // DEBUG
