/**
 * @brief Class and structures for visualization of the simulation
 *
 * @file BitMapWriter.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "BitMapWriter.h"

bool BitMapWriter::writeFile(const int32_t w, const int32_t h, const char* name, const Cell *data) {
    
	/* test graphics */
    uint min = data[0].B;
    uint max = data[0].B;
    for (size_t i = 0; i < w*h; i++)
    {
        if (data[i].B < min) min = data[i].B;
        if (data[i].B > max) max = data[i].B;
    }
	
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
    size_t numberOfPixels = w * h;
    for (int i = 0; i < numberOfPixels; i++) {
		uint8_t shade = static_cast<uint8_t>(255 - floor(255 * data[i].h));
        Pixel pix = Pixel({ shade, shade, 255});
        fout.write((char*)&pix.blue, sizeof(uint8_t));
        fout.write((char*)&pix.green, sizeof(uint8_t));
        fout.write((char*)&pix.red, sizeof(uint8_t));
    }
    fout.close();
	
    return true;
}