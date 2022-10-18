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
	MEMORY(ram);
	if (ram > getTotalSystemMemory())
		throw runtime_error("Not enough RAM for this program");

	Paper ca;
	TIMEIT(ca.setPaperType(PaperType::NOISE | PaperType::SBSK));
	TIMEIT(ca.makeWaterStroke());
	TIMEIT(ca.makeInkStroke());
	TIMEIT(ca.mirror());
	BitMapWriter bmw;

	//generate images
	size_t max = 200;
	for (size_t i = 0; i < max; i++) {
		TIMEIT(ca.run(1, cores, Paper::WorldUnit::doCalc));
		std::string comm = "test";
		comm += to_string(i);
		comm += ".bmp";
		bmw.writeFile(ca.WIDTH, ca.HEIGHT, comm.data(), ca.getOld());
	}
	
	//show images
	std::string comm = "eog --disable-gallery ";
	comm += "test0.bmp";
	system(comm.data());

	//remove all
	system("rm test*.bmp");
}

ProgramWrapper::~ProgramWrapper()
{

}