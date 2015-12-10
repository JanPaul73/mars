/*
 * Velocity6D.cpp
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#include "Velocity6D.h"

namespace mars {
namespace interaction {
namespace datatype {

Velocity6D::Velocity6D(std::string name) :
	BaseType(name),
	translational(name+"/translational"),
	rotational(name+"/rotational")
{
}

Velocity6D::~Velocity6D() {
}

void Velocity6D::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);
	translational.toDataPackage(pkg);
	rotational.toDataPackage(pkg);
}

void Velocity6D::fromDataPackage(const data_broker::DataPackage& pkg) {
	BaseType::fromDataPackage(pkg);
	translational.fromDataPackage(pkg);
	rotational.fromDataPackage(pkg);
}

void Velocity6D::setVelocity6D(const mars::utils::Vector &trans, const mars::utils::Quaternion& rot) {
	translational.setVector(trans);
	rotational.setQuaternion(rot);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
