#pragma once

#include "globals.h"
#include "Context.h"

using M = hfsm2::MachineT<hfsm2::Config::ContextT<Context>>;

using FSM = M::PeerRoot<
	struct Alive,
	M::Composite<struct Patrol,
	struct Stand,
	struct Sit,
	struct Walk,
	struct Run
	>,
	M::Composite<struct Battle,
	struct Advance,
	struct Attack,
	struct Hit,
	struct Defence,
	struct Jump,
	struct Rest,
	struct Fail
	>,
	struct Died
>;


