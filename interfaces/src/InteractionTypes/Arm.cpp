/*
 * Arm.cpp
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#include "Arm.h"

namespace mars {
namespace interaction {
namespace datatype {

Arm::Arm(std::string name) :
	BaseType(name),
	hand(name+"/hand"),
	elbowPos(name+"/elbowPos"),
	shoulderPos(name+"/shoulderPos")
{
}

Arm::~Arm() {
}

const Vec3& Arm::getElbowPos() const {
	return elbowPos;
}

const Hand& Arm::getHand() const {
	return hand;
}

void Arm::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);
	hand.toDataPackage(pkg);
	elbowPos.toDataPackage(pkg);
	shoulderPos.toDataPackage(pkg);
}

void Arm::fromDataPackage(const data_broker::DataPackage& pkg) {
	BaseType::fromDataPackage(pkg);
	hand.fromDataPackage(pkg);
	elbowPos.fromDataPackage(pkg);
	shoulderPos.fromDataPackage(pkg);
}

const Vec3& Arm::getShoulderPos() const {
	return shoulderPos;
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
