/*
 * Arm.h
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_ARM_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_ARM_H_

#include "BaseType.h"
#include "Hand.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Arm: public BaseType {
public:
	Arm(std::string name ="arm");
	virtual ~Arm();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

	const Vec3& getElbowPos() const;
	const Hand& getHand() const;
	const Vec3& getShoulderPos() const;

protected:
	Hand hand;
	Vec3 elbowPos;    //#JanPaul: again the question if positions without at least a rotation axis are enough
	Vec3 shoulderPos; //#JanPaul: 3d position relative to what? Body center?
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_ARM_H_ */