#pragma once

#include "globals.h"
#include "Context.h"

using Config = hfsm2::Config::ContextT<Context>;

using M = hfsm2::MachineT<Config>;

#define S(s) struct s

using FSM = M::PeerRoot<
				M::Composite<S(Patrol),
					S(Stand),
					S(Rest),
					S(Walk),
					S(Advance),
					S(Run)
				>,
				S(Attack),
				M::Composite<S(Beaten),
					S(Hit),
					S(Defence),
					S(Jump)
				>,
				S(Died)
			>;

#undef S
