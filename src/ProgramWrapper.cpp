/**
 * @brief Program Wrapper containing main program logic
 *
 * @file ProgramWrapper.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include <stdio.h>

#include "ProgramWrapper.h"
#include "Util.h"
#include "BitMapWriter.h"
#include "MagicConstants.h"

#include "models/Paper.h"
#include "models/Cell.h"

//time tests
#include <iostream>
#include <chrono>

void doCalc(size_t id, size_t cores, Paper::CAutomata* ca) {
	for (size_t y = id * ca->HEIGHT / cores; y < (id + 1) * ca->HEIGHT / cores; y++) {
		if (y == 0) continue;
		if (y >= ca->HEIGHT - 1) break;
		for (size_t x = 0; x < ca->WIDTH; x++) {
			auto a = ca->getOld(x, y);
			auto b = ca->getNext(x % ca->WIDTH, y % ca->HEIGHT);
		}
	}
}

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	const auto cores = getCores();
	size_t ram = Paper::aproxSize();
	std::cout << "Required memory: " << printSize(ram) << "\n";
	if(ram > getTotalSystemMemory())
		throw runtime_error("Not enough RAM for this program");
	
	Paper ca;
	ca.setPaperType(PaperType::NOISE | PaperType::SBSK);
	
	BitMapWriter bmw;
	bmw.writeFile(ca.WIDTH, ca.HEIGHT, "test.bmp", ca.getOld());
	//bmw.writeFile(ca.WIDTH, ca.HEIGHT, "UkraineNext.bmp", ca.getNext());

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	ca.run(10, cores, Paper::WorldUnit::doCalc);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Time required:   " << time_span.count() << " s" << endl;
}

ProgramWrapper::~ProgramWrapper()
{

}