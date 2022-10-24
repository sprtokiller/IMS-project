#ifndef PAPER_H
#define PAPER_H

#include "template/CAutomata.h"
#include "template/World.h"
#include "MagicConstants.h"
#include "PerlinNoise.h"
#include "float.h"

#include "models/ComplexCell.h"
#include "models/SimpleCell.h"
#include "models/CustomeCell.h"

inline int Tmax(int a, int b) { return a > b ? a : b; };
inline float Tmax(float a, float b) { return a > b ? a : b; };
inline int Tmin(int a, int b) { return a < b ? a : b; };
inline float Tmin(float a, float b) { return a < b ? a : b; };

inline float fRand(float fMin, float fMax) {	return fMin + ((float)rand() / RAND_MAX) * (fMax - fMin); }

// define enum for paper types
enum class PaperType
{
	PLAIN = 1 << 0, //Plain paper-like surface background
	NOISE = 1 << 1, //Perlin noise surface background
	SBSK = 1 << 2, //Southern Bleached Softwood Kraft
	SBHK = 1 << 3, //Southern Bleached Hardwood Kraft
	HYDROPHOBIC = 1 << 4, //make the paper have small hydrophobic spots
};

inline int operator&(PaperType a, PaperType b)
{
	return (static_cast<int>(a) & static_cast<int>(b));
}

inline PaperType operator|(PaperType a, PaperType b)
{
	return PaperType(static_cast<int>(a) | static_cast<int>(b));
}

class Paper: public CAutomata_T<CustomeCell> {
public:
	using Data = CAutomata::World::Data;
	
	Paper(size_t WIDTH, size_t HEIGHT): CAutomata(WIDTH,HEIGHT) {
		rand1 = fRand(0.0, 1.0);
		rand2 = fRand(0.0, 1.0);
	}
	~Paper() {}
	
	void setPaperType(PaperType pt);
	void addWaterDrop(size_t x, size_t y, size_t r);
	void makeWaterStroke();
	void makeInkStroke();
	void calculatePaperMaxSpeed();
	void adjustDt() { dt = ceil(1 / (maxSpeed + DBL_MIN)); }
	float getMaxSpeed() const { return maxSpeed; }
	float getDt() const { return dt; }
	float div_max = 0.0;
private:
	float getPaperMaxSpeed() const { return maxSpeed; }
	void setPaperPlane(size_t newB = DEFAULT_B, size_t newC = DEFAULT_C);
	void setNoise();
	void setHydrophobic();
	void addFibres(const PAPER paper);
	void normalize();
	float maxSpeed = 0.0;
	float dt = 0.0;
	float rand1;
	float rand2;
public:
	// Inherited via CAutomata_T
	virtual void run(size_t cores, size_t cycles) override;
};

#endif // PAPER_H
