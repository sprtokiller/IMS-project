/**
 * @brief Defines the entry point for the application.
 *
 * @file EntryMain.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include <iostream>
#include "ProgramWrapper.h"
#include "Args.h"

/// <summary>
/// Main entry point.
/// Parse arguments, setup CAutomata and run it.
/// </summary>
/// <param name="argc">Argument count</param>
/// <param name="argv">Argument values</param>
/// <returns>Standard exit codes</returns>
int main(int argc, char* argv[])
{
	std::cout << "Hello CA\n";
	ProgramWrapper pw({ argc, argv });
	std::cout << "Bye CA\n";
	return 0;
}
