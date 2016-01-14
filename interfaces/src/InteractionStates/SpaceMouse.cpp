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
	transformGraph_.addItemToFrame(frame_, velocityStateItem_);
}

SpaceMouse::~SpaceMouse() {
	// TODO Auto-generated destructor stub
	transformGraph_.removeItemFromFrame(frame_, velocityStateItem_);
}

Pose SpaceMouse::poseState_; //Necessary?
Velocity6D SpaceMouse::velocityState_; //Necessary?
Item<Velocity6D *>::Ptr SpaceMouse::velocityStateItem_(
		new Item<Transform *>(&velocityState_));

void SpaceMouse::setPoseState(const mars::utils::Vector& trans,
		const mars::utils::Quaternion& rot) {
	poseState_.setPose(trans, rot);
	Transform tf = Transform(poseState_.getPosition(),
			poseState_.getOrientation()); //Keeping tf on stack seems to be OK, as deep down in the end, "updateWorldTransform(tf);" copies the value of tf somewhere else. Otherwise the danger would be that tf is deleted from the stack when leaving this scope, although a reference to it is still stored somewhere?
	updateWorldTransform(tf);
}

void SpaceMouse::setVelocityState(const mars::utils::Vector& trans,
		const mars::utils::Quaternion& rot) {
	velocityState_.setVelocity6D(trans, rot);
	velocityStateItem_.get()->setTime(base::Time::now());
	transformGraph_.removeItemFromFrame(frame_, velocityStateItem_);
	transformGraph_.addItemToFrame(frame_, velocityStateItem_); //Removed before just to trigger the add event, adding an "itemChanged" event to Envire2 would be nicer
}

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
