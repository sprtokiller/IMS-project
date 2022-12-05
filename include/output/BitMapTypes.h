/**
 * @brief Bitmap types definition
 *
 * @file .h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef BITMAPTYPES_H
#define BITMAPTYPES_H

#include "stdint.h"

struct Pixel {
	uint8_t blue = 255;
	uint8_t green = 255;
	uint8_t red = 255;
};

struct Color {
	float R = 0.0;
	float G = 0.0;
	float B = 0.0;
	float A = 0.0;
};

#endif // !BITMAPTYPES_H