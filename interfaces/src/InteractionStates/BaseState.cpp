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

BaseState::BaseState(const std::string& name) {
	name_ = name;
	frame_ = name;
}

BaseState::~BaseState() {
	// TODO Auto-generated destructor stub
}

//envire::core::TransformGraph temp; //Would be different for each instance!
//envire::core::TransformGraph BaseState::transformGraph=temp;
//envire::core::TransformGraph BaseState::transformGraph();
envire::core::TransformGraph BaseState::transformGraph;

void BaseState::updateTransformGraph() {
	TransformGraph transformGraph;
	vertex_descriptor desc = /*BaseState::*/transformGraph.vertex(frame_); //Cannot be done in constructor, because there the frame_=name value is not yet correctly set
	if (desc == transformGraph.null_vertex()) {
		transformGraph.addFrame(frame_);
		Item<BaseState*>::Ptr item(new Item<BaseState*>(this)); //Use the pointer instead, safer to be sure that no copy is created somewhere
//		Item<std::string>::Ptr item(new Item<std::string>("test")); //If this works, the add only the Datatype without the transformGraph (which is a cyclic assignment anyway); or only a pointer to this ("this" is a pointer anyway!)
		transformGraph.addItemToFrame(frame_, item);
	}
}

//see "test_transform_graph.cpp" for examples

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
