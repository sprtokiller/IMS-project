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
#include <iostream>

void doCalc(size_t id, size_t t_count, CAutomata ca) {
	for (size_t y = id * ca.HEIGHT / t_count; y < (id + 1) * ca.HEIGHT / t_count; y++) {
		if (y == 0) continue;
		if (y >= ca.HEIGHT - 1) break;
		for (size_t x = 0; x < ca.WIDTH; x++) {
			//auto a = ca.getOld(x, y);
			//auto b = ca.getNext((x - i) % ca.WIDTH, (y - 1) % ca.HEIGHT);
			//a->B = x;
			//b->B = y;
		}
	}
	cout << "Foo" << id << endl;
}

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	CAutomata ca;
	ca.run(10, 8, doCalc);
}

ProgramWrapper::~ProgramWrapper()
{
}