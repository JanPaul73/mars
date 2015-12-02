/*
 * Leg.h
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_LEG_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_LEG_H_

#include "BaseType.h"
#include "Vec3.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Leg: public BaseType {
public:
	Leg(std::string name ="leg");
	virtual ~Leg();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

	const Vec3& getAnklePos() const;
	const Vec3& getFootPos() const;
	const Vec3& getHipPos() const;
	const Vec3& getKneePos() const;

protected:
	Vec3 hipPos, kneePos, anklePos, footPos; //#JanPaul: Again, only positions?
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_LEG_H_ */
