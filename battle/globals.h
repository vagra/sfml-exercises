#pragma once

#include "../common/headers.h"
#include "../common/Grid.h"

#include <dragon-space/LGrid.h>

#define HFSM2_ENABLE_UTILITY_THEORY
#define HFSM2_ENABLE_PLANS
#include <hfsm2/machine.hpp>

constexpr int INIT_WIDTH = 1600;
constexpr int INIT_HEIGHT = 800;

constexpr int ACTORS = 3000;
constexpr int ACTOR_TYPES = 8;
constexpr int ACTIONS = 12;
constexpr int ROW_ACTIONS = ACTIONS;

constexpr int INIT_DIRECTION = 0;

constexpr int FRAME_WIDTH = 80;
constexpr int FRAME_HEIGHT = 80;
constexpr int ORIGIN_X = 39;
constexpr int ORIGIN_Y = 59;

constexpr float SCALE = 1.0f;

constexpr Grid grid = {
	.lcell_w = 50,
	.lcell_h = 50,
	.tcell_w = 100,
	.tcell_h = 100,
	.grid_l = 0,
	.grid_t = 0,
	.grid_r = 2000,
	.grid_b = 1200,
	.agent_w = 20,
	.agent_h = 20,
	.agent_hw = 10,
	.agent_hh = 10
};

const string PNG_DIR = "../assets/heros/";

enum ACTION {
	WALK = 0,
	RUN = 1,
	SIT = 2,
	DEATH = 3,
	FAIL = 4,
	STAND = 5,
	ADVANCE = 6,
	ATTACK = 7,
	INJURE = 8,
	JUMP = 9,
	REST = 10,
	DEFEND = 11
};
