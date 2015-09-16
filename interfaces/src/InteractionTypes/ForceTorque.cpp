/*
 * ForceTorque.cpp
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#include "ForceTorque.h"

namespace mars {
namespace interaction {
namespace datatype {

ForceTorque::ForceTorque(std::string name) :
	BaseType(name)
{
}

ForceTorque::~ForceTorque() {
}

void ForceTorque::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);

	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}

	pkg.add(prefix+"force/x", force.x());
	pkg.add(prefix+"force/y", force.y());
	pkg.add(prefix+"force/z", force.z());
	pkg.add(prefix+"torque/x", torque.x());
	pkg.add(prefix+"torque/y", torque.y());
	pkg.add(prefix+"torque/z", torque.z());
}

const base::Vector3d& ForceTorque::getForce() const {
	return force;
}

const base::Vector3d& ForceTorque::getTorque() const {
	return torque;
}

void ForceTorque::fromDataPackage(const data_broker::DataPackage& pkg) {
	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}

	BaseType::fromDataPackage(pkg);
	float x,y,z;
	pkg.get(prefix+"force/x", &x);
	pkg.get(prefix+"force/y", &y);
	pkg.get(prefix+"force/z", &z);
	force = base::Vector3d(x,y,z);
	pkg.get(prefix+"torque/x", &x);
	pkg.get(prefix+"torque/y", &y);
	pkg.get(prefix+"torque/z", &z);
	torque = base::Vector3d(x,y,z);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
