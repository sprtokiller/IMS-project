/**
 * @brief CustomeCell class, with our final custom implementation
 *
 * @file CustomeCell.cpp
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/CustomeCell.h"
#include "models/Paper.h"
#include <iomanip>
#include <output/BitMapWriter.h>

template<class T>
void printDebug(T* ca) {
	//std::cout << "[u, v]: \n" << std::setprecision(2) << std::fixed;
	//for (size_t y = 0; y < ca->HEIGHT; y++) {
	//	for (size_t x = 0; x < ca->WIDTH; x++) {
	//		std::cout << "[" << ca->getOld(x, y)->u << ", " << ca->getOld(x, y)->v << "] ";
	//	}
	//	std::cout << "\n";
	//}
}

void CustomeCell::doCalc(size_t cores, CA* tca) {
	
}

void CustomeCell::fixPaperHeight()
{
	//c = h * (C_MAX - C_MIN) + C_MIN;
}

void CustomeCell::setHeightGradient(float new_hx, float new_hy)
{
	//hx = new_hx;
	//hy = new_hy;
}

const Color CustomeCell::draw(Color base) const
{
	Color r = base;
	Color ph = Color({ 0.8, 0.12, 0.0, phobia });
	r = BitMapWriter::mixColors(r, ph);
	
	Color wa = Color({ 0, 0.5, 1.0, Tmax(Tmin(water, 1.0), 0.0) });
	r = BitMapWriter::mixColors(r, wa);
	return r;
}
