/**
 * @brief Structures for argument parsing
 *
 * @file Args.h
 * @author xkrizv03
 * @author xkocic02
 */
#pragma once
#include <string_view>

struct ProgramDesc
{
public:
	ProgramDesc(int argc, char* argv[]);
public:
	bool verbose = false;
};