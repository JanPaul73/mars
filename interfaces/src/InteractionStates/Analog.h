/*
 * Analog.h
 *
 *  Created on: 16.09.2015
 *      Author: mmaurus
 */

#ifndef SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_ANALOG_H_
#define SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_ANALOG_H_

#include "BaseType.h"

namespace mars {
namespace interaction {
namespace datatype {

/*
 *
 */
class Analog: public BaseType {
public:
	Analog(std::string name ="analog");
	virtual ~Analog();

	float getValue() const; //#JanPaul: why no setters?

	using BaseType::toDataPackage;
	using BaseType::fromDataPackage;

	void toDataPackage(data_broker::DataPackage& pkg) const;
	void fromDataPackage(const data_broker::DataPackage& pkg);

protected:
	float value;
};

} /* namespace datatype */
} /* namespace interaction */
} /* namespace mars */

#endif /* SIMULATION_MARS_INTERFACES_SRC_INTERACTIONTYPES_ANALOG_H_ */
