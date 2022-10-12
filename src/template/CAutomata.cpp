#include "template/CAutomata.h"
/**
 * @brief Defines an abstract class for a Cellular Automaton
 *
 * @file CAutomata.cpp
 * @author xkrizv03
 * @author xkocic02
 */

CAutomata::CAutomata(csize_t w, csize_t h)
{
	cells = std::make_pair(std::make_unique<const Field>(), std::make_unique<const Field>());
	
	old = cells.first.get();
	next = cells.second.get();
}

void CAutomata::update()
{
	std::swap(old, next);
}
