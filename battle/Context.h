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

constexpr int ATTACT_STIFFS = 3;
constexpr int FAIL_STIFFS = 100;
constexpr int DEATH_STIFFS = INT32_MAX;

// Events

struct AttackSignl {
	int knockback{};
};

struct DefendSignl {
	int hits{};
	int stiffs{};
	int knockback{};
};

// Context

struct Context {
	int actor_id{};
	int actor_type{};
	int hp{};
	ACTION action{};
	string action_name{};
	int rounds{};
	int round{};
	int frames{};
	int frame{};
	int stiffs{};
	int stiff{};
	int hits{};
	int speed{};
	int knockback{};
	bool end{};
	bool standby{};

	void attackInit() {
		action = ACTION::ATTACK;
		action_name = ActionManager::getActionName(action);

		frames = ActionManager::getAction(actor_type, action)->frames;
		frame = 0;

		rounds = 1;
		round = 0;

		stiffs = ATTACT_STIFFS;
		stiff = 0;

		speed = 0;

		end = false;
		standby = false;
	}

	void defendInit(ACTION action_id, bool dodge = true) {
		action = action_id;
		action_name = ActionManager::getActionName(action_id);

		frames = ActionManager::getAction(actor_type, action_id)->frames;
		frame = 0;

		rounds = 1;
		round = 0;

		if (dodge) {
			hits = 0;
			stiffs = 0;
		}
		else {
			hp = max(0, hp - hits);
			hits = 0;
		}
		stiff = 0;

		speed = 0;

		end = false;
		standby = false;
	}

	void stiffInit() noexcept {
		rounds = 1;
		round = 0;

		stiff = 0;

		knockback = 0;

		end = false;
		standby = false;
	}

	void standbyInit() {
		action = ACTION::REST;
		action_name = ActionManager::getActionName(action);

		frames = ActionManager::getAction(actor_type, action)->frames;
		frame = 0;

		speed = 0;

		knockback = 0;

		end = true;
		standby = true;
	}

	void patrolInit(ACTION action_id) {
		action = action_id;
		action_name = ActionManager::getActionName(action);

		frames = ActionManager::getAction(actor_type, action)->frames;
		frame = 0;

		rounds = rand() % (MAX_ROUNDS + 1 - MIN_ROUNDS) + MIN_ROUNDS;
		round = 0;

		knockback = 0;

		end = false;
		standby = false;
	}

	void failInit() {
		action = ACTION::FAIL;
		action_name = ActionManager::getActionName(action);

		frames = ActionManager::getAction(actor_type, action)->frames;
		frame = 0;

		rounds = 1;
		round = 0;

		stiffs = FAIL_STIFFS;
		stiff = 0;

		speed = 0;

		knockback = 0;

		end = false;
		standby = false;
	}

	void deathInit() {
		action = ACTION::DEATH;
		action_name = ActionManager::getActionName(action);

		frames = ActionManager::getAction(actor_type, action)->frames;
		frame = 0;

		rounds = 1;
		round = 0;

		stiffs = DEATH_STIFFS;
		stiff = 0;

		speed = 0;

		knockback = 0;

		end = false;
		standby = false;
	}

	void step() noexcept {
		frame++;

		if (frame >= frames) {
			round++;
			if (round >= rounds) {
				end = true;
				return;
			}
			frame = 0;
		}
	}

	void stiffStep() noexcept {
		stiff++;

		if (stiff >= stiffs) {
			end = true;
			return;
		}
	}

	void standbyStep() noexcept {
		frame++;

		if (frame >= frames) {
			frame = 0;
		}
	}

	void deathStep() noexcept {
		stiff++;

		if (stiff >= stiffs) {
			stiff = 0;
			return;
		}
	}

	void attack(AttackSignl signl) noexcept {
		knockback = signl.knockback;
	}

	void attacked(DefendSignl signl) noexcept {
		hits = signl.hits;
		stiffs = signl.stiffs;
		knockback = signl.knockback;
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