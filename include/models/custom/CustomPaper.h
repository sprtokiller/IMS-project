#ifndef CUSTOM_PAPER_H
#define CUSTOM_PAPER_H

#include "template/CAutomata.h"
#include "template/World.h"
#include "MagicConstants.h"
#include "PerlinNoise.h"
#include "float.h"

#include "models/custom/CustomCell.h"
#include "models/Paper.h"

class CustomPaper : public CAutomata_T<CustomCell>, public Paper{
public:
	using Data = CAutomata::World::Data;
	
	CustomPaper(size_t WIDTH, size_t HEIGHT): CAutomata(WIDTH,HEIGHT){
		rand1 = fRand(0.0, 1.0);
		rand2 = fRand(0.0, 1.0);
	}
	~CustomPaper() {}
	
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
	void setHydrophobic();
	void addFibres(const PAPER paper);

	virtual const std::vector<Cell*> getData() const override {
		std::vector<Cell*> array;
		for (auto cell : getOld()) {
			array.push_back(cell);
		}
		return array;
	};
};

#endif // CUSTOM_PAPER_H
