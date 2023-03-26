#pragma once

#include "../common/headers.h"


constexpr int INIT_WIDTH = 1600;
constexpr int INIT_HEIGHT = 800;

constexpr int ACTORS = 3000;
constexpr int ACTOR_TYPES = 17;
constexpr int ACTIONS = 3;
constexpr int ROW_ACTIONS = 3;

constexpr int INIT_DIRECTION = 0;

constexpr int FRAME_WIDTH = 100;
constexpr int FRAME_HEIGHT = 100;
constexpr int ORIGIN_X = 50;
constexpr int ORIGIN_Y = 70;

constexpr float SCALE = 0.7f;

const string PNG_DIR = "../assets/characters/";

enum ACTION {
	WALK = 0,
	RUN = 1,
	RAISE = 2
};

