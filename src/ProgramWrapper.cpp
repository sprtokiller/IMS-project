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
#include "output/BitMapWriter.h"
#include "MagicConstants.h"

#include "models/Paper.h"

void PrintWaterDT(const Paper& ca) {
	long long int water = 0;
	for (size_t i = 0; i < ca.W * ca.H; i++)
	{
		water += ca.getOld(i)->getWater() - ca.getNext(i)->getWater();
	}
	printf("WATER  %-10lld DT\n", water);
}

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	srand(time(NULL));
	
	const auto cores = 1; // getCores();
	size_t ram = Paper::aproxSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	MEMORY(ram);
	if (ram > getTotalSystemMemory())
		throw std::runtime_error("Not enough RAM for this program");

	Paper ca(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	TIMEIT(ca.setPaperType(PaperType::NOISE | PaperType::SBSK | PaperType::HYDROPHOBIC));
	TIMEIT(ca.addWaterDrop(ca.W / 2, ca.H / 2, 500));
	//TIMEIT(ca.makeWaterStroke());
	//TIMEIT(ca.makeInkStroke());
	TIMEIT(ca.mirror());
	BitMapWriter bmw;

	const size_t TIME = 1;	/// seconds to simulate
	const size_t STEPS = 1 / TIME_STEP;
	
	/// Iterates simulation by one second and saves image
	auto generateFrame = [&](size_t frame_id) {
		for (size_t i = 0; i < STEPS; i++) {
			ca.run(cores, 1);
			//PrintWaterDT(ca);
		}
		std::string comm = "test";
		comm += std::to_string(frame_id);
		comm += ".bmp";
		bmw.writeFile(ca.W, ca.H, comm.data(), ca.getOld());
	};

	for (size_t frame_id = 0; frame_id < TIME; frame_id++) {
		TIMEIT(generateFrame(frame_id));
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