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

BaseStateEventDispatcher::BaseStateEventDispatcher() {
 GraphEventDispatcher(&(mars::interaction::state::BaseState().envireGraph_)); //envireGraph_ should exist already as it is static and will exist as just for this call we temporarily create a BaseState instance on the stack. (Accessing envireGraph_ directly produced an "invalid use of qualified-name" error.)
}

BaseStateEventDispatcher::~BaseStateEventDispatcher() {
	// TODO Auto-generated destructor stub
}

} /* namespace state */
} /* namespace interaction */
} /* namespace mars */
