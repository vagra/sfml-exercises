#pragma once
#pragma warning(disable: 26434 26440)

#include "globals.h"
#include "FSM.h"
#include "Context.h"
#include "Action.h"
#include "ActionManager.h"


////////////////////////////////////////
// Status
////////////////////////////////////////

struct Turn : FSM::State {

	void enter(Control& control) {
		// cout << "-> turn" << endl;
		control.context().freeTurn();
	}

	void update(FullControl& control) {
		control.changeTo<Patrol>();
	}

};

struct Patrol : FSM::State {
	using FSM::State::react;

	void enter(Control& control) {
		// cout << "-> patrol" << endl;
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.changeTo<Turn>();
		}
	}

	void react(const AttackSignl& signl, FullControl& control) {
		control.changeTo<Attack>();
		control.context().reactAttack(signl);
	}

	void react(const DefendSignl& signl, FullControl& control) {
		control.changeTo<Attacked>();
		control.context().reactAttacked(signl);
	}

	void react(const BackTurnSignl& signl, FullControl& control) {
		control.context().reactBackTurn(signl);
	}
};

struct Stand : Patrol {

	Utility utility(const Control&) { return 0.05f; }

	void enter(Control& control) {
		control.context().initPatrol(ACTION::STAND);
		control.context().speedZero();
	}
};

struct Rest : Patrol {

	Utility utility(const Control&) { return 0.05f; }

	void enter(Control& control) {
		control.context().initPatrol(ACTION::REST);
		control.context().speedZero();
	}
};

struct Walk : Patrol {

	Utility utility(const Control&) { return 0.10f; }

	void enter(Control& control) {
		control.context().initPatrol(ACTION::WALK);
		control.context().speedSlow();
	}
};

struct Advance : Patrol {

	Utility utility(const Control&) { return 0.10f; }

	void enter(Control& control) {
		control.context().initPatrol(ACTION::ADVANCE);
		control.context().speedSlow();
	}
};

struct Run : Patrol {
	Utility utility(const Control&) { return 0.70f; }

	void enter(Control& control) {
		control.context().initPatrol(ACTION::RUN);
		control.context().speedFast();
	}
};

struct Battle : FSM::State {
	void enter(Control& control) {
		// cout << "-> battle" << endl;
	}
};

struct Standby : FSM::State {
	using FSM::State::react;

	void enter(Control& control) {
		control.context().initStandby();
	}

	void react(const AttackSignl& signl, FullControl& control) {
		control.changeTo<Attack>();
		control.context().reactAttack(signl);
	}

	void react(const DefendSignl& signl, FullControl& control) {
		control.changeTo<Attacked>();
		control.context().reactAttacked(signl);
	}

	void update(FullControl& control) {
		control.context().stepStandby();
	}
};

struct Attack : FSM::State {
	void enter(Control& control) {
		control.context().initAttack();
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.context().speedZero();
			control.changeTo<Stiff>();
		}
	}
};

struct Attacked : FSM::State {
	void enter(Control& control) {
		// cout << "-> battle" << endl;
	}
};

struct Injure : FSM::State {
	Utility utility(const Control&) { return 0.70f; }

	void enter(Control& control) {
		control.context().initDefend(ACTION::INJURE, false);
	}

	void update(FullControl& control) {
		control.context().step();

		if (control.context().end) {
			control.changeTo<Stiff>();
		}
	}
};

struct Defend : FSM::State {
	Utility utility(const Control&) { return 0.15f; }

	void enter(Control& control) {
		control.context().initDefend(ACTION::DEFEND, true);
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.changeTo<Standby>();
		}
	}
};

struct Jump : FSM::State {
	Utility utility(const Control&) { return 0.15f; }

	void enter(Control& control) {
		control.context().initDefend(ACTION::JUMP, true);
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.changeTo<Standby>();
		}
	}
};

struct Stiff : FSM::State {

	using FSM::State::react;
	
	void enter(Control& control) {
		control.context().initStiff();
	}

	void update(FullControl& control) {

		control.context().stepStiff();

		if (control.context().hp <= 0) {
			control.changeTo<Fail>();
		}

		if (control.context().end) {
			control.changeTo<Standby>();
		}
	}

	void react(const DefendSignl& signl, FullControl& control) {
		control.changeTo<Attacked>();
		control.context().reactAttacked(signl);
	}
};

struct Fail : FSM::State {
	void enter(Control& control) {
		control.context().initFail();
		control.context().speedZero();
	}

	void update(FullControl& control) {
		control.context().stepStiff();
		if (control.context().end) {
			control.changeTo<Death>();
		}
	}
};

struct Death : FSM::State {
	void enter(Control& control) {
		control.context().initDeath();
		control.context().speedZero();
	}

	void update(FullControl& control) {
		control.context().stepDeath();
	}
};
