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

SpaceMouse::SpaceMouse(const std::string& name) {
	name_ = name;
	frame_ = name;
}

SpaceMouse::~SpaceMouse() {
	// TODO Auto-generated destructor stub
}

void SpaceMouse::setPose(mars::utils::Vector trans,
		mars::utils::Quaternion rot) {
	poseState_.setPose(trans, rot);
	updateTransformGraph();
}

void SpaceMouse::setVelocity(mars::utils::Vector trans,
		mars::utils::Quaternion rot) {
	velocityState_.setVelocity6D(trans, rot);
	updateTransformGraph();
}

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
