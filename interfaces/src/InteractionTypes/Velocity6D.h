/*
 * Velocity6D.h
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VELOCITY6D_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VELOCITY6D_H_

#include "BaseType.h"
#include "Vec3.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Velocity6D: public BaseType {
public:
	Velocity6D(std::string name);
	virtual ~Velocity6D();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

protected:
	Vec3 translational;
	Vec3 rotational;
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VELOCITY6D_H_ */
