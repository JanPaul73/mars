/*
 * Analog.cpp
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#include "Analog.h"

namespace mars {
namespace interaction {
namespace datatype {

Analog::Analog(std::string name) :
	BaseType(name)
{
	value=0.0f;
}

Analog::~Analog() {
}

float Analog::getValue() const {
	return value;
}

void Analog::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);

	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}

	pkg.add(prefix+"value", value);
}

void Analog::fromDataPackage(const data_broker::DataPackage& pkg) {

	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}

	BaseType::fromDataPackage(pkg);
	pkg.get(prefix+"value", &value);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
