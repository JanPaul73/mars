/*
 * SpaceMouse.h
 *
 *  Created on: 27.11.2015
 *      Author: Jan Paul
 */

#include <string>
#include "Pose.h"
#include "Velocity6D.h"
#include <mars/utils/Vector.h>
#include <mars/utils/Quaternion.h>
#include <envire_core/items/Frame.hpp>
#include <envire_core/graph/TransformGraph.hpp>
#include "BaseState.h"

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_

namespace mars {
namespace interaction {
namespace state {
using namespace mars::interaction::datatype;

class SpaceMouse : public BaseState{
public:
	SpaceMouse(const std::string& name="SpaceMouse"); //In case we want two or more Space Mice, give it a unique name in the Envire2 graph
	virtual ~SpaceMouse();

	void setVelocityState(const Velocity6D& velocityState);
	void setVelocityState(const mars::utils::Vector &trans, const mars::utils::Quaternion &rot);

private:
	Velocity6D velocityState_;
    Item<Velocity6D>::Ptr* velocityStateItem_;
    void updateVelocityState();
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_SPACEMOUSE_H_ */
