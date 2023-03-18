#pragma once

#include "globals.h"
#include "Context.h"

using Config = hfsm2::Config::ContextT<Context>;

using M = hfsm2::MachineT<Config>;

#define S(s) struct s

using FSM = M::PeerRoot<
				S(Turn),
				M::Random<S(Patrol),
					S(Stand),
					S(Rest),
					S(Walk),
					S(Advance),
					S(Run)
				>,
				M::Composite<S(Battle),
					S(Standby),
					S(Attack),
					M::Random<S(Attacked),
						S(Injure),
						S(Defend),
						S(Jump)
					>,
					S(Stiff)
				>,
				S(Fail),
				S(Death)
			>;

#undef S
