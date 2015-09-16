/*
 * Finger.h
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FINGER_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FINGER_H_

#include "BaseType.h"
#include "Pose.h"
#include "Vec3.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Finger: public BaseType {
public:
	Finger(std::string name);
	virtual ~Finger();

	const Pose& getPose() const;
	const utils::Vector& getBtipPos() const;
	const utils::Vector& getDipPos() const;
	const utils::Vector& getPipPos() const;
	const utils::Vector& getMcpPos() const;
	const utils::Vector& getCarpPos() const;

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

protected:
	Pose pose;
	/* Does not work due to Vec3 having non-trivial default and copy constructor, destructor and copy assignment operator!
	 	union {
		struct {
			Vec3 carpPos;
			Vec3 mcpPos;
			Vec3 pipPos;
			Vec3 dipPos;
			Vec3 btipPos;
		};
		Vec3 joints[5];
	};*/
	Vec3 carpPos;
	Vec3 mcpPos;
	Vec3 pipPos;
	Vec3 dipPos;
	Vec3 btipPos;

};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FINGER_H_ */
