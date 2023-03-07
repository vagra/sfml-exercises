#pragma once

#include "globals.h"
#include "Action.h"

struct Context {
	Action* action = nullptr;
	int timer{};
	int step{};
	int direction{};
};