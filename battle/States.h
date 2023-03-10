#pragma once
#pragma warning(disable: 26434 26440)

#include "globals.h"
#include "FSM.h"
#include "Context.h"
#include "Action.h"
#include "ActionManager.h"


// Events

struct Attacked {
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

	void react(const Attacked& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Beaten>();
	}
};

struct Rest : FSM::State {
	using FSM::State::react;

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

	void react(const Attacked& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Beaten>();
	}
};

struct Walk : FSM::State {
	using FSM::State::react;

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

	void react(const Attacked& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Beaten>();
	}
};

struct Advance : FSM::State {
	using FSM::State::react;

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

	void react(const Attacked& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Beaten>();
	}
};

struct Run : FSM::State {
	using FSM::State::react;

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

	void react(const Attacked& attack, FullControl& control) {
		control.context().attacked(attack.hits, attack.stiffs);
		control.changeTo<Beaten>();
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

struct Beaten : FSM::State {
	void enter(Control& control) {
		// cout << "-> battle" << endl;
	}
};

struct Hit : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::HIT, true, false);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step(false);
		if (control.context().end) {
			control.succeed();
		}
	}
};

struct Defence : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::DEFENCE, true, true);
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

struct Died : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::DIE);
		control.context().stand();
	}

	void update(FullControl& control) {
		
	}
};
