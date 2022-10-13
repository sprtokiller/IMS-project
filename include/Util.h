#pragma once

typedef unsigned int uint;

#include <iostream>
/// <summary>
/// Prints size of object in formated way
/// </summary>
/// <param name="size">
/// Return parameter of func sizeof()
/// </param>
inline void printSize(size_t size) {
	uint unit = 0;
	size_t remain = size;
	while (size / 1024)
	{
		remain = size;
		size /= 1024;
		unit++;
	}
	cout << "Required space " << size;
	if (remain != size)
		cout << "," << remain;

	switch (unit)
	{
	case 0:
		cout << "B" << endl;
		break;
	case 1:
		cout << "KB" << endl;
		break;
	case 2:
		cout << "MB" << endl;
		break;
	case 3:
		cout << "GB" << endl;
		break;
	case 6:
		cout << "TB" << endl;
		break;
	case 7:
		cout << "PB" << endl;
		break;
	default:
		cout << "INVALID" << endl;
		break;
	}
}

#include <thread>
/// <summary>
/// Returns number of cores in system, else 1
/// </summary>
uint getCores() {
	uint i = std::thread::hardware_concurrency();
	return i == 0 ? 1 : i;
}