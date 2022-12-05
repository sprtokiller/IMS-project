/**
 * @brief Paper CA Math functions definition
 *
 * @file PaperMath.h
 * @author xkrizv03
 * @author xkocic02
 */


#ifndef PAPER_MATH_H
#define PAPER_MATH_H

#include <cstdlib>
#include <float.h>

inline int Tmax(int a, int b) { return a > b ? a : b; };
inline float Tmax(float a, float b) { return a > b ? a : b; };
inline int Tmin(int a, int b) { return a < b ? a : b; };
inline float Tmin(float a, float b) { return a < b ? a : b; };
inline float fRand(float fMin, float fMax) { return fMin + ((float)rand() / RAND_MAX) * (fMax - fMin); }

#endif //! PAPER_MATH_H
