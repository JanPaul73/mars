/*
 * Vec3.h
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VEC3_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VEC3_H_

#include "BaseType.h"
#include <mars/utils/Vector.h>

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Vec3: public BaseType {
public:
	Vec3(std::string name ="vec3");
	virtual ~Vec3();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

	const utils::Vector& getData() const{
		return getVector();
	}

	const utils::Vector& getVector() const {
		return vector;
	}

	void setVector(const mars::utils::Vector& vector) {
		this->vector = vector;
	}

protected:
	utils::Vector vector; //#JanPaul: Maybe instead of using "/MARS/simulation/mars/common/utils/src/Vector.h"
	                      //use "Vector3d" from "/MARS/rock/base-types/base/Eigen.hpp" to be more consequent?
	                      //Wrench ("/MARS/rock/base-types/base/Wrench.hpp"),
	                      //which "/MARS/simulation/mars/interfaces/src/InteractionTypes/ForceTorque.h" is based on,
	                      //also uses "Vector3d" from "/MARS/rock/base-types/base/Eigen.hpp"
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VEC3_H_ */
