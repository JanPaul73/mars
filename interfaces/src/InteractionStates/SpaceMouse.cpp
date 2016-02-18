/*
 * SpaceMouse.cpp
 *
 *  Created on: 27.11.2015
 *      Author: Jan Paul
 */

#include "SpaceMouse.h"

namespace mars {
namespace interaction {
namespace state {

SpaceMouse::SpaceMouse(const std::string& name) :
		BaseState(name) {
	velocityStateItem_=new Item<Velocity6D>::Ptr(new Item<Velocity6D>(velocityState_));
	addItem(*velocityStateItem_);
}

SpaceMouse::~SpaceMouse() {
	removeItem(*velocityStateItem_);
	delete(velocityStateItem_);
}

void SpaceMouse::setPoseState(const Pose& poseState) {
	poseState_ = poseState;
	updateWorldTransform();
}

void SpaceMouse::setPoseState(const mars::utils::Vector& trans,
		const mars::utils::Quaternion& rot) {
	poseState_.setPose(trans, rot);
	updateWorldTransform();
}

void SpaceMouse::updateWorldTransform() {
	Transform tf = Transform(poseState_.getPosition(),
			poseState_.getOrientation()); //Keeping tf on stack seems to be OK, as deep down in the end, "updateWorldTransform(tf);" copies the value of tf somewhere else. Otherwise the danger would be that tf is deleted from the stack when leaving this scope, although a reference to it is still stored somewhere?
	BaseState::updateWorldTransform(tf);
}

void SpaceMouse::setVelocityState(const Velocity6D& velocityState) {
	velocityState_ = velocityState;
	updateVelocityState();
}

void SpaceMouse::setVelocityState(const mars::utils::Vector& trans,
		const mars::utils::Quaternion& rot) {
	velocityState_.setVelocity6D(trans, rot);
	updateVelocityState();
}

void SpaceMouse::updateVelocityState() {
	velocityStateItem_->get()->setTime(base::Time::now());
	updateItem(velocityStateItem_);
	//transformGraph_.removeItemFromFrame(frame_, velocityStateItem_);
	//transformGraph_.addItemToFrame(frame_, velocityStateItem_); //Removed before just to trigger the add event, adding an "itemChanged" event to Envire2 would be nicer
}

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
