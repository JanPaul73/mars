#ifndef INTERACTIONTYPES_H
#define INTERACTIONTYPES_H

#include "Pose.hpp"
#include "Wrench.hpp"
#include "Quaternion.h"
#include "Vector.h"
namespace mars {
namespace InteractionTypes {

struct BaseType : public mars::data_broker::DataPackage {
	int timestamp;
	float uncertainty;
};

struct Pose : public base::Pose, public BaseType {

};

struct ForceTorque : public base::Wrench, public BaseType {

};

struct Velocity6D : public BaseType {
	mars::utils::Vector translational;
	mars::utils::Vector rotational;
};

struct Analog : public BaseType {
	float value;
};

struct Head : public BaseType {
	Pose pose;
};

struct Finger : public BaseType {
	Pose pose;
	mars::utils::Vector btipPos;
	mars::utils::Vector dipPos;
	mars::utils::Vector pipPos;
	mars::utils::Vector mcpPos;
	mars::utils::Vector carpPos;
};

struct Hand : public BaseType {
	Pose pose;
	Finger pinky;
	Finger thumb;
	Finger middleFinger;
	Finger ringFinger;
	Finger indexFinger;
	mars::utils::Vector palmPos;
	mars::utils::Vector palmNormal;
	mars::utils::Vector wristPos;
};

struct Arm : public BaseType {
	Hand hand;
	mars::utils::Vector elbowPos;
	mars::utils::Vector shoulderPos;
};

struct Leg : public BaseType {
	mars::utils::Vector hipPos;
	mars::utils::Vector kneePos;
	mars::utils::Vector anklePos;
	mars::utils::Vector footPos;
};

struct FullBody : public BaseType {
	Arm leftArm;
	Arm rightArm;
	Head head;
	Leg leftLeg;
	Leg rightLeg;
	mars::utils::Vector shoulderCenter;
	mars::utils::Vector spinePos;
	mars::utils::Vector hipCenter;
};

};
};

#endif //INTERACTIONTYPES_H
