/*
 * BaseType.cpp
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#include "BaseType.h"

namespace mars {
namespace interaction {
namespace datatype {

BaseType::BaseType(std::string name) :
		name(name),
		timestamp(-1),
		uncertainty(0)
{
}

BaseType::~BaseType() {
}

int BaseType::getTimestamp() const
{
	return timestamp;
}

float BaseType::getUncertainty() const
{
	return uncertainty;
}

void BaseType::toDataPackage(data_broker::DataPackage& pkg) const
{
	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}
	pkg.add(prefix+"timestamp", timestamp);
	pkg.add(prefix+"uncertainty", uncertainty);
}

void BaseType::fromDataPackage(const data_broker::DataPackage& pkg)
{
	std::string prefix = "";
	if(!name.empty()) {
		prefix = name + "/";
	}
	pkg.get(prefix+"timestamp", &timestamp);
	pkg.get(prefix+"uncertainty", &uncertainty);
}


} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
