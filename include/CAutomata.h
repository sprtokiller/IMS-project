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

class CAutomata
{
public:
	CAutomata(size_t w, size_t h);
	~CAutomata() = default;
private:
	std::pair<std::unique_ptr<Field>, std::unique_ptr<Field>> cells;
};