/**
 * @brief Random utility functions for the project
 *
 * @file Util.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef UTIL_H
#define UTIL_H

#include <sstream>
#include <iostream>

/// <summary>
/// Returns memory as formated string with units
/// </summary>
std::string sizeToMemory(size_t size);

/// <summary>
/// Prints memory as formated string with units
/// </summary>
void MEMORY(size_t size);

/// <summary>
/// Returns number of cores in system, else 1
/// </summary>
size_t getCores();

/// <summary>
/// Returns size of total system memory in GB, else 1
/// </summary>
unsigned long long getTotalSystemMemory();

//time tests
#include <iostream>
#include <chrono>

/// <summary>
/// Starts FUNC and measures runtime time
/// </summary>
#define TIMEIT(FUNC)\
do {\
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();\
	{\
	FUNC;\
	}\
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();\
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);\
	std::cout << "TIMEIT ";\
	std::cout.width(10);\
	std::cout << left << time_span.count() << " s ";\
	std::cout << #FUNC << endl;\
} while (false);

#endif //UTIL_H