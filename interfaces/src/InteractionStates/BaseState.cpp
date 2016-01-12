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

void BaseState::makeSureTransformGraphExists() {
	TransformGraph transformGraph;
	vertex_descriptor desc = /*BaseState::*/transformGraph.vertex(frame_); //Cannot be done in constructor, because there the frame_=name value is not yet correctly set
	if (desc == transformGraph.null_vertex()) {
		transformGraph.addFrame(frame_);
		Item<BaseState*>::Ptr item(new Item<BaseState*>(this)); //Use the pointer instead, safer to be sure that no copy is created somewhere
//		Item<std::string>::Ptr item(new Item<std::string>("test")); //If this works, then add only the Datatype without the transformGraph (which is a cyclic assignment anyway); or only a pointer to this ("this" is a pointer anyway!)
		transformGraph.addItemToFrame(frame_, item);

		if (transformGraph.vertex(root_) == transformGraph.null_vertex()) {
			transformGraph.addFrame(frame_);
		}
		Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
		transformGraph.addTransform(root_, frame_, tf);
	}
}

void BaseState::makeSureTransformFromExists(FrameId& other) {
	try {
		transformGraph.getTransform(other, frame_);
	} catch (UnknownTransformException &e) {
		Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
		transformGraph.addTransform(other, frame_, tf);
	}
}

void BaseState::makeSureTransformToExists(FrameId& other) {
	try {
		transformGraph.getTransform(frame_, other);
	} catch (UnknownTransformException &e) {
		Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
		transformGraph.addTransform(frame_, other, tf);
	}
}

void BaseState::makeSureWorldTransformExists() {
	try {
		transformGraph.getTransform(root_, frame_);
	} catch (UnknownTransformException &e) {
		Transform tf; //Null transformation for now, should be OK to keep it on stack, as transformGraph.addTransform copies it into a struct
		transformGraph.addTransform(root_, frame_, tf);
	}
}

void BaseState::updateWorldTransform(Transform& tf) {
	makeSureTransformGraphExists();
	makeSureWorldTransformExists();
	transformGraph.updateTransform(root_, frame_, worldTF);
}

void BaseState::updateTransformTo(Transform& tf, FrameId& other) {
	makeSureTransformGraphExists();
	makeSureTransformToExists(other);
	transformGraph.updateTransform(frame_, other, tf);
}

void BaseState::updateTransformFrom(Transform& tf, FrameId& other) {
	makeSureTransformGraphExists();
	makeSureTransformFromExists(other);
	transformGraph.updateTransform(other, frame_, tf);
}

//see "test_transform_graph.cpp" for examples

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
