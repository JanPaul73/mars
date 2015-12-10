/*
 * Vec3.cpp
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#include "Vec3.h"

namespace mars {
namespace interaction {
namespace datatype {

Vec3::Vec3(std::string name) :
	BaseType(name)
{
}

Vec3::~Vec3() {
}

void Vec3::toDataPackage(data_broker::DataPackage& pkg) const {
	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}
	pkg.add(prefix+"x", vector.x());
	pkg.add(prefix+"y", vector.y());
	pkg.add(prefix+"z", vector.z());
}

void Vec3::fromDataPackage(const data_broker::DataPackage& pkg) {
	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}
	float x,y,z;
	pkg.get(prefix+"x", &x);
	pkg.get(prefix+"y", &y);
	pkg.get(prefix+"z", &z);
	vector = utils::Vector(x,y,z);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

