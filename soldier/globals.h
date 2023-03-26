#pragma once

#include "../common/headers.h"
#include "../common/Grid.h"

#include <dragon-space/LGrid.h>


constexpr int INIT_WIDTH = 1600;
constexpr int INIT_HEIGHT = 800;

constexpr int ACTORS = 3000;
constexpr int ACTOR_TYPES = 6;
constexpr int ACTIONS = 8;
constexpr int ROW_ACTIONS = 4;

constexpr int INIT_DIRECTION = 0;

constexpr int FRAME_WIDTH = 100;
constexpr int FRAME_HEIGHT = 80;
constexpr int ORIGIN_X = 50;
constexpr int ORIGIN_Y = 56;

constexpr float SCALE = 0.5f;

constexpr Grid grid = {
	.lcell_w = 50,
	.lcell_h = 50,
	.tcell_w = 100,
	.tcell_h = 100,
	.grid_l = 0,
	.grid_t = 0,
	.grid_r = 2000,
	.grid_b = 1200,
	.agent_w = 16,
	.agent_h = 16,
	.agent_hw = 8,
	.agent_hh = 8
};

const string PNG_DIR = "../assets/soldiers/";

enum ACTION {
	ATTACK = 0,
	DEFEND = 1,
	DEATH = 2,
	INJURE = 3,
	STAND = 4,
	JUMP = 5,
	WALK = 6,
	RUN = 7
};

