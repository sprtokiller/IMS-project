/**
 * @brief Program Wrapper containing main program logic
 *
 * @file ProgramWrapper.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once

#include "Args.h"

class ProgramWrapper
{
public:
	ProgramWrapper(ProgramDesc d);
	~ProgramWrapper();
	
private:
	ProgramDesc pd;
	//CAutomata paper;
};