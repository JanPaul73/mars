/*
 * Head.cpp
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#include "Head.h"

namespace mars {
namespace interaction {
namespace datatype {

Head::Head(std::string name) :
	BaseType(name),
	pose(name+"/pose")
{
}

Head::~Head() {
}

const Pose& Head::getPose() const {
	return pose;
}

void Head::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);
	pose.toDataPackage(pkg);
}

void Head::fromDataPackage(const data_broker::DataPackage& pkg) {
	BaseType::fromDataPackage(pkg);
	pose.fromDataPackage(pkg);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
