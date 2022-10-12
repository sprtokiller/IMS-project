/**
 * @brief Program Wrapper containing main program logic
 *
 * @file ProgramWrapper.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "ProgramWrapper.h"

ProgramWrapper::ProgramWrapper(ProgramDesc d) :pd(d)
{
	CAutomata<int, 10, 10> ca;
	ca.flip();
}

ProgramWrapper::~ProgramWrapper()
{
}