/*
 * SpaceMouse.h
 *
 *  Created on: 27.11.2015
 *      Author: Jan Paul
 */

#include <string>
#include <mars/interfaces/Pose.h>
#include <mars/interfaces/Velocity6D.h>
//#include <envire_core/items/Frame.hpp>

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_

namespace mars {
namespace interaction {
namespace state {

class SpaceMouse {
public:
	SpaceMouse(const std::string& name="SpaceMouse"); //In case we want two or more Space Mice, give it a unique name in the Envire2 graph
	virtual ~SpaceMouse();
	void setState();
private:
	mars::interaction::datatype::Pose poseState_;
	mars::interaction::datatype::Velocity6D velocityState_;
	std::string name_;
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_ */
