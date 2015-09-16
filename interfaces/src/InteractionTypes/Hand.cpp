/*
 * Hand.cpp
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#include "Hand.h"

namespace mars {
namespace interaction {
namespace datatype {

Hand::Hand(std::string name) :
	BaseType(name),
	pose(name+"/pose"),
	palmPos(name+"/palmPos"),
	palmNormal(name+"/palmNormal"),
	wristPos(name+"/wristPos"),
	thumb(name+"/thumb"),
	indexFinger(name+"/indexFinger"),
	middleFinger(name+"/middleFinger"),
	ringFinger(name+"/ringFinger"),
	pinky(name+"/pinky")
{

}

Hand::~Hand() {
}

void Hand::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg);
	pose.toDataPackage(pkg);
	palmPos.toDataPackage(pkg);
	palmNormal.toDataPackage(pkg);
	wristPos.toDataPackage(pkg);
	thumb.toDataPackage(pkg);
	indexFinger.toDataPackage(pkg);
	middleFinger.toDataPackage(pkg);
	ringFinger.toDataPackage(pkg);
	pinky.toDataPackage(pkg);
}

void Hand::fromDataPackage(const data_broker::DataPackage& pkg) {
	BaseType::fromDataPackage(pkg);
	pose.fromDataPackage(pkg);
	palmPos.fromDataPackage(pkg);
	palmNormal.fromDataPackage(pkg);
	wristPos.fromDataPackage(pkg);
	thumb.fromDataPackage(pkg);
	indexFinger.fromDataPackage(pkg);
	middleFinger.fromDataPackage(pkg);
	ringFinger.fromDataPackage(pkg);
	pinky.fromDataPackage(pkg);
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
