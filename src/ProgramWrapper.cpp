/**
 * @brief Program Wrapper containing main program logic
 *
 * @file ProgramWrapper.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include <stdio.h>

#include "ProgramWrapper.h"
#include "template/CAutomata.h"
#include "Cell.h"
#include "Util.h"
#include "BitMapWriter.h"
#include "MagicConstants.h"

//time tests
#include <iostream>
#include <chrono>

using CAutomata = CAutomata_T<Cell, DEFAULT_WIDTH, DEFAULT_HEIGHT>;

void doCalc(size_t id, size_t cores, CAutomata* ca) {
	for (size_t y = id * ca->HEIGHT / cores; y < (id + 1) * ca->HEIGHT / cores; y++) {
		if (y == 0) continue;
		if (y >= ca->HEIGHT - 1) break;
		for (size_t x = 0; x < ca->WIDTH; x++) {
			auto a = ca->getOld(x, y);
			auto b = ca->getNext(x % ca->WIDTH, y % ca->HEIGHT);
			b->B = y + a->B * x;
		}
	}
}

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	const auto cores = getCores();
	size_t ram = CAutomata::aproxSize();
	std::cout << "Required memory: " << printSize(ram) << "\n";
	if(ram > getTotalSystemMemory())
		throw runtime_error("Not enough RAM for this program");
	
	CAutomata ca;
	ca.setPaperType(PaperType::NOISE);
	
	BitMapWriter bmw;
	bmw.writeFile(ca.WIDTH, ca.HEIGHT, "noise.bmp", ca.getOld(0, 0));
	//bmw.writeFile(ca.WIDTH, ca.HEIGHT, "UkraineNext.bmp", ca.getNext(0, 0));

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	ca.run(10, cores, doCalc);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Time required = " << time_span.count() << " seconds" << endl;
}

ProgramWrapper::~ProgramWrapper()
{

}