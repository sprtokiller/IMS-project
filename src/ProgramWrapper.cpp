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
#include "models/SimpleCell.h"

template <typename T>
Cell_T* abstracFactory() {
	return (Cell_T*) new T();
}

#define CELL_TYPE SimpleCell
auto factory = abstracFactory<CELL_TYPE>;

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	srand(time(NULL));
	
	const auto cores = getCores();
	const size_t TIME = 10;	/// seconds to simulate
	const size_t STEPS = 1; // / TIME_STEP;

	size_t ram = Paper::aproxSize<CELL_TYPE>(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	MEMORY(ram);
	if (ram > getTotalSystemMemory())
		throw std::runtime_error("Not enough RAM for this program");

	Paper ca(DEFAULT_WIDTH, DEFAULT_HEIGHT, factory);
	TIMEIT(ca.setPaperType(PaperType::NOISE | PaperType::SBSK | PaperType::HYDROPHOBIC));
	//TIMEIT(ca.addWaterDrop(ca.W / 2, ca.H / 2, 500));
	////TIMEIT(ca.makeWaterStroke());
	////TIMEIT(ca.makeInkStroke());
	TIMEIT(ca.mirror());
	BitMapWriter bmw;
	
	/// Iterates simulation by one second and saves image
	auto generateFrame = [&](size_t frame_id) {
		ca.run(cores, STEPS, CELL_TYPE::doCalc);
		std::string comm = "test";
		comm += std::to_string(frame_id);
		comm += ".bmp";
		bmw.writeFile(ca.W, ca.H, comm.data(), ca.getOld());
	};

	for (size_t frame_id = 0; frame_id < TIME; frame_id++) {
		TIMEIT(generateFrame(frame_id));
	}

	int ret = 0;
	const char* cmd = nullptr;
	// create an animation
	cmd = "convert -delay 50 -resize 20% -loop 0 test*.bmp animation.gif";
	ret = system(cmd);
	if (ret == -1) fprintf(stderr,"error executing '%s'",cmd);
	// show the animation
	cmd = "eog --disable-gallery animation.gif";
	ret = system(cmd);
	if (ret == -1) fprintf(stderr, "error executing '%s'", cmd);
	// delete not necessary pictures
	cmd = "rm test*.bmp";
	ret = system(cmd);
	if (ret == -1) fprintf(stderr, "error executing '%s'", cmd);
}

ProgramWrapper::~ProgramWrapper()
{

}