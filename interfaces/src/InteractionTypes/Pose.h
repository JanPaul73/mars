/*
 * Pose.h
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_POSE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_POSE_H_

#include "BaseType.h"
#include <base/Pose.hpp>
#include <mars/utils/Vector.h>
#include <mars/utils/Quaternion.h>

namespace mars {
namespace interaction {
namespace datatype {
using namespace mars::utils;

/*
 *
 */
class Pose: public BaseType, public base::Pose {
public:
	Pose(std::string name ="pose"); //constructor with default name parameter for simple "Pose p;", also for all the other types
	virtual ~Pose();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

	void setPose(Vector trans, Quaternion rot);

    //Position    position;
    //Orientation orientation;

	const utils::Vector& getPosition() const {
		return position;
	}

	void setVector(const base::Position& position) {
		this->position = position;
	}

	const utils::Vector& getOrientation() const {
		return orientation;
	}

	void setOrientation(const base::Orientation& orientation) {
		this->orientation = orientation;
	}
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_POSE_H_ */
