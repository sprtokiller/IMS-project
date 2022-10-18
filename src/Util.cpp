#include "Util.h"

#include <thread>

/// <summary>
/// Returns value as string
/// </summary>
std::string to_string(uint value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

std::string sizeToMemory(size_t size) {
	std::string msg;

	uint unit = 0;
	size_t remain = 0;
	while (size / 1024) {
		remain = size;
		size /= 1024;
		unit++;
	}

	//leave last unit after decimal
	while (remain / 10) { remain /= 10; }

	msg += to_string(size);
	if (remain != 0) {
		msg += ",";
		msg += to_string(remain);
	}

	while (msg.length() < 10) msg += " ";

	switch (unit)
	{
	case 0:
		msg += " B";
		break;
	case 1:
		msg += " KB";
		break;
	case 2:
		msg += " MB";
		break;
	case 3:
		msg += " GB";
		break;
	case 6:
		msg += " TB";
		break;
	case 7:
		msg += " PB";
		break;
	default:
		return "INVALID";
		break;
	}
	return msg;
}

void MEMORY(size_t size) {
	std::cout << "MEMORY " << sizeToMemory(size) << "\n";
}

size_t getCores() {
	size_t i = std::thread::hardware_concurrency();
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
unsigned long long getTotalSystemMemory(){return 1;}
#endif



