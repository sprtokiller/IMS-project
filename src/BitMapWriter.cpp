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
    size_t maxInk = 0;
    for (auto& cell : data)
    {
		if (cell.getWater() > maxWater)
			maxWater = cell.getWater();
    }

    for (auto& cell : data) {

        // background
		Color r = Color({ 1.0, 1.0, 1.0, 1.0});
		// paper height
        Color paper = Color({ 0.9490, 0.9334, 0.7961, cell.h });
        // Mix it
        r = mixColors(r, paper);
        // water level
        Color water = Color({ 0.45, 0.68, 0.86, std::min(cell.getWater() / WATER_MAX_GRAPHIC_LEVEL, 1.0) });
        // Mix it
        r = mixColors(r, water);
        // ink level
        //Color ink = Color({ 0.0863, 0.1490, 0.2980, min(cell.getInk() / INK_MAX_GRAPHIC_LEVEL, 1.0) });
        // Mix it again
        //r = mixColors(r, ink);
		
        Pixel pix = Pixel({ (uint8_t)floor(255 * r.B), (uint8_t)floor(255 * r.G), (uint8_t)floor(255 * r.R)});

        fout.write((char*)&pix.blue, sizeof(uint8_t));
        fout.write((char*)&pix.green, sizeof(uint8_t));
        fout.write((char*)&pix.red, sizeof(uint8_t));
    }
    fout.close();
    return true;
}

Color BitMapWriter::mixColors(Color bg, Color fg) {
    Color r = Color();
    r.A = 1 - (1 - fg.A) * (1 - bg.A);
    r.R = fg.R * fg.A / r.A + bg.R * bg.A * (1 - fg.A) / r.A;
    r.G = fg.G * fg.A / r.A + bg.G * bg.A * (1 - fg.A) / r.A;
    r.B = fg.B * fg.A / r.A + bg.B * bg.A * (1 - fg.A) / r.A;
    return r;
}