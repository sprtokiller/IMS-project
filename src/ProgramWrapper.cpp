/**
 * @brief Program Wrapper containing main program logic
 *
 * @file ProgramWrapper.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include <stdio.h>
#include <iostream>

#include "ProgramWrapper.h"
#include "Util.h"
#include "BitMapWriter.h"
#include "MagicConstants.h"

#include "models/Paper.h"

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	const auto cores = getCores();
	size_t ram = Paper::aproxSize();
	std::cout << "MEMORY " << printSize(ram) << "\n";
	if(ram > getTotalSystemMemory())
		throw runtime_error("Not enough RAM for this program");
	
	Paper ca;
	TIMEIT(ca.setPaperType(PaperType::NOISE | PaperType::SBSK));
	TIMEIT(ca.makeWaterStroke());
	TIMEIT(ca.makeInkStroke());
	TIMEIT(ca.mirror());
	TIMEIT(ca.run(10, cores, Paper::WorldUnit::doCalc));
	
	return;

	BitMapWriter bmw;
	bmw.writeFile(ca.WIDTH, ca.HEIGHT, "test.bmp", ca.getOld());
}

ProgramWrapper::~ProgramWrapper()
{

}