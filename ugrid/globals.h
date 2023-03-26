#pragma once

#include "../common/headers.h"
#include "../common/Grid.h"

#include <dragon-space/LGrid.h>


constexpr int INIT_WIDTH = 1600;
constexpr int INIT_HEIGHT = 800;

constexpr int ACTORS = 3000;
constexpr int ACTOR_TYPES = 4;
constexpr int ACTIONS = 1;
constexpr int ROW_ACTIONS = 1;

constexpr int INIT_DIRECTION = 0;

constexpr int FRAME_WIDTH = 64;
constexpr int FRAME_HEIGHT = 64;
constexpr int ORIGIN_X = 32;
constexpr int ORIGIN_Y = 32;

constexpr float SCALE = 0.25f;

constexpr Grid grid = {
	.grid_l = 0,
	.grid_t = 0,
	.grid_r = 2000,
	.grid_b = 1200,
	.cell_w = 40,
	.cell_h = 40,
	.agent_r = 8
};

const string PNG_DIR = "../assets/tanks/";

enum ACTION {
	RUN = 0
};

