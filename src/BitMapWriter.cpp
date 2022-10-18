/**
 * @brief Class and structures for visualization of the simulation
 *
 * @file BitMapWriter.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "BitMapWriter.h"

bool BitMapWriter::writeFile(const int32_t w, const int32_t h, const char* name, const Paper::Data& data) {
   
    std::ofstream fout(name, std::ios::binary);

    BmpHeader header = BmpHeader();
    header.sizeOfBitmapFile = header.pixelDataOffset + w * h * 3;
	
    BmpInfoHeader infoheader = BmpInfoHeader();
    infoheader.width = w;
    infoheader.height = h;

    fout.write(header.bitmapSignatureBytes, 2);
    fout.write((char*)&header.sizeOfBitmapFile, sizeof(uint32_t));
    fout.write((char*)&header.reservedBytes, sizeof(uint32_t));
    fout.write((char*)&header.pixelDataOffset, sizeof(uint32_t));

    fout.write((char*)&infoheader.sizeOfThisHeader, sizeof(uint32_t));
    fout.write((char*)&infoheader.width, sizeof(int32_t));
    fout.write((char*)&infoheader.height, sizeof(int32_t));
    fout.write((char*)&infoheader.numberOfColorPlanes, sizeof(uint16_t));
    fout.write((char*)&infoheader.colorDepth, sizeof(uint16_t));
    fout.write((char*)&infoheader.compressionMethod, sizeof(uint32_t));
    fout.write((char*)&infoheader.rawBitmapDataSize, sizeof(uint32_t));
    fout.write((char*)&infoheader.horizontalResolution, sizeof(int32_t));
    fout.write((char*)&infoheader.verticalResolution, sizeof(int32_t));
    fout.write((char*)&infoheader.colorTableEntries, sizeof(uint32_t));
    fout.write((char*)&infoheader.importantColors, sizeof(uint32_t));

    // writing pixel data, TODO, replace with automaton visualization
    size_t maxWater = 0;
    size_t minWater = -1;
    for (auto& cell : data)
    {
		if (cell.getWater() > maxWater)
			maxWater = cell.getWater();
		if (cell.getWater() < minWater)
			minWater = cell.getWater();
    }

    for (auto& cell : data) {

        // background, paper height
        Color bg = Color({ 1.0, 1.0 - cell.h, 1.0 - cell.h, 0.50 });
        // foreground, water level
        Color fg = Color({ 1.0 - cell.getWater() / maxWater , 1.0 - cell.getWater() / maxWater , 1.0, 0.5 });
        // The result
        Color r = Color();
        r.A = 1 - (1 - fg.A) * (1 - bg.A);
        r.R = fg.R * fg.A / r.A + bg.R * bg.A * (1 - fg.A) / r.A;
        r.G = fg.G * fg.A / r.A + bg.G * bg.A * (1 - fg.A) / r.A;
        r.B = fg.B * fg.A / r.A + bg.B * bg.A * (1 - fg.A) / r.A;
		
        Pixel pix = Pixel({ (uint8_t)floor(255 * r.B), (uint8_t)floor(255 * r.G), (uint8_t)floor(255 * r.R)});

        fout.write((char*)&pix.blue, sizeof(uint8_t));
        fout.write((char*)&pix.green, sizeof(uint8_t));
        fout.write((char*)&pix.red, sizeof(uint8_t));
    }
    fout.close();
    std::string comm = "feh " + std::string(name);
    system(comm.data());
    return true;
}