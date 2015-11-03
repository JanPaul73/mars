/*
 * FullBody.cpp
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#include "FullBody.h"

namespace mars {
namespace interaction {
namespace datatype {

FullBody::~FullBody() {
}

const Head& FullBody::getHead() const {
	return head;
}

const Vec3& FullBody::getHipCenter() const {
	return hipCenter;
}

const Arm& FullBody::getLeftArm() const {
	return leftArm;
}

const Leg& FullBody::getLeftLeg() const {
	return leftLeg;
}

const Arm& FullBody::getRightArm() const {
	return rightArm;
}

const Leg& FullBody::getRightLeg() const {
	return rightLeg;
}

const Vec3& FullBody::getShoulderCenter() const {
	return shoulderCenter;
}

FullBody::FullBody(std::string name) :
	BaseType(name),
	leftArm(name+"/leftArm"),
	rightArm(name+"/rightArm"),
	head(name+"/head"),
	leftLeg(name+"/leftLeg"),
	rightLeg(name+"/rightLeg"),
	shoulderCenter(name+"/shoulderCenter"),
	spinePos(name+"/spinePos"),
	hipCenter(name+"/hipCenter")
{
}

void FullBody::toDataPackage(data_broker::DataPackage& pkg) const {
	BaseType::toDataPackage(pkg); //#JanPaul: This will not be unique as "get" in "fromDataPackage" will use
	                              //"DataItem *dataItem = getItemByName(itemName);"
	                              //and the arms and legs will contain values with non unique names.
	                              //Solution: Each of these datatypes needs its own name (already there and
	                              //in constructor, just not initialized) which must then be prefixed to the data item
	                              //with a "/" (already done in "Pose" for example). All parents' names need to be
	                              //prefixed, too, by something like e.g.
	                              //Arm leftArm(this->name+"/"+"leftArm"), rightArm(this->name+"/"+"leftArm");
	                              //so that data items like "Body1/leftArm/elbowPos/x" are sent and received.
	                              //(The above example should be replaced by a more elegant solution like
	                              //"this->addLeftArm(...);" .)
	leftArm.toDataPackage(pkg);
	rightArm.toDataPackage(pkg);
	head.toDataPackage(pkg);
	leftLeg.toDataPackage(pkg);
	rightLeg.toDataPackage(pkg);
	shoulderCenter.toDataPackage(pkg);
	spinePos.toDataPackage(pkg);
	hipCenter.toDataPackage(pkg);
}

void FullBody::fromDataPackage(const data_broker::DataPackage& pkg) {
	BaseType::fromDataPackage(pkg);
	leftArm.fromDataPackage(pkg);
	rightArm.fromDataPackage(pkg);
	head.fromDataPackage(pkg);
	leftLeg.fromDataPackage(pkg);
	rightLeg.fromDataPackage(pkg);
	shoulderCenter.fromDataPackage(pkg);
	spinePos.fromDataPackage(pkg);
	hipCenter.fromDataPackage(pkg);
}

const Vec3& FullBody::getSpinePos() const {
	return spinePos;
}

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */
