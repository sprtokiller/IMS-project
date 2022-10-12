/**
 * @brief Defines an abstract class for a Cellular Automaton
 *
 * @file CAutomata.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Field.h"
#include "Cell.h"
#include <util.h>

class CAutomata
{
public:
	CAutomata(csize_t w, csize_t h);
	~CAutomata() = default;

	void update();
private:
	const Field* old;
	const Field* next;

	std::pair<std::unique_ptr<const Field>, std::unique_ptr<const Field>> cells;
};