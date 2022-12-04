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
#include "models/custom/CustomPaper.h"
#include "models/simple/SimplePaper.h"

using PaperUsed = CustomPaper;

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	srand(time(NULL));
	
	const auto cores = getCores();
	size_t ram = PaperUsed::aproxSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	MEMORY(ram);
	if (ram > getTotalSystemMemory())
		throw std::runtime_error("Not enough RAM for this program");

	PaperUsed ca(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	TIMEIT(ca.setPaperType(PaperType::NOISE | PaperType::SBSK | PaperType::HYDROPHOBIC));
	TIMEIT(ca.addWaterDrop(ca.W / 2, ca.H / 2, 500));
	//TIMEIT(ca.makeWaterStroke());
	//TIMEIT(ca.makeInkStroke());
    ca.flip();
	TIMEIT(ca.mirror());
	BitMapWriter bmw;

	const size_t FRAMES = 20;	/// seconds to simulate
	const size_t STEPS_PER_FRAME = 30; /// TIME_STEP;
	
	auto generateFrame = [&](size_t frame_id) {
		fprintf(stderr, "\t");
		TIMEIT(ca.run(cores, STEPS_PER_FRAME));
		std::string comm = "new_test" + std::to_string(frame_id) + ".bmp";
        fprintf(stderr, "\t");
        TIMEIT(bmw.writeFile(ca.W, ca.H, comm.data(), &ca));
	};

	for (size_t frame_id = 0; frame_id < FRAMES; frame_id++) {
		TIMEIT(generateFrame(frame_id));
	}

	// create an animation
	system("convert -delay 30 -resize 20% -loop 0 new_test*.bmp animation.gif");
	// show the animation
	system("eog --disable-gallery animation.gif");
	// delete not necessary pictures
	system("rm new_test*.bmp animation.gif");
}

ProgramWrapper::~ProgramWrapper()
{

}