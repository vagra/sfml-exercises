#pragma once
#pragma warning(disable: 26434 26440)

#include "globals.h"
#include "FSM.h"
#include "Context.h"
#include "Action.h"
#include "ActionManager.h"


// Events

struct Combat {
	int hits{};
	int stiffs{};
};


// Status

struct Patrol : FSM::State {
	void enter(Control& control) {
		// cout << "-> patrol" << endl;
	}
};

struct Stand : FSM::State {
	using FSM::State::react;

	Utility utility(const Control&) { return 0.05f; }

	void enter(Control& control) {
		control.context().init(ACTION::STAND);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.succeed();
		}
	}

	void react(const Combat& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Attacked>();
	}
};

struct Rest : FSM::State {
	using FSM::State::react;

	Utility utility(const Control&) { return 0.05f; }

	void enter(Control& control) {
		control.context().init(ACTION::REST);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.succeed();
		}
	}

	void react(const Combat& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Attacked>();
	}
};

struct Walk : FSM::State {
	using FSM::State::react;

	Utility utility(const Control&) { return 0.10f; }

	void enter(Control& control) {
		control.context().init(ACTION::WALK);
		control.context().slow();
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.succeed();
		}
	}

	void react(const Combat& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Attacked>();
	}
};

struct Advance : FSM::State {
	using FSM::State::react;

	Utility utility(const Control&) { return 0.10f; }

	void enter(Control& control) {
		control.context().init(ACTION::ADVANCE);
		control.context().slow();
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.succeed();
		}
	}

	void react(const Combat& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Attacked>();
	}
};

struct Run : FSM::State {
	using FSM::State::react;

	Utility utility(const Control&) { return 0.70f; }

	void enter(Control& control) {
		control.context().init(ACTION::RUN);
		control.context().fast();
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.succeed();
		}
	}

	void react(const Combat& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Attacked>();
	}
};


struct Attack : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::ATTACK, true);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
		if (control.context().end) {
			control.succeed();
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
		control.context().init(ACTION::INJURE, true, false);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step(false);
		if (control.context().end) {
			control.succeed();
		}
	}
};

struct Defend : FSM::State {
	Utility utility(const Control&) { return 0.15f; }

	void enter(Control& control) {
		control.context().init(ACTION::DEFEND, true, true);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step(true);
		if (control.context().end) {
			control.succeed();
		}
	}
};

struct Jump : FSM::State {
	Utility utility(const Control&) { return 0.15f; }

	void enter(Control& control) {
		control.context().init(ACTION::JUMP, true, true);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step(true);
		if (control.context().end) {
			control.succeed();
		}
	}
};

struct Death : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::DEATH);
		control.context().stand();
	}

	void update(FullControl& control) {
		
	}
};
