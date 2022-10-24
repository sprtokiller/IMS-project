/**
 * @brief Class and structures for visualization of the simulation
 *
 * @file BitMapWriter.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef BITMAPWRITER_H
#define BITMAPWRITER_H

//source: https://dev.to/muiz6/c-how-to-write-a-bitmap-image-from-scratch-1k6m
#include <cstdint>
#include <fstream>
#include <array>
#include <math.h>
#include "MagicConstants.h"
#include "BitMapTypes.h"
#include "models/PaperCell.h"
#include "models/Paper.h"

struct BmpHeader {
    const char bitmapSignatureBytes[2] = { 'B', 'M' };
    uint32_t sizeOfBitmapFile; // this needs to be redefined
    const uint32_t reservedBytes = 0;
    const uint32_t pixelDataOffset = 54;
};

struct BmpInfoHeader {
    const uint32_t sizeOfThisHeader = 40;
    int32_t width; // this needs to be redefined
    int32_t height; // this needs to be redefined
    const uint16_t numberOfColorPlanes = 1; // must be 1
    const uint16_t colorDepth = 24;
    const uint32_t compressionMethod = 0;
    const uint32_t rawBitmapDataSize = 0; // generally ignored
    const int32_t horizontalResolution = 25400 / CELL_SIZE; // in pixel per meter (based on cell size)
    const int32_t verticalResolution = 25400 / CELL_SIZE; // in pixel per meter
    const uint32_t colorTableEntries = 0;
    const uint32_t importantColors = 0;
};

class BitMapWriter
{
public:
    BitMapWriter() {};
    ~BitMapWriter() {};
    static Color mixColors(Color bg, Color fg);
	bool writeFile(const int32_t w, const int32_t h, const char* name, const Paper::Data& data);
};


#endif