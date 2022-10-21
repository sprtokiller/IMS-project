#ifndef PAPER_H
#define PAPER_H

#include "template/CAutomata.h"
#include "template/World.h"
#include "MagicConstants.h"
#include "PerlinNoise.h"

#include "models/ComplexCell.h"
#include "models/SimpleCell.h"
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

class Paper: public CAutomata_T<ComplexCell, DEFAULT_WIDTH, DEFAULT_HEIGHT> {
public:
	using Data = CAutomata::World::Data;
	
	Paper();
	~Paper();
	
	void setPaperType(PaperType pt);
	void makeWaterStroke();
	void makeInkStroke();
	void calculateMaxSpeed();
	double getMaxSpeed() const { return maxSpeed; }
	double div_max = 0.0;
private:
	void setPaperPlane(size_t newB = DEFAULT_B, size_t newC = DEFAULT_C);
	void setNoise();
	void addFibres(const PAPER paper);
	void normalize();
	double maxSpeed = 0.0;
public:
	// Inherited via CAutomata_T
	virtual void run(size_t cores, size_t cycles) override;
};

#endif // PAPER_H
