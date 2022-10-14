/**
 * @brief Random utility functions for the project
 *
 * @file Util.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef UTIL_H
#define UTIL_H

using namespace std;

typedef unsigned int uint;

#include <sstream>
#include <iostream>
inline string to_string(uint value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

/// <summary>
/// Prints size of object in formated way
/// </summary>
/// <param name="size">
/// Return parameter of func sizeof()
/// </param>
inline string printSize(size_t size) {
	string msg;
	
	uint unit = 0;
	size_t remain = size;
	while (size / 1024)
	{
		remain = size;
		size /= 1024;
		unit++;
	}
	msg += to_string(size);
	if (remain != 0) {
		msg += ",";
		msg += to_string(remain);
	}
		
	switch (unit)
	{
	case 0:
		msg += "B";
		break;
	case 1:
		msg += "KB";
		break;
	case 2:
		msg += "MB";
		break;
	case 3:
		msg += "GB";
		break;
	case 6:
		msg += "TB";
		break;
	case 7:
		msg += "PB";
		break;
	default:
		return "INVALID";
		break;
	}
	return msg;
}

#include <thread>
/// <summary>
/// Returns number of cores in system, else 1
/// </summary>
uint getCores() {
	uint i = std::thread::hardware_concurrency();
	return i == 0 ? 1 : i;
}

#ifdef __linux__
//for sysconfig systems
#include <unistd.h>
unsigned long long getTotalSystemMemory()
{
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return pages * page_size;
}
#elif _WIN32
//for windows systems
#include <windows.h>
unsigned long long getTotalSystemMemory()
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
}
#else
//for other systems
unsigned long long getTotalSystemMemory()
{
	return 2;
}
#endif

#endif