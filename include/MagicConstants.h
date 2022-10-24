/**
 * @brief Constants defining the particle behavior
 *
 * @file MagicConstants.h
 * @author xkrizv03
 * @author xkocic02
 */

#ifndef MAGICCONSTANTS_H
#define MAGICCONSTANTS_H

#define um *1
#define mm um*1000
#define cm mm*10
#define m  mm*1000

#define fg *1
#define pg fg*1000
#define ng pg*1000
#define ug ng*1000
#define mg ug*1000
#define g mg*1000

//used for calculation only
namespace RL {
	constexpr float WATER_EVAPORATION_RATE = 47 fg; // per second per 1 um2
	constexpr float WATER_DIFUSION_ALPHA = 2.299e-9 m m;
	constexpr float INK_DIFUSION_BETA = 2e-9 m m;
}

// minimal size unit we simulate
constexpr uint CELL_SIZE = 20 um;
constexpr uint CELL_AREA = CELL_SIZE * CELL_SIZE;

// Simple Cell default bottom height and water capture column height + their changes based on paper structure
constexpr int DEFAULT_B = 500;
constexpr int DEFAULT_C = 1000;
constexpr int B_CHANGE = 500;
constexpr int C_CHANGE = 200;

// particle count of ink brush
constexpr size_t INK_BRUSH_INK_ADD = 2000;
constexpr size_t INK_BRUSH_WATER_ADD = 2000;

constexpr size_t WATER_MAX_GRAPHIC_LEVEL = 30000;
constexpr size_t INK_MAX_GRAPHIC_LEVEL = 2500;

struct PAPER {
	uint FIBER_LEN;
	uint FIBER_INVERSE_DENSITY;
};

constexpr PAPER SBSK = { 3 mm / CELL_SIZE, 50 };
constexpr PAPER SBHK = { 1500 um / CELL_SIZE, 50 };

// simulation size in real life units 
constexpr size_t DEFAULT_WIDTH = 5 cm / CELL_SIZE;
constexpr size_t DEFAULT_HEIGHT = 5 cm / CELL_SIZE;

// ink brush and stroke dimensions
constexpr size_t INK_BRUSH_WIDTH = (5 mm / CELL_SIZE) > DEFAULT_HEIGHT ? DEFAULT_HEIGHT - 4 : (5 mm / CELL_SIZE);
constexpr size_t INK_BRUSH_START_X = DEFAULT_WIDTH / 5;
constexpr size_t INK_BRUSH_END_X = DEFAULT_WIDTH - DEFAULT_WIDTH / 5;
constexpr size_t INK_BRUSH_START_Y = (DEFAULT_HEIGHT - INK_BRUSH_WIDTH) / 2;
constexpr size_t INK_BRUSH_END_Y = (DEFAULT_HEIGHT + INK_BRUSH_WIDTH) / 2;

// water brush and stroke dimensions
constexpr size_t WATER_BRUSH_WATER_ADD = 40000;
constexpr size_t WATER_BRUSH_WIDTH = (5 mm / CELL_SIZE) > DEFAULT_WIDTH ? DEFAULT_WIDTH - 4 : (5 mm / CELL_SIZE);
constexpr size_t WATER_BRUSH_START_X = (DEFAULT_HEIGHT - WATER_BRUSH_WIDTH) / 2;
constexpr size_t WATER_BRUSH_END_X = (DEFAULT_HEIGHT + WATER_BRUSH_WIDTH) / 2;
constexpr size_t WATER_BRUSH_START_Y = DEFAULT_WIDTH / 5;
constexpr size_t WATER_BRUSH_END_Y = DEFAULT_WIDTH - DEFAULT_WIDTH / 5;


/*
WATER_DIFUSION_ALPHA in RL = 2.299·10−9 m2·s−1 at 25 °C

From that we express simulation time step

TIME_STEP = 1 / (WATER_DIFUSION_ALPHA * CELL_SIZE^2)
*/

constexpr float TIME_STEP = CELL_AREA / RL::WATER_DIFUSION_ALPHA;
constexpr float WATER_DIFUSION_ALPHA = RL::WATER_DIFUSION_ALPHA * TIME_STEP / CELL_AREA;
constexpr float WATER_EVAPORATION_RATE = RL::WATER_EVAPORATION_RATE * TIME_STEP * CELL_AREA / 1000;
constexpr float INK_DIFUSION_BETA = RL::INK_DIFUSION_BETA * TIME_STEP / CELL_AREA;;

static_assert(WATER_DIFUSION_ALPHA <= 1, "WATER_DIFUSION_ALPHA must be <= 1 for simulation to work properly!");

/* complex simulation  */
constexpr float C_MIN = 5.0;
constexpr float C_MAX = 10.0;

constexpr float WC_U = 0.1; // watercolor viscosity
constexpr float WC_K = 0.01; // viscous drag
constexpr size_t REL_MAX = 50; // max relax iterations
constexpr float REL_TOL = 0.01; // relax tolerance
constexpr float REL_DAMP = 0.1; // relax damping
 
#undef um
#undef mm
#undef cm
#undef m

#undef fg
#undef pg
#undef ng
#undef ug
#undef mg
#undef g

#endif