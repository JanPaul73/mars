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

namespace mars {
namespace interaction {
namespace state {
using namespace envire::core;

class BaseState { //TODO: More complex types like a hand or a skeleton should be made out of more than one of such objects, inheriting from "BaseComplexState"
public:
	BaseState(const std::string& name="BaseState");
	static envire::core::EnvireGraph envireGraph_;
	virtual ~BaseState();

	void updateWorldTransform(Transform& tf);
	void updateTransformTo(Transform& tf, FrameId& other);
	void updateTransformFrom(Transform& tf, FrameId& other);
private:
	static const std::string root_;
	void makeSureTransformFromExists(FrameId& other);
	void makeSureTransformToExists(FrameId& other);

protected:
    template <typename Item>
	void updateItem(const Item &item)
	{
	 removeItem(item); //Removed before just to trigger the add event, adding an "itemChanged" event to Envire2 would be nicer
	 addItem(item);
	}
    template <typename Item>
	void removeItem(const Item &item)
	{
	 envireGraph_.removeItemFromFrame(item);
	}
    template <typename Item>
	void addItem(const Item &item)
	{
	 envireGraph_.addItemToFrame(frame_, item);
	}
	FrameId frame_;
	std::string name_;
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_ */
