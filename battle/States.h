#pragma once

#include "globals.h"
#include "FSM.h"


struct Alive : FSM::State{
	using FSM::State::react;
};


struct Patrol : FSM::State {
	using FSM::State::react;
};

struct Stand : FSM::State {
	using FSM::State::react;
};

struct Sit : FSM::State {
	using FSM::State::react;
};

struct Walk : FSM::State {
	using FSM::State::react;
};

struct Run : FSM::State {
	using FSM::State::react;
};

struct Battle : FSM::State {
	using FSM::State::react;
};

struct Advance : FSM::State {
	using FSM::State::react;
};

struct Attack : FSM::State {
	using FSM::State::react;
};

struct Hit : FSM::State {
	using FSM::State::react;
};

struct Defence : FSM::State {
	using FSM::State::react;
};

struct Jump : FSM::State {
	using FSM::State::react;
};

struct Rest : FSM::State {
	using FSM::State::react;
};

struct Fail : FSM::State {
	using FSM::State::react;
};

struct Died : FSM::State {
	using FSM::State::react;
};
