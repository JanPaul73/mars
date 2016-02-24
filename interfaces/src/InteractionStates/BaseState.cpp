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

	std::cout << "Adding Frame: " << frame_ << "\n";

	envireGraph_.addFrame(frame_);
	Item<BaseState*>::Ptr item(new Item<BaseState*>(this)); //Use the pointer instead of reference, safer to be sure that no content copy is created somewhere
	envireGraph_.addItemToFrame(frame_, item);

	if (envireGraph_.vertex(root_) == envireGraph_.null_vertex()) { //Has maybe already been done by other constructor call (transformGraph_ is static)
		envireGraph_.addFrame(root_);
	}
	//World transform:
	Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
	envireGraph_.addTransform(root_, frame_, tf);
}

BaseState::~BaseState() {
	envireGraph_.removeTransform(root_, frame_);
	//envireGraph_.removeTransform(frame_, root_);//JP: The above command does that already implicitly
	envireGraph_.removeFrame(frame_);
}

envire::core::EnvireGraph BaseState::envireGraph_; //Necessary?
const std::string BaseState::root_="#root#"; //Necessary?

void BaseState::makeSureTransformFromExists(FrameId& other) {
	try {
		envireGraph_.getTransform(other, frame_);
	} catch (UnknownTransformException &e) {
		Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
		envireGraph_.addTransform(other, frame_, tf);
	}
}

void BaseState::makeSureTransformToExists(FrameId& other) {
	try {
		envireGraph_.getTransform(frame_, other);
	} catch (UnknownTransformException &e) {
		Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
		envireGraph_.addTransform(frame_, other, tf);
	}
}

void BaseState::updateWorldTransform(Transform& tf) {
	envireGraph_.updateTransform(root_, frame_, tf);
}

void BaseState::updateTransformTo(Transform& tf, FrameId& other) {
	makeSureTransformToExists(other);
	envireGraph_.updateTransform(frame_, other, tf);
}

void BaseState::updateTransformFrom(Transform& tf, FrameId& other) {
	makeSureTransformFromExists(other);
	envireGraph_.updateTransform(other, frame_, tf);
}


//see "test_transform_graph.cpp" for examples

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
