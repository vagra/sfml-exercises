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
	int stiffs{};
	int hits{};
	int rounds{};
	int round{};
	int speed{};
	bool end{};

	void init(ACTION action_id, bool once = false, bool dodge = true) {
		action = action_id;
		action_name = ActionManager::getActionName(action_id);

		frames = ActionManager::getAction(actor_type, action_id)->frames;
		frame = 0;

		if (once) {
			rounds = 1;
		}
		else {
			rounds = rand() % (MAX_ROUNDS + 1 - MIN_ROUNDS) + MIN_ROUNDS;
		}
		round = 0;

		if (dodge) {
			hits = 0;
		}

		end = false;
		
		// cout << fmt::format("{} -> {}: {}*{}  {}", actor_id, action_name, frames, rounds, speed) << endl;
	}

	void step(bool dodge = true) noexcept {
		frame++;

		if (dodge && (frame >= frames)) {
			frame = 0;
			round++;
			if (round >= rounds) {
				round = 0;
				end = true;
			}
			return;
		}

		if (!dodge && (frame >= stiffs)) {
			frame = 0;
			round++;
			if (round >= rounds) {
				round = 0;
				end = true;
			}
			return;
		}
	}

	void attacked(int hits, int stiffs) noexcept {
		hits = -hits;
		stiffs = stiffs;
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