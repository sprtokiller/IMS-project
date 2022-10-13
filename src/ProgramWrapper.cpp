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
	CAutomata ca;

	for (size_t i = 0; i < 1; i++) {
		for (size_t x = 0; x < ca.WIDTH; x++)
			for (size_t y = 0; y < ca.HEIGHT; y++) {
				auto a = ca.getOld(x, y);
				auto b = ca.getNext((x - i) % ca.WIDTH, (y - 1) % ca.HEIGHT);
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