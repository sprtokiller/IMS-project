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

template<class T>
void CustomeCell::doCalc(size_t cores, T* tca) {
	
}

void CustomeCell::fixPaperHeight()
{
	//c = h * (C_MAX - C_MIN) + C_MIN;
}

void CustomeCell::setHeightGradient(double new_hx, double new_hy)
{
	//hx = new_hx;
	//hy = new_hy;
}

const Color CustomeCell::draw() const
{
	Color ph = Color({ 0, 0.5, 1.0, phobia });
	Color wa = Color({ 0, 1.0, 0, water });
	return BitMapWriter::mixColors(wa, ph);
}

//needed for proper linking
namespace CUSTOMECELL {
	void Linking() {
		Paper ca;
		Paper::WorldUnit::doCalc<Paper>(0, &ca);
		exit(EXIT_FAILURE);
	}
}