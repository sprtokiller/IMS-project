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
	std::string_view feed = "";
	std::string_view certfile = "";
	std::string_view certdir = "";
	bool T_flag = false;
	bool a_flag = false;
	bool u_flag = false;
	bool usedefaultcert = true;
	bool useURL = true;
};