#pragma once

#include "globals.h"
#include "Action.h"

struct Context {
	int actor_type{};
	ACTION action{};
	int frames{};
	int timer{};
	int step{};
	int direction{};
};