/**
 * @brief Takes care of program startup arguments and sets all corresponding flags
 *
 * @file Args.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include <Args.h>
#include <iostream>
#include <stdlib.h>
#include <getopt.h>

/// <summary>
/// Prints the usage of this script
/// </summary>
void usage()
{
	std::cerr <<
		R"(Usage: ./blah [flags?]"
		  "	-T (if present, shows additional information about last change time)\n"
		  "Arguments can be in any order\n)";
}

/// <summary>
/// Parses program arguments with option long_options[] and sets corresponding flags
/// </summary>
/// <param name="argc">Argument count</param>
/// <param name="argv">Array of arguments</param>
ProgramDesc::ProgramDesc(int argc, char* argv[])
{
	int c;
	opterr = 0;

	if (argc < 1)
	{
		usage();
		exit(EXIT_FAILURE);
	}
	
	while ((c = getopt(argc, argv, "vh")) != -1)
		switch (c)
		{
		case 'v':
			verbose = true;
			break;
		case 'h':
			usage();
			exit(EXIT_SUCCESS);
			break;
		default:
			usage();
			exit(EXIT_FAILURE);
			break;
		}
}
