/*
 * BaseState.cpp
 *
 *  Created on: 27.11.2015
 *      Author: Jan Paul
 */

#include "BaseState.h"

namespace mars {
namespace interaction {
namespace state {

BaseState::BaseState(const std::string& name) :
		name_(name), frame_(name) {
}

BaseState::~BaseState() {
	// TODO Auto-generated destructor stub
}

void BaseState::updateTransformGraph() {
	vertex_descriptor desc = transformGraph.vertex(frame_); //Cannot be done in constructor, because there the frame_=name value is not yet correctly set
	if (desc == transformGraph.null_vertex()) {
		transformGraph.addFrame(frame_);
		Item<string>::Ptr item(new Item<BaseState>(this));
		transformGraph.addItemToFrame(frame_, item);
	}
}

//see "test_transform_graph.cpp" for examples

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
