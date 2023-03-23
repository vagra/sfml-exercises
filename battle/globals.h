#pragma once

#include "../common/headers.h"

#include <dragon-space/LGrid.h>

#define HFSM2_ENABLE_UTILITY_THEORY
#define HFSM2_ENABLE_PLANS
#include <hfsm2/machine.hpp>

constexpr int INIT_WIDTH = 1600;
constexpr int INIT_HEIGHT = 800;

constexpr int ACTOR_TYPES = 8;
constexpr int ACTIONS = 12;

constexpr int DIRECTIONS = 8;
constexpr int INIT_DIRECTION = 6;

constexpr int MAX = 2000;

constexpr int FRAME_WIDTH = 80;
constexpr int FRAME_HEIGHT = 80;
constexpr int ORIGIN_X = 39;
constexpr int ORIGIN_Y = 59;

constexpr float SCALE = 1.0f;

constexpr int AGENT_WIDTH = 20;
constexpr int AGENT_HEIGHT = 20;
constexpr int AGENT_HALFW = 10;
constexpr int AGENT_HALFH = 10;

constexpr int GRID_WIDTH = 2000;
constexpr int GRID_HEIGHT = 1200;

constexpr int LCELL_WIDTH = 50;
constexpr int LCELL_HEIGHT = 50;
constexpr int TCELL_WIDTH = 100;
constexpr int TCELL_HEIGHT = 100;

const string PNG_DIR = "../assets/heros/";

const string ACTOR_PNG = "helo{}.png";

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

const array<string, ACTIONS> ACTION_NAMES = {
	"walk",
	"run",
	"sit",
	"death",
	"fail",
	"stand",
	"advance",
	"attack",
	"injure",
	"jump",
	"rest",
	"defend"
};