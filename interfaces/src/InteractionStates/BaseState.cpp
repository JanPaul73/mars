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

	transformGraph_.addFrame(frame_);
	Item<BaseState*>::Ptr item(new Item<BaseState*>(this)); //Use the pointer instead of reference, safer to be sure that no content copy is created somewhere
	transformGraph_.addItemToFrame(frame_, item);

	if (transformGraph_.vertex(root_) == transformGraph_.null_vertex()) { //Has maybe already been done by other constructor call (transformGraph_ is static)
		transformGraph_.addFrame(root_);
	}
	//World transform:
	Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
	transformGraph_.addTransform(root_, frame_, tf);
}

BaseState::~BaseState() {
	transformGraph_.removeTransform(root_, frame_);
	transformGraph_.removeFrame(frame_);
}

//envire::core::TransformGraph BaseState::transformGraph_; //Necessary?
//std::string BaseState::root_="#root#"; //Necessary?

void BaseState::makeSureTransformFromExists(FrameId& other) {
	try {
		transformGraph_.getTransform(other, frame_);
	} catch (UnknownTransformException &e) {
		Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
		transformGraph_.addTransform(other, frame_, tf);
	}
}

void BaseState::makeSureTransformToExists(FrameId& other) {
	try {
		transformGraph_.getTransform(frame_, other);
	} catch (UnknownTransformException &e) {
		Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
		transformGraph_.addTransform(frame_, other, tf);
	}
}

void BaseState::updateWorldTransform(Transform& tf) {
	transformGraph_.updateTransform(root_, frame_, tf);
}

void BaseState::updateTransformTo(Transform& tf, FrameId& other) {
	makeSureTransformToExists(other);
	transformGraph_.updateTransform(frame_, other, tf);
}

void BaseState::updateTransformFrom(Transform& tf, FrameId& other) {
	makeSureTransformFromExists(other);
	transformGraph_.updateTransform(other, frame_, tf);
}

//see "test_transform_graph.cpp" for examples

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
