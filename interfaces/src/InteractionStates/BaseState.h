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
	static envire::core::TransformGraph transformGraph_;
	static const std::string root_;
	void makeSureTransformFromExists(FrameId& other);
	void makeSureTransformToExists(FrameId& other);

protected:
    template <class T>
	void updateItem(const T &item);
    template <class T>
	void removeItem(const T &item);
    template <class T>
	void addItem(const T &item);
	FrameId frame_;
	std::string name_;
};

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONSTATES_BASESTATE_H_ */
