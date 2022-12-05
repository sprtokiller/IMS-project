/**
 * @brief Paper types definition
 *
 * @file PaperType.h
 * @author xkrizv03
 * @author xkocic02
 */

#pragma once
#ifndef PAPER_TYPES_H
#define PAPER_TYPES_H

// define enum for paper types
enum class PaperType {
    PLAIN = 1 << 0,            //Plain paper-like surface background
    NOISE = 1 << 1,            //Perlin noise surface background
    SBSK = 1 << 2,            //Southern Bleached Softwood Kraft
    SBHK = 1 << 3,            //Southern Bleached Hardwood Kraft
    HYDROPHOBIC = 1 << 4,    //make the paper have small hydrophobic spots
};

inline int operator&(PaperType a, PaperType b) {
    return (static_cast<int>(a) & static_cast<int>(b));
}

inline PaperType operator|(PaperType a, PaperType b) {
    return PaperType(static_cast<int>(a) | static_cast<int>(b));
}

#endif //! PAPER_TYPES_H