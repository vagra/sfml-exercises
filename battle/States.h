#pragma once
#pragma warning(disable: 26434 26440)

#include "globals.h"
#include "FSM.h"
#include "Context.h"
#include "Action.h"
#include "ActionManager.h"


struct Alive : FSM::State{
	void enter(Control& control) {
		// cout << "-> alive" << endl;
	}
};

struct Patrol : FSM::State {
	void enter(Control& control) {
		// cout << "-> patrol" << endl;
	}
};

struct Stand : FSM::State {
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
};

struct Sit : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::SIT);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();

	}
};

struct Walk : FSM::State {
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
};

struct Run : FSM::State {
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
};

struct Battle : FSM::State {
	void enter(Control& control) {
		// cout << "-> battle" << endl;
	}
};

struct Advance : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::ADVANCE);
		control.context().slow();
	}

	void update(FullControl& control) {
		control.context().step();
	}
};

struct Attack : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::ATTACK);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
	}
};

struct Hit : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::HIT);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
	}
};

struct Defence : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::DEFENCE);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
	}
};

struct Jump : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::JUMP);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
	}
};

struct Rest : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::REST);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
	}
};

struct Fail : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::FAIL);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
	}
};

struct Died : FSM::State {
	void enter(Control& control) {
		control.context().init(ACTION::DIE);
		control.context().stand();
	}

	void update(FullControl& control) {
		control.context().step();
	}
};
