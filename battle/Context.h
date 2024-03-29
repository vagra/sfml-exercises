#pragma once

#include "globals.h"
#include "../common/ActionManager.h"

constexpr int MIN_ROUNDS = 1;
constexpr int MAX_ROUNDS = 5;

constexpr int MIN_RUN_SPEED = 10;
constexpr int MAX_RUN_SPEED = 20;
constexpr int MIN_WALK_SPEED = 10;
constexpr int MAX_WALK_SPEED = 5;

constexpr int ATTACT_STIFFS = 3;
constexpr int FAIL_STIFFS = 100;
constexpr int DEATH_STIFFS = INT32_MAX;

////////////////////////////////////////
// Events
////////////////////////////////////////

struct AttackSignl {
	int knockback{};
	int direction{};
};

struct DefendSignl {
	int hits{};
	int stiffs{};
	int knockback{};
	int direction{};
};

struct FreeTurnSignl {};
struct BumpTurnSignl {};
struct BackTurnSignl {
	int direction{};
};

////////////////////////////////////////
// Context
////////////////////////////////////////

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
	int direction{};
	bool end{};
	bool standby{};

	// ------------------------------------
	// inits

	void initAttack() {
		action = ACTION::ATTACK;
		action_name = ActionManager::instance().getActionName(action);

		frames = ActionManager::instance().getAction(actor_type, action)->frames;
		frame = 0;

		rounds = 1;
		round = 0;

		stiffs = ATTACT_STIFFS;
		stiff = 0;

		speed = 0;

		end = false;
		standby = false;
	}

	void initDefend(ACTION action_id, bool dodge = true) {
		action = action_id;
		action_name = ActionManager::instance().getActionName(action_id);

		frames = ActionManager::instance().getAction(actor_type, action_id)->frames;
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

	void initStiff() noexcept {
		rounds = 1;
		round = 0;

		stiff = 0;

		knockback = 0;

		end = false;
		standby = false;
	}

	void initStandby() {
		action = ACTION::REST;
		action_name = ActionManager::instance().getActionName(action);

		frames = ActionManager::instance().getAction(actor_type, action)->frames;
		frame = 0;

		speed = 0;

		knockback = 0;

		end = true;
		standby = true;
	}

	void initPatrol(ACTION action_id) {
		action = action_id;
		action_name = ActionManager::instance().getActionName(action);

		frames = ActionManager::instance().getAction(actor_type, action)->frames;
		frame = 0;

		rounds = rand() % (MAX_ROUNDS + 1 - MIN_ROUNDS) + MIN_ROUNDS;
		round = 0;

		knockback = 0;

		end = false;
		standby = false;
	}

	void initFail() {
		action = ACTION::FAIL;
		action_name = ActionManager::instance().getActionName(action);

		frames = ActionManager::instance().getAction(actor_type, action)->frames;
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

	void initDeath() {
		action = ACTION::DEATH;
		action_name = ActionManager::instance().getActionName(action);

		frames = ActionManager::instance().getAction(actor_type, action)->frames;
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

	// ------------------------------------
	// steps

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

	void stepStiff() noexcept {
		stiff++;

		if (stiff >= stiffs) {
			end = true;
			return;
		}
	}

	void stepStandby() noexcept {
		frame++;

		if (frame >= frames) {
			frame = 0;
		}
	}

	void stepDeath() noexcept {
		stiff++;

		if (stiff >= stiffs) {
			stiff = 0;
			return;
		}
	}

	// ------------------------------------
	// combat reacts

	void reactAttack(const AttackSignl& signl) noexcept {
		knockback = signl.knockback;
		direction = signl.direction;
	}

	void reactAttacked(const DefendSignl& signl) noexcept {
		hits = signl.hits;
		stiffs = signl.stiffs;
		knockback = signl.knockback;
		direction = signl.direction;
	}

	void reactBumpTurn(const BumpTurnSignl& signl) noexcept {
		const int range = rand() % (DIRECTIONS - 3) + 2;
		direction = (direction + range) % DIRECTIONS;
	}

	void reactBackTurn(const BackTurnSignl& signl) noexcept {
		const int range = rand() % (DIRECTIONS - 5) + 7;
		direction = (signl.direction + range) % DIRECTIONS;
	}

	// ------------------------------------
	// speeds

	void speedSlow() noexcept {
		speed = rand() % (MAX_WALK_SPEED - MIN_WALK_SPEED) + MIN_WALK_SPEED;
	}

	void speedFast() noexcept {
		speed = rand() % (MAX_RUN_SPEED - MIN_RUN_SPEED) + MIN_RUN_SPEED;
	}

	void speedZero() noexcept {
		speed = 0;
	}

	// ------------------------------------
	// direction

	void freeTurn() noexcept {
		direction = rand() % DIRECTIONS;
	}

	
};