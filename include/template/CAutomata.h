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
	CAutomata();

	void flip();
	
	unique_ptr<const Field<T, WIDTH, HEIGHT>> old;
	unique_ptr<const Field<T, WIDTH, HEIGHT>> next;
};

template <class T, size_t WIDTH, size_t HEIGHT>
inline CAutomata<T, WIDTH, HEIGHT>::CAutomata()
{
	old = make_unique<const Field<T, WIDTH, HEIGHT>>();
	next = make_unique<const Field<T, WIDTH, HEIGHT>>();
}

template <class T, size_t WIDTH, size_t HEIGHT>
inline void CAutomata<T, WIDTH, HEIGHT>::flip()
{
	swap(old, next);
}
