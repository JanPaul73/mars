/*
 * FullBody.h
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FULLBODY_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FULLBODY_H_

#include "BaseType.h"
#include "Arm.h"
#include "Head.h"
#include "Leg.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class FullBody: public BaseType {
public:
	FullBody(std::string name);
	virtual ~FullBody();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

	const Head& getHead() const;
	const Vec3& getHipCenter() const;
	const Arm& getLeftArm() const;
	const Leg& getLeftLeg() const;
	const Arm& getRightArm() const;
	const Leg& getRightLeg() const;
	const Vec3& getShoulderCenter() const;
	const Vec3& getSpinePos() const;

protected:
	Arm leftArm, rightArm;
	Head head;
	Leg leftLeg, rightLeg;
	Vec3 shoulderCenter, spinePos, hipCenter;
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FULLBODY_H_ */
