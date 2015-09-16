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

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Pose: public BaseType, public base::Pose {
public:
	Pose(std::string name);
	virtual ~Pose();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_POSE_H_ */
