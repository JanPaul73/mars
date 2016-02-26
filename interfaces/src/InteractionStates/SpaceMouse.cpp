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
	std::cout << "Creating SpaceMouse.\n";
	std::cout << "Creating velocityStateItem_.\n";
	velocityStateItem_=new Item<Velocity6D>::Ptr(new Item<Velocity6D>(velocityState_));
	addItem(*velocityStateItem_);
}

SpaceMouse::~SpaceMouse() {
	std::cout << "Deleting SpaceMouse.\n";
	//removeItem(*velocityStateItem_); //TODO: JP: method not yet working like that
	std::cout << "Deleting velocityStateItem_.\n";
	delete(velocityStateItem_);
	std::cout << "Deleted velocityStateItem_.\n";
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
	updateItem(*velocityStateItem_);
	//transformGraph_.removeItemFromFrame(frame_, velocityStateItem_);
	//transformGraph_.addItemToFrame(frame_, velocityStateItem_); //Removed before just to trigger the add event, adding an "itemChanged" event to Envire2 would be nicer
}

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
