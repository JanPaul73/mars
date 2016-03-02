/*
 * BaseStateEventDispatcher.cpp
 *
 *  Created on: 23.02.2016
 *      Author: Jan Paul
 */

#include "BaseStateEventDispatcher.h"

namespace mars {
namespace interaction {
namespace state {

BaseStateEventDispatcher::BaseStateEventDispatcher() : GraphEventDispatcher(&(mars::interaction::state::BaseState().envireGraph_)) {
	                                                   //envireGraph_ should exist already as it is static and will exist as just for this call we temporarily create a BaseState instance on the stack. (Accessing envireGraph_ directly produced an "invalid use of qualified-name" error.)
                                                       //Only works when called here, calling it below has the same effect as calling GraphEventDispatcher() without arguments
	//std::cout << "Creating BaseStateEventDispatcher.\n";
	//std::cout << "Creating temp BaseState to get envireGraph_.\n";
	//GraphEventDispatcher(&(mars::interaction::state::BaseState().envireGraph_)); //does not work, has the same effect as calling GraphEventDispatcher() without arguments, must be done above!
	//std::cout << "Created (and most probably correctly destroyed) temp BaseState to get envireGraph_.\n";
}

BaseStateEventDispatcher::~BaseStateEventDispatcher() {
	//std::cout << "Deleting BaseStateEventDispatcher.\n";
	// TODO Auto-generated destructor stub
}

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
