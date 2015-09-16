/*
 * Finger.cpp
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#include "Finger.h"

namespace mars {
namespace interaction {
namespace datatype {

Finger::Finger(std::string name) :
	BaseType(name),
	pose(name+"/pose"),
	carpPos(name+"/carpPos"),
	mcpPos(name+"/mcpPos"),
	pipPos(name+"/pipPos"),
	dipPos(name+"/dipPos"),
	btipPos(name+"/btipPos")
{
}

Finger::~Finger() {
}

const Pose& Finger::getPose() const {
	return pose;
}

const utils::Vector& Finger::getBtipPos() const {
	return btipPos.getData();
}

const utils::Vector& Finger::getDipPos() const {
	return dipPos.getData();
}

const utils::Vector& Finger::getPipPos() const {
	return pipPos.getData();
}

const utils::Vector& Finger::getMcpPos() const {
	return mcpPos.getData();
}

const utils::Vector& Finger::getCarpPos() const {
	return carpPos.getData();
}

void Finger::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);
	pose.toDataPackage(pkg);
	carpPos.toDataPackage(pkg);
	mcpPos.toDataPackage(pkg);
	pipPos.toDataPackage(pkg);
	dipPos.toDataPackage(pkg);
	btipPos.toDataPackage(pkg);
}

void Finger::fromDataPackage(const data_broker::DataPackage& pkg) {
	BaseType::fromDataPackage(pkg);
	pose.fromDataPackage(pkg);
	carpPos.fromDataPackage(pkg);
	mcpPos.fromDataPackage(pkg);
	pipPos.fromDataPackage(pkg);
	dipPos.fromDataPackage(pkg);
	btipPos.fromDataPackage(pkg);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
