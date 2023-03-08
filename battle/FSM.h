#pragma once

#include "globals.h"
#include "Context.h"

using Config = hfsm2::Config::ContextT<Context>;

using M = hfsm2::MachineT<Config>;

#define S(s) struct s

using FSM = M::PeerRoot<
	M::Composite<S(Alive),
		M::Composite<S(Patrol),
			S(Stand),
			S(Walk),
			S(Run),
			S(Sit)
		>,
		M::Composite<S(Battle),
			S(Rest),
			S(Advance),
			S(Attack),
			S(Hit),
			S(Defence),
			S(Jump),
			S(Fail)
		>
	>,
	S(Died)
>;

#undef S
