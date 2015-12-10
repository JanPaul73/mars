/*
 * Head.h
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_HEAD_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_HEAD_H_

#include "BaseType.h"
#include "Pose.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Head: public BaseType {
public:
	Head(std::string name ="head");
	virtual ~Head();

	const Pose& getPose() const;

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);
protected:
	Pose pose;
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_HEAD_H_ */
