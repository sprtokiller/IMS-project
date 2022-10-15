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
	PLAIN = 1 << 0, //Plain paper-like surface background
	NOISE = 1 << 1, //Perlin noise surface background
	SBSK = 1 << 2, //Southern Bleached Softwood Kraft
	SBHK = 1 << 3, //Southern Bleached Hardwood Kraft
};

inline int operator&(PaperType a, PaperType b)
{
	return (static_cast<int>(a) & static_cast<int>(b));
}

inline PaperType operator|(PaperType a, PaperType b)
{
	return PaperType(static_cast<int>(a) | static_cast<int>(b));
}

class Paper: public CAutomata_T<SimpleCell, DEFAULT_WIDTH, DEFAULT_HEIGHT> {
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
