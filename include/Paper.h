#ifndef PAPER_H
#define PAPER_H

#include "template/CAutomata.h"
#include "template/World.h"
#include "Cell.h"
#include "MagicConstants.h"
#include "PerlinNoise.h"

// define enum for paper types
enum class PaperType
{
	DEFAULT, //Plain paper-like surface
	NOISE, //Perlin noise world
	SBSK, //Southern Bleached Softwood Kraft
	SBHK, //Southern Bleached Hardwood Kraft
	CF //Cotton Fabric
};

class Paper: public CAutomata_T<Cell, DEFAULT_WIDTH, DEFAULT_HEIGHT> {
public:
	Paper();
	~Paper();
	
	void setPaperType(PaperType pt);
private:
	void setPaperPlane(size_t newB = DEFAULT_B, size_t newC = DEFAULT_C);
	void setNoise();
	void addFibres(const PAPER paper);
	void normalize();
};

#endif // PAPER_H
