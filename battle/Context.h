#pragma once

#include "globals.h"
#include "Action.h"
#include "ActionManager.h"

constexpr int MIN_ROUNDS = 1;
constexpr int MAX_ROUNDS = 5;

constexpr int MIN_RUN_SPEED = 10;
constexpr int MAX_RUN_SPEED = 20;
constexpr int MIN_WALK_SPEED = 10;
constexpr int MAX_WALK_SPEED = 5;

struct Context {
	int actor_id{};
	int actor_type{};
	ACTION action{};
	string action_name{};
	int frames{};
	int frame{};
	int rounds{};
	int round{};
	int speed{};
	bool end{};

	void init(ACTION action_id) {
		action = action_id;
		action_name = ActionManager::getActionName(action_id);

		frames = ActionManager::getAction(actor_type, action_id)->frames;
		frame = 0;

		rounds = rand() % (MAX_ROUNDS + 1 - MIN_ROUNDS) + MIN_ROUNDS;
		round = 0;

		end = false;
		
		// cout << fmt::format("{} -> {}: {}*{}  {}", actor_id, action_name, frames, rounds, speed) << endl;
	}

	void step() noexcept {
		frame++;
		if (frame >= frames) {
			frame = 0;
			round++;
			if (round >= rounds) {
				round = 0;
				end = true;
			}
		}
	}

	void slow() noexcept {
		speed = rand() % (MAX_WALK_SPEED - MIN_WALK_SPEED) + MIN_WALK_SPEED;
	}

	void fast() noexcept {
		speed = rand() % (MAX_RUN_SPEED - MIN_RUN_SPEED) + MIN_RUN_SPEED;
	}

	void stand() noexcept {
		speed = 0;
	}
};