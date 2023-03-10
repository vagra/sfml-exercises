#pragma once

#include "globals.h"

struct Action
{
	string name;
	int frames{};
	int start{};
};

struct ActionSet
{
	string name;
	unordered_map<string, unique_ptr<Action>> actions;
	vector<string> names;

	Action* getAction(string name) {
		if (actions.find(name) != actions.end()) {
			return actions[name].get();
		}
		else {
			return nullptr;
		}
	}

	Action* getAction(int index) {
		return getAction(names.at(index));
	}
};

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