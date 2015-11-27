/*
 * BaseState.h
 *
 *  Created on: 27.11.2015
 *      Author: jan
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_

#include <envire_core/graph/TransformGraph.hpp>

namespace mars {
namespace interaction {
namespace state {

class BaseState {
public:
	BaseState();
	virtual ~BaseState();

	const envire::core::TransformGraph& getTransformGraph() const {
		return transformGraph;
	}

	static envire::core::TransformGraph transformGraph;
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_ */
