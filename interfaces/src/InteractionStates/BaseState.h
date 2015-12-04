/*
 * BaseState.h
 *
 *  Created on: 27.11.2015
 *      Author: Jan Paul
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_

#include <envire_core/all>

namespace mars {
namespace interaction {
namespace state {
using namespace envire::core;
using namespace std;

class BaseState {
public:
	BaseState(const std::string& name="BaseState");
	virtual ~BaseState();

	TransformGraph& getTransformGraph() const {
		return transformGraph;
	}

	void updateTransformGraph();
private:
	static envire::core::TransformGraph transformGraph;
	FrameId frame_;
	std::string name_;
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_ */
