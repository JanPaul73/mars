/*
 *  Copyright 2011, 2012, DFKI GmbH Robotics Innovation Center
 *
 *  This file is part of the MARS simulation framework.
 *
 *  MARS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  MARS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * \file ConnexionPlugin.cpp
 * \author Michael Rohn
 * \brief A Plugin to use the 3D-Mouse by 3Dconnexion in MARS to control the camera
 */

#include "ConnexionPlugin.h"
#include "ConnexionHID.h"

#include <mars/interfaces/sim/NodeManagerInterface.h>
#include <mars/interfaces/graphics/GraphicsManagerInterface.h>
#include <mars/interfaces/Logging.hpp>
#include <cstdio>

namespace mars {
namespace plugins {
namespace connexion_plugin {

using namespace lib_manager;
using namespace mars::interfaces;
using namespace mars::utils;
using namespace mars::sim;

ConnexionPlugin::ConnexionPlugin(LibManager *theManager) :
		QThread(), MarsPluginTemplateGUI(theManager,
				std::string("ConnexionPlugin")), camMutex(QMutex::Recursive) {
	//                                           ^JP: To avoid deadlocks due to event system leading to multiple locks of this mutex in sequence
	//std::cout << "Creating ConnexionPlugin.\n";

	thread_closed = false;
	myWidget = NULL;
	object_id = 0;
	win_id = 1;
	object_mode = 1;
	resetCam = false;
	name = "ConnexionPlugin";
	for (int i = 0; i < 6; i++) {
		use_axis[i] = 1;
		sensitivity[i] = 1.0;
	}
	sensitivity[0] = 2.0;
	sensitivity[1] = 2.0;
	sensitivity[2] = 2.0;

	isInit = false;
	init();
	newValues = new connexionValues;
	//std::cout << "Creating BaseStateEventDispatcher from ConnexionPlugin.\n";
	mars::interaction::state::BaseStateEventDispatcher();
	//std::cout << "Created BaseStateEventDispatcher from ConnexionPlugin.\n";
}

void ConnexionPlugin::init() {
	if (!control->graphics || isInit)
		return;
	isInit = true;

	// add options to the menu
	if (gui) {
		std::string tmp = resourcesPath
				+ "/mars/plugins/connexion_plugin/connexion.png";
		gui->addGenericMenuAction("../Windows/Parameter", 1, this, 0, tmp,
				true);
	}

	is_init = false;

	camReset();
	if (initConnexionHID(0)) {
		LOG_INFO("%s: Device registered", name.c_str());
		LOG_INFO("%s: running ...", name.c_str());
		is_init = true;
	} else {
		LOG_ERROR("%s: not able to register Device.", name.c_str());
		run_thread = false;
	}

	LOG_INFO("%s: loaded", name.c_str());
	if (is_init) {
		run_thread = true;
		LOG_INFO("%s: starting ...", name.c_str());
		this->start();
	} else {
		run_thread = false;
		thread_closed = true;
		LOG_ERROR("%s: init not successful.", name.c_str());
	}

	// set update to gui update
	if (control->graphics) {
		control->graphics->addGraphicsUpdateInterface(this);
	}

}

ConnexionPlugin::~ConnexionPlugin(void) {
	fprintf(stderr, "Delete ConnexionPlugin\n");
	run_thread = false;

	while (!thread_closed && isInit) {
		msleep(10);
	}

	closeConnexionHID();
	delete newValues;
}

//void ConnexionPlugin::updateSpaceMouseState() {
//	std::cout << "updateSpaceMouseState.\n";
//	//JP: This is never called!!
//
//	double data[7];
//	Quaternion q(1.0, 0.0, 0.0, 0.0);
//
//	camMutex.lock();
//	sReal tmpCamState[7];
//	tmpCamState[0] = camState[0];
//	tmpCamState[1] = camState[1];
//	tmpCamState[2] = camState[2];
//	tmpCamState[3] = camState[3];
//	tmpCamState[4] = camState[4];
//	tmpCamState[5] = camState[5];
//	tmpCamState[6] = camState[6];
//	Vector trans(camState[0], camState[1], camState[2]);
//	Quaternion qRot(camState[6], camState[3], camState[4], camState[5]);
//	camState[0] = 0.0;
//	camState[1] = 0.0;
//	camState[2] = 0.0;
//	camState[3] = 0.0; //q.x
//	camState[4] = 0.0; //q.y
//	camState[5] = 0.0; //q.z
//	camState[6] = 1.0; //q.w
//	camMutex.unlock();
//
//	if (object_mode == 1) {
//		//interfaces::GraphicsWindowInterface *gw = control->graphics->get3DWindow(win_id);
//
//		//if (gw) {
//		if (resetCam) {
//			/*gw->getCameraInterface()->updateViewportQuat(tmpCamState[0], //TODO: Jan Paul: Now instead write data into the Envire2 tree using the spaceMouse_ member
//			 tmpCamState[1],
//			 tmpCamState[2],
//			 tmpCamState[3],
//			 tmpCamState[4],
//			 tmpCamState[5],
//			 tmpCamState[6]);*/
//			spaceMouse_.setPoseState(trans, qRot);
//			resetCam = false;
//		}
//		/*gw->getCameraInterface()->getViewportQuat(data, data+1, data+2, //Jan Paul: Now instead read data from the Envire2 tree using the spaceMouse_ member
//		 data+3, data+4, data+5,
//		 data+6);*/
//		data[0] = spaceMouse_.getPoseState().position.x(); //Jan Paul: Now reading data from the Envire2 tree using the spaceMouse_ member
//		data[1] = spaceMouse_.getPoseState().position.y();
//		data[2] = spaceMouse_.getPoseState().position.z();
//
//		data[3] = spaceMouse_.getPoseState().orientation.x();
//		data[4] = spaceMouse_.getPoseState().orientation.y();
//		data[5] = spaceMouse_.getPoseState().orientation.z();
//		data[6] = spaceMouse_.getPoseState().orientation.w();
//
//		q = Quaternion(data[6], data[3], data[4], data[5]);
//		trans = q * trans;
//		q = q * qRot;
//
//		spaceMouse_.setVelocityState(trans, qRot);
//
//		data[0] += trans.x();
//		data[1] += trans.y();
//		data[2] += trans.z();
//
//		trans.x() = data[0];
//		trans.y() = data[1];
//		trans.z() = data[2];
//		/*gw->getCameraInterface()->updateViewportQuat(data[0], data[1], data[2], //Jan Paul: Now instead write data into the Envire2 tree using the spaceMouse_ member and change the camera state in callback reacting to envire2 event
//		 q.x(), q.y(), q.z(), q.w());*/
//		spaceMouse_.setPoseState(trans, q); //Jan Paul: Now writing data into the Envire2 tree using the spaceMouse_ member
//		//}
//	} else if (object_mode == 2) {
//		//interfaces::GraphicsWindowInterface *gw = control->graphics->get3DWindow(win_id);
//
//		//if (gw) {
//		/*gw->getCameraInterface()->getViewportQuat(data, data+1, data+2, //Jan Paul: Now instead read data from the Envire2 tree using the spaceMouse_ member
//		 data+3, data+4, data+5,
//		 data+6);*/
//
//		data[0] = spaceMouse_.getPoseState().position.x(); //Jan Paul: Now reading data from the Envire2 tree using the spaceMouse_ member
//		data[1] = spaceMouse_.getPoseState().position.y();
//		data[2] = spaceMouse_.getPoseState().position.z();
//
//		data[3] = spaceMouse_.getPoseState().orientation.x();
//		data[4] = spaceMouse_.getPoseState().orientation.y();
//		data[5] = spaceMouse_.getPoseState().orientation.z();
//		data[6] = spaceMouse_.getPoseState().orientation.w();
//
//		q = Quaternion(data[6], data[3], data[4], data[5]);
//		trans = q * trans;
//
//		spaceMouse_.setVelocityState(trans, qRot);
//		//}
//		core_objects_exchange node;
//		control->nodes->getNodeExchange(object_id, &node);
//		Quaternion tmpQ(node.rot);
//		Vector tmpV = node.pos;
//
//		//trans = QVRotate(tmpQ, trans);
//		Quaternion qi = q;
//		qi.x() *= -1;
//		qi.y() *= -1;
//		qi.z() *= -1;
//		qRot = q * qRot * qi;
//		//tmpQ = quad_state;
//		tmpQ = qRot * tmpQ;
//		//tmpQ = tmpQ*qi;
//
//		tmpV += trans;
//		NodeData my_node;
//		my_node.index = object_id;
//		my_node.pos = tmpV;
//		my_node.rot = tmpQ;
//		//control->nodes->editNode(&my_node, EDIT_NODE_POS | EDIT_NODE_MOVE_ALL); //Now instead write data into the Envire2 tree using the spaceMouse_ member and TODO: change the object state in callback reacting to envire2 event
//		//control->nodes->editNode(&my_node, EDIT_NODE_ROT | EDIT_NODE_MOVE_ALL);
//
//		std::cout << "Setting pose state from ConnexionPlugin.\n";
//		spaceMouse_.setPoseState(my_node.pos, my_node.rot); //Jan Paul: Now writing data into the Envire2 tree using the spaceMouse_ member
//	}
//}

void ConnexionPlugin::preGraphicsUpdate() {
	double data[7];
	if (newValueReceived) {
		//std::cout << "preGraphicsUpdate.\n";
		//TODO: Jan Paul: This should now be done using an Envire2-Callback (or Envire2 Graph Data)
		//      See: /slam-envire_core/test/test_transform_graph.cpp for event system example
		Quaternion q(1.0, 0.0, 0.0, 0.0);

		//camMutex.lock();

		// Local handling of camState variable that was global before: --------------------------------------------------------------
		/*
		 * state[0..2] -> trans: x,y,z
		 * state[3..6] -> rot: x,y,z,w (quaternion)
		 */
		mars::interfaces::sReal camState[7];

		camMutex.lock();
		base::TransformWithCovariance T =
				spaceMouse_.envireGraph_.getEdgeProperty(spaceMouse_.root_,
						spaceMouse_.frame_).transform;
		camMutex.unlock();
		//^This could be done more directly using spaceMouse_ and its internal states, but the above way is to test and show that the
		// general input interface supports string based property searches, including
		// "e.target == spaceMouse_.frame_" in "ConnexionPlugin::edgeModified".
		Vector trans(T.translation);
		Quaternion qRot(T.orientation);

		camState[0] = trans.x();
		camState[1] = trans.y();
		camState[2] = trans.z();
		camState[3] = qRot.x();
		camState[4] = qRot.y();
		camState[5] = qRot.z();
		camState[6] = qRot.w();
		// End of local handling of camState variable that was global before. --------------------------------------------------------------

		sReal tmpCamState[7];
		tmpCamState[0] = camState[0];
		tmpCamState[1] = camState[1];
		tmpCamState[2] = camState[2];
		tmpCamState[3] = camState[3];
		tmpCamState[4] = camState[4];
		tmpCamState[5] = camState[5];
		tmpCamState[6] = camState[6];

		//Now already done above:
		//Vector trans(camState[0], camState[1], camState[2]);
		//Quaternion qRot(camState[6], camState[3], camState[4], camState[5]);

		//JP: Why is/was this done?
		//    Probably to make the updates stored in camState only be applied once until a new value is received from the SpaceMouse.
		//    TODO: This could also mean that the camState values do not store absolute values but also deltas, which would mean that
		//    wrong values (speed instead of pose) are stored in the spaceMouse_!
		//    For now use a flag to have the "camState only be applied once until a new value is received from the SpaceMouse" effect.
		//    => Probably OK to leave this in, but still the camera keeps moving by itself and when moving the SpaceMouse the effect is
		//       way too fast. Maybe that "speed instead of absolute pose" problem has to be addressed!
//        camState[0] = 0.0;
//        camState[1] = 0.0;
//        camState[2] = 0.0;
//        camState[3] = 0.0; //q.x
//        camState[4] = 0.0; //q.y
//        camState[5] = 0.0; //q.z
//        camState[6] = 1.0; //q.w
//
//    	//JP: As this will trigger a new edgeModified event which will also lock the camMutex, the camMutex has been changed to recursive mode to avoid deadlocks
//    	std::cout << "Setting velocity state from ConnexionPlugin, camReset.\n";
//    	spaceMouse_.setVelocityState(mars::interaction::datatype::Velocity6D());
//    	std::cout << "Setting pose state from ConnexionPlugin, camReset.\n";
//    	spaceMouse_.setPoseState(Vector(camState[0], camState[1], camState[2]), Quaternion(camState[6],camState[3],camState[4],camState[5]));

		newValueReceived = false;

		//camMutex.unlock();

		if (object_mode == 1) {
			interfaces::GraphicsWindowInterface *gw =
					control->graphics->get3DWindow(win_id);

			if (gw) {
				if (resetCam) {
					gw->getCameraInterface()->updateViewportQuat(tmpCamState[0],
							tmpCamState[1], tmpCamState[2], tmpCamState[3],
							tmpCamState[4], tmpCamState[5], tmpCamState[6]);
					resetCam = false;
				}
				//gw->getCameraInterface()->getViewportQuat(data, data + 1,
				//		data + 2, data + 3, data + 4, data + 5, data + 6);

//				q = Quaternion(data[6], data[3], data[4], data[5]);
//				trans = q * trans;
//				q = q * qRot;
//
//				data[0] += trans.x();
//				data[1] += trans.y();
//				data[2] += trans.z();

				q = qRot;
				data[0] = trans.x();
				data[1] = trans.y();
				data[2] = trans.z();

				gw->getCameraInterface()->updateViewportQuat(data[0], data[1],
						data[2], q.x(), q.y(), q.z(), q.w());
			}
		} else if (object_mode == 2) {
			interfaces::GraphicsWindowInterface *gw =
					control->graphics->get3DWindow(win_id);

			if (gw) {
				gw->getCameraInterface()->getViewportQuat(data, data + 1,
						data + 2, data + 3, data + 4, data + 5, data + 6);
				q = Quaternion(data[6], data[3], data[4], data[5]);
				//trans = q * trans;
			}
			core_objects_exchange node;
			control->nodes->getNodeExchange(object_id, &node);
			Quaternion tmpQ(node.rot);
			Vector tmpV = node.pos;

			//trans = QVRotate(tmpQ, trans);
//			Quaternion qi = q;
//			qi.x() *= -1;
//			qi.y() *= -1;
//			qi.z() *= -1;
//			qRot = q * qRot * qi;
			//tmpQ = quad_state;
			tmpQ = qRot;				// * tmpQ;
			//tmpQ = tmpQ*qi;

			tmpV /*+*/= trans;
			NodeData my_node;
			my_node.index = object_id;
			my_node.pos = tmpV;
			my_node.rot = tmpQ;
			control->nodes->editNode(&my_node,
					EDIT_NODE_POS | EDIT_NODE_MOVE_ALL);
			control->nodes->editNode(&my_node,
					EDIT_NODE_ROT | EDIT_NODE_MOVE_ALL);
		}
	} else //Then the 2d mouse might have changed the view or the simulation might have moved the object and we want to mirror that into the space mouse data:
	{
		if (object_mode == 1) {
			setSpaceMouseToCamera();
		} else {
			setSpaceMouseToObject();
		}
	}
}

void ConnexionPlugin::menuAction(int action, bool checked) {
	switch (action) {
	case 1:
		if (!myWidget) {
			myWidget = new ConnexionWidget(control);
			//      control->gui->addDockWidget((void*)myWidget);
			myWidget->show();
			//myWidget->setGeometry(40, 40, 200, 200);
			connect(myWidget, SIGNAL(hideSignal()), this, SLOT(hideWidget()));
			connect(myWidget, SIGNAL(closeSignal()), this, SLOT(closeWidget()));

			myWidget->setWindowID(win_id);
			myWidget->setObjectID(object_id);
			myWidget->setLockAxis(use_axis);
			myWidget->setSensitivity(sensitivity);

			connect(myWidget, SIGNAL(windowSelected(unsigned long)), this,
					SLOT(windowSelected(unsigned long)));
			connect(myWidget, SIGNAL(objectSelected(unsigned long)), this,
					SLOT(objectSelected(unsigned long)));
			connect(myWidget, SIGNAL(setObjectMode(int)), this,
					SLOT(setObjectMode(int)));
			connect(myWidget, SIGNAL(setLockAxis(int, bool)), this,
					SLOT(setLockAxis(int, bool)));
			connect(myWidget, SIGNAL(sigSensitivity(int, double)), this,
					SLOT(setSensitivity(int, double)));
		} else {
			closeWidget();          //myWidget->hide();
		}
		break;
	}
}

void ConnexionPlugin::run() {

	while (run_thread) {
		getValue(motion, newValues);

		motion[0] *= sensitivity[0] * use_axis[0] * 0.01;
		motion[1] *= sensitivity[1] * use_axis[1] * 0.01;
		motion[2] *= sensitivity[2] * use_axis[2] * 0.01;
		motion[3] *= sensitivity[3] * use_axis[3] * 0.001;
		motion[4] *= sensitivity[4] * use_axis[4] * 0.001;
		motion[5] *= sensitivity[5] * use_axis[5] * 0.001;

		updateSpaceMouseRawState(motion);

		if (newValues->button1 == 1) {
			camReset();
		}

		msleep(20/* *500 */); //JP: *500 just to make it slower for testing, remove this!
	}
	LOG_INFO("%s: ... stopped", name.c_str());

	thread_closed = true;
}

void ConnexionPlugin::updateSpaceMouseRawState(sReal motion[6]) {
	//std::cout << "updateSpaceMouseRawState.\n";
	sReal tx, ty, tz;
	sReal rx, ry, rz;

	Quaternion q1, q2, q3;
	Vector move, x_axis, y_axis, z_axis;

	tx = motion[0];  //x-axis
	ty = motion[1];  //y-axis
	tz = motion[2];  //z-axis
	rx = motion[3]; //tilt
	ry = motion[4]; //roll
	rz = motion[5]; //spin

	if (fabs(tx) < 0.0001)
		tx = 0.0;
	if (fabs(ty) < 0.0001)
		ty = 0.0;
	if (fabs(tz) < 0.0001)
		tz = 0.0;

	if (fabs(rx) < 0.0001)
		rx = 0.0;
	if (fabs(ry) < 0.0001)
		ry = 0.0;
	if (fabs(rz) < 0.0001)
		rz = 0.0;

	if (tx != 0.0 || ty != 0.0 || tz != 0.0 || rx != 0.0 || ry != 0.0
			|| rz != 0.0) { //Only create a mouse moved event if there is really a significant movement,
							//otherwise leave the control to the 2D mouse
		x_axis.x() = 1;
		x_axis.y() = 0;
		x_axis.z() = 0;

		y_axis.x() = 0;
		y_axis.y() = 1;
		y_axis.z() = 0;

		z_axis.x() = 0;
		z_axis.y() = 0;
		z_axis.z() = 1;

		//camMutex.lock();

		// Local handling of camState variable that was global before: --------------------------------------------------------------
		/*
		 * state[0..2] -> trans: x,y,z
		 * state[3..6] -> rot: x,y,z,w (quaternion)
		 */
		mars::interfaces::sReal camState[7];

		camMutex.lock();
		base::TransformWithCovariance T =
				spaceMouse_.envireGraph_.getEdgeProperty(spaceMouse_.root_,
						spaceMouse_.frame_).transform;
		//^This could be done more directly using spaceMouse_ and its internal states, but the above way is to test and show that the
		// general input interface supports string based property searches
		camMutex.unlock();
		Vector trans(T.translation);
		Quaternion qRot(T.orientation);

		camState[0] = trans.x();
		camState[1] = trans.y();
		camState[2] = trans.z();
		camState[3] = qRot.x();
		camState[4] = qRot.y();
		camState[5] = qRot.z();
		camState[6] = qRot.w();
		// End of local handling of camState variable that was global before. --------------------------------------------------------------

		Quaternion tmpQuatState(camState[6], camState[3], camState[4],
				camState[5]);

		x_axis = tmpQuatState * x_axis;
		y_axis = tmpQuatState * y_axis;
		z_axis = tmpQuatState * z_axis;

		qFromAxisAndAngle(q1, x_axis, rx);
		qFromAxisAndAngle(q2, y_axis, ry);
		qFromAxisAndAngle(q3, z_axis, -rz);

		tmpQuatState = q1 * q2 * q3 * tmpQuatState;

		camState[3] = tmpQuatState.x();
		camState[4] = tmpQuatState.y();
		camState[5] = tmpQuatState.z();
		camState[6] = tmpQuatState.w();

		x_axis *= tx;
		y_axis *= ty;
		z_axis *= -tz;

		move.x() = x_axis.x() + y_axis.x() + z_axis.x(); // left / right
		move.y() = x_axis.y() + y_axis.y() + z_axis.y(); // forward / backward
		move.z() = x_axis.z() + y_axis.z() + z_axis.z(); // up / down

		camState[0] += move.x(); //x-axis
		camState[1] += move.y(); //y-axis
		camState[2] += move.z(); //z-axis

		camMutex.lock();
		//Jan Paul: Now writing data into the Envire2 tree using the spaceMouse_ member:
		//JP: As this will trigger a new edgeModified event which will also lock the camMutex, the camMutex has been changed to recursive mode to avoid deadlocks
		//std::cout << "Setting velocity state from ConnexionPlugin.\n";
		spaceMouse_.setVelocityState(move, (q1 * q2 * q3));
		//std::cout << "Setting pose state from ConnexionPlugin.\n";
		spaceMouse_.setPoseState(
				Vector( { camState[0], camState[1], camState[2] }),
				tmpQuatState);

		camMutex.unlock();
	}
}

void ConnexionPlugin::camReset(void) {
	camMutex.lock();
	resetCam = true;
	camMutex.unlock();

	// Local handling of camState variable that was global before: --------------------------------------------------------------
	/*
	 * state[0..2] -> trans: x,y,z
	 * state[3..6] -> rot: x,y,z,w (quaternion)
	 */
	mars::interfaces::sReal camState[7];
	// End of local handling of camState variable that was global before. --------------------------------------------------------------

	camState[0] = 0.0;
	camState[1] = 0.0;
	camState[2] = 2.5;
	camState[3] = 0.0;
	camState[4] = 0.0;
	camState[5] = 0.0;
	camState[6] = 1.0;

	//JP: As this will trigger a new edgeModified event which will also lock the camMutex, the camMutex has been changed to recursive mode to avoid deadlocks
	camMutex.lock();
	//std::cout << "Setting velocity state from ConnexionPlugin, camReset.\n";
	spaceMouse_.setVelocityState(mars::interaction::datatype::Velocity6D());
	//std::cout << "Setting pose state from ConnexionPlugin, camReset.\n";
	spaceMouse_.setPoseState(Vector(camState[0], camState[1], camState[2]),
			Quaternion(camState[6], camState[3], camState[4], camState[5]));
	resetCam = true;
	camMutex.unlock();
}

void ConnexionPlugin::qFromAxisAndAngle(Quaternion &q, Vector vec,
		sReal angle) {
	sReal l = vec.x() * vec.x() + vec.y() * vec.y() + vec.z() * vec.z();
	if (l > 0.0) {
		angle *= 0.5;
		q.w() = cos(angle);
		l = sin(angle) * sqrt(l);
		q.x() = vec.x() * l;
		q.y() = vec.y() * l;
		q.z() = vec.z() * l;
	} else {
		q.w() = 1;
		q.x() = 0;
		q.y() = 0;
		q.z() = 0;
	}
}

void ConnexionPlugin::hideWidget(void) {
	//if (myWidget) myWidget->close();
}

void ConnexionPlugin::closeWidget(void) {
	if (myWidget) {
		delete myWidget;
		//    control->gui->removeDockWidget((void*)myWidget);
		myWidget = NULL;
	}
}

void ConnexionPlugin::objectSelected(unsigned long id) {
	object_id = id;
	LOG_DEBUG("id: %lu", id);
	ConnexionPlugin::setSpaceMouseToObject();
	if (object_mode == 2) {
		ConnexionPlugin::setSpaceMouseToObject();
	}
}

void ConnexionPlugin::windowSelected(unsigned long id) {
	win_id = id;
	if (object_mode == 1) {
		ConnexionPlugin::setSpaceMouseToCamera();
	}
}

void ConnexionPlugin::setObjectMode(int mode) {
	object_mode = mode;
	if (object_mode == 1) {
		ConnexionPlugin::setSpaceMouseToCamera();
	} else {
		ConnexionPlugin::setSpaceMouseToObject();
	}
}

void ConnexionPlugin::setLockAxis(int axis, bool val) {
	if (axis > 0 && axis < 7)
		use_axis[axis - 1] = val;
}

void ConnexionPlugin::setSensitivity(int axis, double sens) {
	if (axis > 0 && axis < 7)
		sensitivity[axis - 1] = sens;
}

//void edgeAdded(const EdgeAddedEvent& e) {}
//void edgeRemoved(const EdgeRemovedEvent& e) {}
void ConnexionPlugin::edgeModified(const envire::core::EdgeModifiedEvent& e) {
	//std::cout << "edgeModified\n";
	if (e.target == spaceMouse_.frame_) {
		//std::cout << "___________________________SpaceMouseMoved\n";
		camMutex.lock();
		newValueReceived = true;
		camMutex.unlock();

		//Now we could extract the data from spaceMouse_.envireGraph_.getEdgeProperty(spaceMouse_.root_, spaceMouse_.frame_).transform,
		//however, as this is done in ConnexionPlugin::preGraphicsUpdate, there is no point in doing anything special here
	}
}
//void frameAdded(const FrameAddedEvent& e) {}
//void frameRemoved(const FrameRemovedEvent& e) {}
void ConnexionPlugin::itemAdded(const envire::core::ItemAddedEvent& e) {
	//std::cout << "itemAdded\n";
}
//void itemRemoved(const ItemRemovedEvent& e) {}

void ConnexionPlugin::setSpaceMouseToCamera() {
	//std::cout << "setSpaceMouseToCamera:\n";
	double data[7];

	interfaces::GraphicsWindowInterface *gw = control->graphics->get3DWindow(
			win_id);

	if (gw) {
		gw->getCameraInterface()->getViewportQuat(data, data + 1, data + 2,
				data + 3, data + 4, data + 5, data + 6);

		Vector trans;
		trans.x() = data[0];
		trans.y() = data[1];
		trans.z() = data[2];
		Quaternion qRot;
		qRot.x() = data[3];
		qRot.y() = data[4];
		qRot.z() = data[5];
		qRot.w() = data[6];

		//std::cout << "Setting velocity state from ConnexionPlugin.\n";
		//spaceMouse_.setVelocityState(move, (q1 * q2 * q3));
		//^The speed would have to be calculated from the new and last pose state, leaving that out for now (keeping the old velocity),
		// as moving the 2D mouse in between is also a special case that should be seldom and also be more elegantly solved by a synchronizer
		// in the general interaction interface that synchronizes 2d Mouse and space mouse inputs somehow.

		camMutex.lock();
		//std::cout << "Setting pose state from ConnexionPlugin.\n";
		spaceMouse_.setPoseState(trans, qRot);

		newValueReceived = false; //The above setXState commands triggered an event, but not due to real space mouse movement.
		//                        However, the newValueReceived value will be set to true by this event
		//                        (before these setXState Methods return, as they call the event subscribers directly in a last step).
		//                        So reset the newValueReceived variable so that this method "ConnexionPlugin::preGraphicsUpdate"
		//                        does not think that a real space mouse movement has been received, because changes to the space mouse state
		//                        here can only come from 2d mouse movements.
		camMutex.unlock();
		//std::cout << "setSpaceMouseToCamera done.\n";
	}
}
void ConnexionPlugin::setSpaceMouseToObject() {
	//std::cout << "setSpaceMouseToObject:\n";
	core_objects_exchange node;
	control->nodes->getNodeExchange(object_id, &node);
	Quaternion tmpQ(node.rot);
	Vector tmpV = node.pos;

	camMutex.lock();
	//std::cout << "Setting pose state from ConnexionPlugin.\n";
	spaceMouse_.setPoseState(tmpV, tmpQ);

	newValueReceived = false; //The above setXState commands triggered an event, but not due to real space mouse movement.
	//                        However, the newValueReceived value will be set to true by this event
	//                        (before these setXState Methods return, as they call the event subscribers directly in a last step).
	//                        So reset the newValueReceived variable so that this method "ConnexionPlugin::preGraphicsUpdate"
	//                        does not think that a real space mouse movement has been received, because changes to the space mouse state
	//                        here can only come from 2d mouse movements.
	camMutex.unlock();
	//std::cout << "setSpaceMouseToObject done.\n";
}

}					// end of namespace connexion_plugin
} // end of namesp:ace plugins
} // end of namespace mars

DESTROY_LIB(mars::plugins::connexion_plugin::ConnexionPlugin);
CREATE_LIB(mars::plugins::connexion_plugin::ConnexionPlugin);
