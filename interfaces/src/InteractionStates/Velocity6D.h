/*
 * Velocity6D.h
 *
 *  Created on: 15.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VELOCITY6D_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VELOCITY6D_H_

#include "BaseType.h"
#include <mars/utils/Vector.h>
#include <mars/utils/Quaternion.h>
#include "Vec3.h"
#include "Quaternion.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Velocity6D: public BaseType {
public:
	Velocity6D(std::string name ="velocity6D");
	virtual ~Velocity6D();

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

	void setVelocity6D(const mars::utils::Vector& trans, const mars::utils::Quaternion& rot);

	const datatype::Quaternion& getRotational() const {
		return rotational;
	}

	void setRotational(const datatype::Quaternion& rotational) {
		this->rotational = rotational;
	}

	const datatype::Vec3& getTranslational() const {
		return translational;
	}

	void setTranslational(const datatype::Vec3& translational) {
		this->translational = translational;
	}

protected:
	datatype::Vec3 translational;
	datatype::Quaternion rotational;
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VELOCITY6D_H_ */
