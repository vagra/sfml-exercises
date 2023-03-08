#pragma once
#pragma warning(disable: 26434)

#include "globals.h"
#include "FSM.h"
#include "Context.h"
#include "Action.h"
#include "ActionManager.h"


struct Alive : FSM::State{
	void enter(Control& control) {
		cout << "-> alive" << endl;
	}
};

struct Patrol : FSM::State {
	void enter(Control& control) {
		cout << "-> patrol" << endl;
	}
};

struct Stand : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::STAND;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::STAND
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> stand" << endl;
	}

	void update(FullControl& control) noexcept {
		control.context().step += 1;
		if (control.context().step >= control.context().frames) {
			control.changeTo<Walk>();
		}
	}
};

struct Sit : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::SIT;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::SIT
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> sit" << endl;
	}
};

struct Walk : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::WALK;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::WALK
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> walk" << endl;
	}

	void update(FullControl& control) noexcept {
		control.context().step += 1;
		if (control.context().step >= control.context().frames) {
			control.changeTo<Run>();
		}
	}
};

struct Run : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::RUN;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::RUN
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> run" << endl;
	}

	void update(FullControl& control) noexcept {
		control.context().step += 1;
		if (control.context().step >= control.context().frames) {
			control.changeTo<Stand>();
		}
	}
};

struct Battle : FSM::State {
	void enter(Control& control) {
		cout << "-> battle" << endl;
	}
};

struct Advance : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::ADVANCE;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::ADVANCE
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> advance" << endl;
	}
};

struct Attack : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::ATTACK;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::ATTACK
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> attack" << endl;
	}
};

struct Hit : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::HIT;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::HIT
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> hit" << endl;
	}
};

struct Defence : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::DEFENCE;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::DEFENCE
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> defence" << endl;
	}
};

struct Jump : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::JUMP;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::JUMP
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> jump" << endl;
	}
};

struct Rest : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::REST;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::REST
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> rest" << endl;
	}
};

struct Fail : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::FAIL;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::FAIL
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> fail" << endl;
	}
};

struct Died : FSM::State {
	void enter(Control& control) {
		control.context().action = ACTION::DIE;
		control.context().frames = ActionManager::getAction(
			control.context().actor_type,
			ACTION::DIE
		)->frames;
		control.context().step = 0;
		control.context().timer = 0;
		cout << "-> died" << endl;
	}
};
