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
#include <mars/utils/Vector.h>
#include <mars/utils/Quaternion.h>

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

	void setVelocity6D(mars::utils::Vector trans, mars::utils::Quaternion rot);

	const Quaternion& getRotational() const {
		return rotational;
	}

	void setRotational(const Quaternion& rotational) {
		this->rotational = rotational;
	}

	const Vec3& getTranslational() const {
		return translational;
	}

	void setTranslational(const Vec3& translational) {
		this->translational = translational;
	}

protected:
	Vec3 translational;
	Quaternion rotational;
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_VELOCITY6D_H_ */
