/*
 * BaseState.h
 *
 *  Created on: 27.11.2015
 *      Author: Jan Paul
 *
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_

#include <envire_core/all>
#include "BaseType.h"

#include <string>
#include "Pose.h"
#include "Velocity6D.h"
#include <mars/utils/Vector.h>
#include <mars/utils/Quaternion.h>
#include <envire_core/items/Frame.hpp>
#include <envire_core/graph/TransformGraph.hpp>

namespace mars {
namespace interaction {
namespace state {
using namespace mars::interaction::datatype;
using namespace envire::core;

class BaseState { //TODO: More complex types like a hand or a skeleton should be made out of more than one of such objects, inheriting from "BaseComplexState"
public:
	BaseState(const std::string& name="BaseState");
	virtual ~BaseState();

	void updateWorldTransform(Transform& tf);
	void updateTransformTo(Transform& tf, FrameId& other);
	void updateTransformFrom(Transform& tf, FrameId& other);
	static envire::core::EnvireGraph envireGraph_;
	FrameId frame_;
	static const std::string root_;

	const Pose& getPoseState() const {
		return poseState_;
	}

	void setPoseState(const Pose& poseState);
	void setPoseState(const mars::utils::Vector &trans, const mars::utils::Quaternion &rot);
private:
	Pose poseState_;
	void makeSureTransformFromExists(FrameId& other);
	void makeSureTransformToExists(FrameId& other);
    void updateWorldTransform();
protected:
    template <typename Item>
	void updateItem(const Item &item)
	{
     //std::cout << "updating Item\n";
	 removeItem(item); //Removed before just to be able to trigger an add event after that, adding an "itemChanged" event to Envire2 would be nicer
	 addItem(item);
	}
    template <typename Item>
	void removeItem(const Item &item)
	{
     //std::cout << "removing Item\n";
	 envireGraph_.removeItemFromFrame(item);
	}
    template <typename Item>
	void addItem(const Item &item)
	{
     //std::cout << "adding Item\n";
	 envireGraph_.addItemToFrame(frame_, item);
	}
	std::string name_;
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_ */
