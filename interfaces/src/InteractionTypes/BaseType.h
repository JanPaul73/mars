/*
 * BaseType.h
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_BASETYPE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_BASETYPE_H_

#include <string>
#include <mars/data_broker/DataPackage.h>

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class BaseType {
public:
	BaseType(std::string name);
	virtual ~BaseType();

	int getTimestamp() const;
	float getUncertainty() const;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

protected:
	std::string name;
	int timestamp;
	float uncertainty;
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_BASETYPE_H_ */

/*

#include "Quaternion.h"
#include "Vector.h"

class Finger : public BaseType {
public:
	Finger() : BaseType() {

	}
	virtual ~Finger();

	data_broker::DataPackage toDataPackage() const {
		data_broker::DataPackage package = pose.toDataPackage();

		return package;
	}

	void fromDataPackage(const data_broker::DataPackage& package) {

	}

private:
	Pose pose;
	mars::utils::Vector btipPos;
	mars::utils::Vector dipPos;
	mars::utils::Vector pipPos;
	mars::utils::Vector mcpPos;
	mars::utils::Vector carpPos;
};

struct Hand : public BaseType {
	Pose pose;
	Finger pinky;
	Finger thumb;
	Finger middleFinger;
	Finger ringFinger;
	Finger indexFinger;
	mars::utils::Vector palmPos;
	mars::utils::Vector palmNormal;
	mars::utils::Vector wristPos;
};

struct Arm : public BaseType {
	Hand hand;
	mars::utils::Vector elbowPos;
	mars::utils::Vector shoulderPos;
};

struct Leg : public BaseType {
	mars::utils::Vector hipPos;
	mars::utils::Vector kneePos;
	mars::utils::Vector anklePos;
	mars::utils::Vector footPos;
};

struct FullBody : public BaseType {
	Arm leftArm;
	Arm rightArm;
	Head head;
	Leg leftLeg;
	Leg rightLeg;
	mars::utils::Vector shoulderCenter;
	mars::utils::Vector spinePos;
	mars::utils::Vector hipCenter;
};

};
};
*/
