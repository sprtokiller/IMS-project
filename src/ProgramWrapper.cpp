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

#include "models/complex/ComplexPaper.h"
#include "models/simple/SimplePaper.h"

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	srand(time(NULL));
	
	const auto cores = getCores();
	size_t ram = ComplexPaper::aproxSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	MEMORY(ram);
	if (ram > getTotalSystemMemory())
		throw std::runtime_error("Not enough RAM for this program");

	SimplePaper ca(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	TIMEIT(ca.setPaperType(PaperType::NOISE | PaperType::SBSK | PaperType::HYDROPHOBIC));
	TIMEIT(ca.addWaterDrop(ca.W / 2, ca.H / 2, 500));
	//TIMEIT(ca.makeWaterStroke());
	//TIMEIT(ca.makeInkStroke());
	TIMEIT(ca.mirror());
	BitMapWriter bmw;

	const size_t TIME = 10;	/// seconds to simulate
	const size_t STEPS = 1; /// TIME_STEP;
	
	/// Iterates simulation by one second and saves image
	auto generateFrame = [&](size_t frame_id) {
		for (size_t i = 0; i < STEPS; i++) {
			fprintf(stderr, "\t");
			TIMEIT(ca.run(cores, 1));
		}
		std::string comm = "test";
		comm += std::to_string(frame_id);
		comm += ".bmp";
		bmw.writeFile(ca.W, ca.H, comm.data(), &ca);
	};

	for (size_t frame_id = 0; frame_id < TIME; frame_id++) {
		TIMEIT(generateFrame(frame_id));
	}

	// create an animation
	system("convert -delay 50 -resize 20% -loop 0 test*.bmp animation.gif");
	// show the animation
	system("eog --disable-gallery animation.gif");
	// delete not necessary pictures
	system("rm test*.bmp");
}

ProgramWrapper::~ProgramWrapper()
{

}