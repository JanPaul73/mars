/*
 * SpaceMouse.h
 *
 *  Created on: 27.11.2015
 *      Author: jan
 */


//#include <envire_core/items/Frame.hpp>

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_

class SpaceMouse {
public:
	SpaceMouse(const std::string& name) : name_(name) {}; //In case we want two or more Space Mice, give it a unique name in the Envire2 graph
	SpaceMouse() : name_("SpaceMouse") {};
	virtual ~SpaceMouse();
private:
	mars::interaction::datatype::Pose poseState_;
	mars::interaction::datatype::Velocity6D velocityState_;
	std::string name_="SpaceMouse";
};

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_ */
