/*
 * BaseStateEventDispatcher.h
 *
 *  Created on: 23.02.2016
 *      Author: Jan Paul
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATEEVENTDISPATCHER_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATEEVENTDISPATCHER_H_

#include "BaseState.h"

#include <envire_core/events/GraphEventDispatcher.hpp>

namespace mars {
namespace interaction {
namespace state {

class BaseStateEventDispatcher: public envire::core::GraphEventDispatcher {
public:
	BaseStateEventDispatcher();
	virtual ~BaseStateEventDispatcher();
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATEEVENTDISPATCHER_H_ */
