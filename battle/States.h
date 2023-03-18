#pragma once
#pragma warning(disable: 26434 26440)

#include "globals.h"
#include "FSM.h"
#include "Context.h"
#include "Action.h"
#include "ActionManager.h"


// Status

struct Patrol : FSM::State {
	using FSM::State::react;

	void enter(Control& control) {
		// cout << "-> patrol" << endl;
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.succeed();
		}
	}

	void react(const AttackSignl& signl, FullControl& control) {
		control.changeTo<Attack>();
		control.context().attack(signl);
	}

	void react(const DefendSignl& signl, FullControl& control) {
		control.changeTo<Attacked>();
		control.context().attacked(signl);
	}
};

struct Stand : Patrol {

	Utility utility(const Control&) { return 0.05f; }

	void enter(Control& control) {
		control.context().patrolInit(ACTION::STAND);
		control.context().stand();
	}
};

struct Rest : Patrol {

	Utility utility(const Control&) { return 0.05f; }

	void enter(Control& control) {
		control.context().patrolInit(ACTION::REST);
		control.context().stand();
	}
};

struct Walk : Patrol {

	Utility utility(const Control&) { return 0.10f; }

	void enter(Control& control) {
		control.context().patrolInit(ACTION::WALK);
		control.context().slow();
	}
};

struct Advance : Patrol {

	Utility utility(const Control&) { return 0.10f; }

	void enter(Control& control) {
		control.context().patrolInit(ACTION::ADVANCE);
		control.context().slow();
	}
};

struct Run : Patrol {
	Utility utility(const Control&) { return 0.70f; }

	void enter(Control& control) {
		control.context().patrolInit(ACTION::RUN);
		control.context().fast();
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
		control.context().standbyInit();
	}

	void react(const AttackSignl& signl, FullControl& control) {
		control.changeTo<Attack>();
		control.context().attack(signl);
	}

	void react(const DefendSignl& signl, FullControl& control) {
		control.changeTo<Attacked>();
		control.context().attacked(signl);
	}

	void update(FullControl& control) {
		control.context().standbyStep();
	}
};

struct Attack : FSM::State {
	void enter(Control& control) {
		control.context().attackInit();
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.context().stand();
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
		control.context().defendInit(ACTION::INJURE, false);
	}

	void update(FullControl& control) {
		/*fmt::print("id: {} injure, hits: {}\n",
			control.context().actor_id, control.context().hits);*/
		control.context().step();

		if (control.context().hp <= 0) {
			control.changeTo<Fail>();
		}

		if (control.context().end) {
			control.changeTo<Stiff>();
		}
	}
};

struct Defend : FSM::State {
	Utility utility(const Control&) { return 0.15f; }

	void enter(Control& control) {
		control.context().defendInit(ACTION::DEFEND, true);
	}

	void update(FullControl& control) {
		/*fmt::print("id: {} defend, hits: {}\n",
			control.context().actor_id, control.context().hits);*/
		control.context().step();
		if (control.context().end) {
			control.changeTo<Standby>();
		}
	}
};

struct Jump : FSM::State {
	Utility utility(const Control&) { return 0.15f; }

	void enter(Control& control) {
		control.context().defendInit(ACTION::JUMP, true);
	}

	void update(FullControl& control) {
		/*fmt::print("id: {} jump, hits: {}\n",
			control.context().actor_id, control.context().hits);*/
		control.context().step();
		if (control.context().end) {
			control.changeTo<Standby>();
		}
	}
};

struct Stiff : FSM::State {

	using FSM::State::react;
	
	void enter(Control& control) {
		control.context().stiffInit();
	}

	void update(FullControl& control) {
		/*fmt::print("id: {} stiff, hits: {}, stiff: {}/{}",
			control.context().actor_id, control.context().hits,
			control.context().stiff, control.context().stiffs);*/
		control.context().stiffStep();
		if (control.context().end) {
			control.changeTo<Standby>();
		}
	}

	void react(const DefendSignl& signl, FullControl& control) {
		control.changeTo<Attacked>();
		control.context().attacked(signl);
	}
};

struct Fail : FSM::State {
	void enter(Control& control) {
		control.context().failInit();
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().stiffStep();
		if (control.context().end) {
			control.changeTo<Death>();
		}
	}
};

struct Death : FSM::State {
	void enter(Control& control) {
		/*fmt::print("id: {} death\n", control.context().actor_id);*/
		control.context().deathInit();
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().deathStep();
	}
};
