#include "CAutomata.h"
/**
 * @brief Defines an abstract class for a Cellular Automaton
 *
 * @file CAutomata.cpp
 * @author xkrizv03
 * @author xkocic02
 */

CAutomata::CAutomata(size_t w, size_t h)
{
	cells = std::make_pair(std::make_unique<Field>(w, h), std::make_unique<Field>(w, h));
}
