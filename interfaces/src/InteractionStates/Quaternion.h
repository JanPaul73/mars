/*
 * Quaternion.h
 *
 *  Created on: 16.09.2015
 *      Author: Jan Paul
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_QUATERNION_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_QUATERNION_H_

#include "BaseType.h"
#include <mars/utils/Quaternion.h>

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Quaternion: public BaseType {
public:
	Quaternion(std::string name ="quaternion");
	virtual ~Quaternion();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	const utils::Quaternion& getData() const;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

	const utils::Quaternion& getQuaternion() const {
		return quat;
	}
	void setQuaternion(const mars::utils::Quaternion& quat) {
		this->quat = quat;
	}

protected:
	utils::Quaternion quat; //#JanPaul: Maybe instead of using "/MARS/simulation/mars/common/utils/src/Vector.h"
	                      //use "Vector3d" from "/MARS/rock/base-types/base/Eigen.hpp" to be more consequent?
	                      //Wrench ("/MARS/rock/base-types/base/Wrench.hpp"),
	                      //which "/MARS/simulation/mars/interfaces/src/InteractionTypes/ForceTorque.h" is based on,
	                      //also uses "Vector3d" from "/MARS/rock/base-types/base/Eigen.hpp"
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VEC3_H_ */