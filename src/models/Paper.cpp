/**
 * @brief Constants defining the particle behavior
 *
 * @file MagicConstants.h
 * @author xkrizv03
 * @author xkocic02
 */

#include "models/Paper.h"
#include <MagicConstants.h>

void Paper::setPaperType(PaperType type) {
    if (type & PaperType::PLAIN)
        setPaperPlane(DEFAULT_B, DEFAULT_C);

    if (type & PaperType::NOISE)
        setNoise();

    if (type & PaperType::SBSK)
        addFibres(SBSK);

    if (type & PaperType::SBHK)
        addFibres(SBHK);

    if (type & PaperType::HYDROPHOBIC)
        setHydrophobic();
}