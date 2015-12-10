/*
 * ForceTorque.h
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FORCETORQUE_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FORCETORQUE_H_

#include "BaseType.h"
#include <base/Wrench.hpp>

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class ForceTorque: protected base::Wrench, public BaseType {
public:
	ForceTorque(std::string name ="forceTorque");
	virtual ~ForceTorque();

	const base::Vector3d& getForce() const;
	const base::Vector3d& getTorque() const;

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_FORCETORQUE_H_ */
