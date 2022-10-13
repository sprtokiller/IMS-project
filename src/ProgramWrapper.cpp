/**
 * @brief Program Wrapper containing main program logic
 *
 * @file ProgramWrapper.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "ProgramWrapper.h"
#include "template/CAutomata.h"
#include "Cell.h"
#include <stdio.h>

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	const size_t s = 10000;
	CAutomata<Cell, s, s> ca;

	for (size_t i = 0; i < 10; i++) {
		for (size_t x = 0; x < s; x++)
			for (size_t y = 0; y < s; y++) {
				auto a = ca.getOld(x, y);
				auto b = ca.getNext((x - i) % s, (y - 1) % s);
				//a->B = x;
				b->B = y;
			}
		ca.flip();
	}

	ca.flip();
}

ProgramWrapper::~ProgramWrapper()
{
}