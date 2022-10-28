#ifndef SIMPLE_PAPER_H
#define SIMPLE_PAPER_H

#include "template/CAutomata.h"
#include "template/World.h"
#include "MagicConstants.h"
#include "PerlinNoise.h"
#include "float.h"

#include "models/simple/SimpleCell.h"
#include "models/Paper.h"

class SimplePaper: public CAutomata_T<SimpleCell>, public Paper {
public:
	using Data = CAutomata::World::Data;
	
	SimplePaper(size_t WIDTH, size_t HEIGHT): CAutomata(WIDTH,HEIGHT) {
		rand1 = fRand(0.0, 1.0);
		rand2 = fRand(0.0, 1.0);
	}
	~SimplePaper() {}
	
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
	void normalize();
	float maxSpeed = 0.0;
	float dt = 0.0;
	float rand1;
	float rand2;
public:
	// Inherited via CAutomata_T
	virtual void run(size_t cores, size_t cycles) override;
	
	void setPaperPlane(size_t newB, size_t newC);
	void setNoise();
	void addFibres(const PAPER paper);
	void setHydrophobic();

	const std::vector<Cell*> getData() const {
		return std::vector<Cell*>{};//TODO
	}
};

#endif // SIMPLE_PAPER_H
