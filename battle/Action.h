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

	Action* getAction(string name);
	Action* getAction(int index);
};

enum ACTION {
	WALK = 0,
	RUN = 1,
	SIT = 2,
	DIE = 3,
	FAIL = 4,
	STAND = 5,
	ADVANCE = 6,
	ATTACK = 7,
	HIT = 8,
	JUMP = 9,
	REST = 10,
	DEFENCE = 11
};

const array<string, ACTIONS> ACTION_NAMES = {
	"walk",
	"run",
	"sit",
	"die",
	"fail",
	"stand",
	"advance",
	"attack",
	"hit",
	"jump",
	"rest",
	"defence"
};