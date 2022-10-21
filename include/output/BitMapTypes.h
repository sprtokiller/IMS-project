#ifndef BITMAPTYPES_H
#define BITMAPTYPES_H

#include "stdint.h"

struct Pixel {
	uint8_t blue = 255;
	uint8_t green = 255;
	uint8_t red = 255;
};

struct Color {
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;
	double A = 0.0;
};

#endif // !BITMAPTYPES_H