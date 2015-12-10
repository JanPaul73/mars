/*
 * Leg.cpp
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#include "Leg.h"

namespace mars {
namespace interaction {
namespace datatype {

Leg::Leg(std::string name) :
	BaseType(name),
	hipPos(name+"/hipPos"),
	kneePos(name+"/kneePos"),
	anklePos(name+"/anklePos"),
	footPos(name+"/footPos")
{
}

Leg::~Leg() {
}

const Vec3& Leg::getAnklePos() const {
	return anklePos;
}

const Vec3& Leg::getFootPos() const {
	return footPos;
}

const Vec3& Leg::getHipPos() const {
	return hipPos;
}

void Leg::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);
	hipPos.toDataPackage(pkg);
	kneePos.toDataPackage(pkg);
	anklePos.toDataPackage(pkg);
	footPos.toDataPackage(pkg);
}

void Leg::fromDataPackage(const data_broker::DataPackage& pkg) {
	BaseType::fromDataPackage(pkg);
	hipPos.fromDataPackage(pkg);
	kneePos.fromDataPackage(pkg);
	anklePos.fromDataPackage(pkg);
	footPos.fromDataPackage(pkg);
}

const Vec3& Leg::getKneePos() const {
	return kneePos;
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
