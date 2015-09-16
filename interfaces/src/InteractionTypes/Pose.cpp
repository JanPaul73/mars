/*
 * Pose.cpp
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#include "Pose.h"

namespace mars {
namespace interaction {
namespace datatype {

Pose::Pose(std::string name) :
	BaseType(name)
{
}

Pose::~Pose() {
}

void Pose::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);

	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}
	pkg.add(prefix+"position/x", position.x());
	pkg.add(prefix+"position/y", position.y());
	pkg.add(prefix+"position/z", position.z());
	pkg.add(prefix+"orientation/x", orientation.x());
	pkg.add(prefix+"orientation/y", orientation.y());
	pkg.add(prefix+"orientation/z", orientation.z());
	pkg.add(prefix+"orientation/w", orientation.w());
}

void Pose::fromDataPackage(const data_broker::DataPackage& pkg) {
	BaseType::fromDataPackage(pkg);
	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}
	float x,y,z,w;
	pkg.get(prefix+"position/x", &x);
	pkg.get(prefix+"position/y", &y);
	pkg.get(prefix+"position/z", &z);
	position = base::Position(x,y,z);
	pkg.get(prefix+"orientation/x", &x);
	pkg.get(prefix+"orientation/y", &y);
	pkg.get(prefix+"orientation/z", &z);
	pkg.get(prefix+"orientation/w", &w);
	orientation = base::Orientation(w,x,y,z);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
