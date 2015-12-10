/*
 * Quaternion.cpp
 *
 *  Created on: 16.09.2015
 *      Author: Jan Paul
 */

#include "Quaternion.h"

namespace mars {
namespace interaction {
namespace datatype {

Quaternion::Quaternion(std::string name) :
	BaseType(name)
{
}

Quaternion::~Quaternion() {
}

void Quaternion::toDataPackage(data_broker::DataPackage& pkg) const {
	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}
	pkg.add(prefix+"w", quat.x());
	pkg.add(prefix+"x", quat.x());
	pkg.add(prefix+"y", quat.y());
	pkg.add(prefix+"z", quat.z());
}

const utils::Quaternion& Quaternion::getData() const {
	return getQuaternion();
}

void Quaternion::fromDataPackage(const data_broker::DataPackage& pkg) {
	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}
	float w,x,y,z;
	pkg.get(prefix+"w", &w);
	pkg.get(prefix+"x", &x);
	pkg.get(prefix+"y", &y);
	pkg.get(prefix+"z", &z);
	quat = utils::Quaternion(w,x,y,z);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

