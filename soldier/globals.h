#pragma once

#include "../common/headers.h"

#include <dragon-space/LGrid.h>
constexpr int INIT_WIDTH = 1600;
constexpr int INIT_HEIGHT = 800;

constexpr int ACTORS = 500;
constexpr int ACTOR_TYPES = 6;
constexpr int ACTIONS = 8;
constexpr int ROW_ACTIONS = 4;

constexpr int INIT_DIRECTION = 0;

constexpr int FRAME_WIDTH = 100;
constexpr int FRAME_HEIGHT = 80;
constexpr int ORIGIN_X = 50;
constexpr int ORIGIN_Y = 56;

constexpr float SCALE = 0.5f;

constexpr int AGENT_WIDTH = 16;
constexpr int AGENT_HEIGHT = 16;
constexpr int AGENT_HALFW = 8;
constexpr int AGENT_HALFH = 8;

constexpr int GRID_WIDTH = 2000;
constexpr int GRID_HEIGHT = 1200;

constexpr int LCELL_WIDTH = 50;
constexpr int LCELL_HEIGHT = 50;
constexpr int TCELL_WIDTH = 100;
constexpr int TCELL_HEIGHT = 100;

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

