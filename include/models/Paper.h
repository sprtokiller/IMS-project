#ifndef PAPER_H
#define PAPER_H

#include "models/PaperType.h"
#include "models/PaperMath.h"
#include "models/PaperCell.h"
#include "MagicConstants.h"
#include <vector>

class Paper{
public:
	virtual ~Paper() {};

	void setPaperType(PaperType pt);

	virtual void setPaperPlane(size_t newB, size_t newC) {};
	virtual void setNoise() {};
	virtual void addFibres(const PAPER type) {};
	virtual void setHydrophobic() {};

	virtual const std::vector<Cell*> getData() const = 0;
};

#endif //! PAPER_H
