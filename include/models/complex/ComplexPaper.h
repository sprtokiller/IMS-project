#ifndef COMPLEX_PAPER_H
#define COMPLEX_PAPER_H

#include "template/CAutomata.h"
#include "template/World.h"
#include "MagicConstants.h"
#include "PerlinNoise.h"

#include "models/complex/ComplexCell.h"
#include "models/Paper.h"

class ComplexPaper: public CAutomata_T<ComplexCell>, public Paper{
public:
	using Data = CAutomata::World::Data;
	
	ComplexPaper(size_t WIDTH, size_t HEIGHT): CAutomata(WIDTH,HEIGHT) {}
	~ComplexPaper() {}
	
	void addWaterDrop(size_t x, size_t y, size_t r);
	void makeWaterStroke();
	void makeInkStroke();
	void calculatePaperMaxSpeed();
	void adjustDt() { dt = ceil(1 / (maxSpeed + DBL_MIN)); }
	float getMaxSpeed() const { return maxSpeed; }
	float getDt() const { return dt; }
	float div_max = 0.0;
	void normalize();
private:
	float getPaperMaxSpeed() const { return maxSpeed; }
	float maxSpeed = 1.0;
	float dt = 1.0;
public:
	// Inherited via CAutomata_T
	virtual void run(size_t cores, size_t cycles) override;

	void setPaperPlane(size_t newB, size_t newC);
	void setNoise();
	void addFibres(const PAPER type);
	void setHydrophobic();

	const std::vector<Cell*> getData() const {
		std::vector<Cell*> array;
		for (auto cell : getOld()) {
			array.push_back(cell);
		}
		return array;
	}
};

#endif // COMPLEX_PAPER_H
