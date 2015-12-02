/*
 * Hand.h
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_HAND_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_HAND_H_

#include "BaseType.h"
#include "Finger.h"
#include "Vec3.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Hand: public BaseType {
public:
	Hand(std::string name ="hand");
	virtual ~Hand();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

	const Finger& getIndexFinger() const {
		return indexFinger;
	}

	const Finger& getMiddleFinger() const {
		return middleFinger;
	}

	const Vec3& getPalmNormal() const {
		return palmNormal;
	}

	const Vec3& getPalmPos() const {
		return palmPos;
	}

	const Finger& getPinky() const {
		return pinky;
	}

	const Pose& getPose() const {
		return pose;
	}

	const Finger& getRingFinger() const {
		return ringFinger;
	}

	const Finger& getThumb() const {
		return thumb;
	}

	const Vec3& getWristPos() const {
		return wristPos;
	}

protected:
	Pose pose;
	Vec3 palmPos;  //#JanPaul: Sure we only need positions and not poses and/or joint angle positions?
                   //It would at least be good to maybe only store data about these parts in only one form
                   //and then be able to get/set the same data in other forms. For example set only joint angle
                   //positions by setter methods, store only positions (3d) in variables and later get
                   //limb (finger etc.) poses from getter methods if needed. As storing positions needs
                   //(simple) per-joint inverse kinematics to calculate joint angle positions and poses from that,
                   //storing poses or joint angle positions might be better. In any case, additionally the rotation
                   //axis of each joint should be stored somehow additionally as this will be needed for all those
                   //conversions.
	Vec3 palmNormal;
	Vec3 wristPos;
	Finger thumb, indexFinger, middleFinger, ringFinger, pinky;
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_HAND_H_ */
