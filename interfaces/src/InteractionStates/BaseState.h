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
	virtual ~BaseState();

	void updateWorldTransform(Transform& tf);
	void updateTransformTo(Transform& tf, FrameId& other);
	void updateTransformFrom(Transform& tf, FrameId& other);
private:
	static envire::core::EnvireGraph envireGraph_;
	static const std::string root_;
	void makeSureTransformFromExists(FrameId& other);
	void makeSureTransformToExists(FrameId& other);

protected:
	void updateItem(const Item<mars::interaction::datatype::BaseType *>::Ptr &item);
	void removeItem(const Item<mars::interaction::datatype::BaseType *>::Ptr &item);
	void addItem(const Item<mars::interaction::datatype::BaseType *>::Ptr &item);
	FrameId frame_;
	std::string name_;
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_ */
