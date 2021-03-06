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

#include "SimEntity.h"
#include <configmaps/ConfigData.h>
#include <iostream>
#include <mars/utils/mathUtils.h>
#include <mars/interfaces/NodeData.h>
#include <mars/interfaces/sim/ControlCenter.h>
#include <mars/interfaces/sim/SimulatorInterface.h>
#include <mars/interfaces/sim/NodeManagerInterface.h>
#include <mars/interfaces/sim/MotorManagerInterface.h>
#include <iterator> // ostream_iterator

namespace mars {
  using namespace interfaces;
  namespace sim {

    SimEntity::SimEntity(const std::string &name) : name(name), control(NULL),
                                                    selected(false) {
    }

    SimEntity::SimEntity(const configmaps::ConfigMap& parameters) : control(NULL),
                                                                    selected(false) {
      config = parameters;
      this->name = (std::string) config["name"];
    }

    SimEntity::SimEntity(ControlCenter *c,
                         const std::string &name) : name(name), control(c),
                                                    selected(false) {
    }

    SimEntity::SimEntity(ControlCenter *c,
                         const configmaps::ConfigMap& parameters) : control(c),
                                                                    selected(false) {
      config = parameters;
      this->name = (std::string) config["name"];
    }

    void SimEntity::appendConfig(const configmaps::ConfigMap& parameters) {
      configmaps::ConfigMap map = parameters;
      config.append(map);
    }

    void SimEntity::removeEntity() {
//        for (std::vector<NodeId>::iterator it = oldNodeIDs.begin();
//                it != oldNodeIDs.end(); ++it) {
//            control->nodes->removeNode(*it);
//        }
//        oldNodeIDs.clear();
    }

    void SimEntity::addNode(unsigned long nodeId, const std::string& name) {
      nodeIds[nodeId] = name;
    }

    void SimEntity::addMotor(unsigned long motorId, const std::string& name) {
      motorIds[motorId] = name;
    }

    void SimEntity::addController(long unsigned int controllerId) {
      controllerIds.push_back(controllerId);
    }

    void SimEntity::addJoint(long unsigned int jointId, const std::string& name) {
      jointIds[jointId] = name;
    }

    void SimEntity::addSensor(long unsigned int sensorId, const std::string& name) {
      sensorIds[sensorId] = name;
    }

    bool SimEntity::select(unsigned long nodeId) {
      //check if the node belongs to the robot
      //   std::map<unsigned long, std::string>::iterator it = nodeIds.find(nodeId);
      //node belongs to the robot
      if (nodeIds.count(nodeId)) {
        //no need to check if it has been previously selected as std::set does that
        selectedNodes.insert(nodeId);
        return true;
      } else {
        return false;
      }
    }

    long unsigned int SimEntity::getNode(const std::string& name) {
      for (std::map<unsigned long, std::string>::const_iterator iter = nodeIds.begin();
          iter != nodeIds.end(); ++iter) {
        if (iter->second == name)
          return iter->first;
      }
      return 0;
    }

    std::string SimEntity::getNode(long unsigned int id) {
      //TODO problem if node does not exist
      return nodeIds.find(id)->second;
    }

    long unsigned int SimEntity::getMotor(const std::string& name) {
      for (std::map<unsigned long, std::string>::const_iterator iter = motorIds.begin();
          iter != motorIds.end(); ++iter) {
        if (iter->second == name)
          return iter->first;
      }
      return 0;
    }

    std::string SimEntity::getMotor(long unsigned int id) {
      //TODO problem if node does not exist
      return motorIds.find(id)->second;
    }

    long unsigned int SimEntity::getJoint(const std::string& name) {
      for (std::map<unsigned long, std::string>::const_iterator iter = jointIds.begin();
          iter != jointIds.end(); ++iter) {
        if (iter->second == name)
          return iter->first;
      }
      return 0;
    }

    std::string SimEntity::getJoint(long unsigned int id) {
      //TODO problem if node does not exist
      return jointIds.find(id)->second;
    }

    std::vector<unsigned long> SimEntity::getControllerList() {
      return controllerIds;
    }

    void SimEntity::printNodes() {
      std::cout << "Nodes of Robot " << name << "with id: " << ":\n";
      for (std::map<unsigned long, std::string>::const_iterator iter = nodeIds.begin();
          iter != nodeIds.end(); ++iter) {
        std::cout << iter->first << '\t' << iter->second << '\n';
      }
      std::cout << std::endl;
    }

    void SimEntity::printMotors() {
      std::cout << "Motors of Robot " << name << ":\n";
      for (std::map<unsigned long, std::string>::const_iterator iter = motorIds.begin();
          iter != motorIds.end(); ++iter) {
        std::cout << iter->first << '\t' << iter->second << '\n';
      }
      std::cout << std::endl;
    }

    void SimEntity::printControllers() {
      std::cout << "Controllers of Robot " << name << ":\n";
      for (size_t i = 0; i < controllerIds.size(); i++) {
        std::cout << controllerIds.at(i) << std::endl;
      }
    }

    void SimEntity::setInitialPose() {
      bool worldAnchor = false;
      if(!control) return;
      if(config.find("rootNode") != config.end()) {
        if(config.find("anchor") != config.end()) {
          if((std::string)config["anchor"] == "world") {
            worldAnchor = true;
          }
        }
        NodeId id = getNode((std::string)config["rootNode"]);
        NodeData myNode = control->nodes->getFullNode(id);
        utils::Quaternion tmpQ(1, 0, 0, 0);
        utils::Vector tmpV;
        if(config.find("position") != config.end()) {
          myNode.pos.x() = config["position"][0];
          myNode.pos.y() = config["position"][1];
          myNode.pos.z() = config["position"][2];
          control->nodes->editNode(&myNode, EDIT_NODE_POS | EDIT_NODE_MOVE_ALL);
        }
        if(config.find("rotation") != config.end()) {
          // check if euler angles or quaternion is provided; rotate around z
          // if only one angle is provided
          switch (config["rotation"].size()) {
          case 1: tmpV[0] = 0;
            tmpV[1] = 0;
            tmpV[2] = config["rotation"][0];
            tmpQ = utils::eulerToQuaternion(tmpV);
            break;
          case 3: tmpV[0] = config["rotation"][0];
            tmpV[1] = config["rotation"][1];
            tmpV[2] = config["rotation"][2];
            tmpQ = utils::eulerToQuaternion(tmpV);
            break;
          case 4: tmpQ.x() = (sReal)config["rotation"][1];
            tmpQ.y() = (sReal)config["rotation"][2];
            tmpQ.z() = (sReal)config["rotation"][3];
            tmpQ.w() = (sReal)config["rotation"][0];
            break;
          }
          myNode.rot = tmpQ;
          control->nodes->editNode(&myNode, EDIT_NODE_ROT | EDIT_NODE_MOVE_ALL);
        }
        if(worldAnchor) {
          control->sim->connectNodes(id, 0);
        }
        // set Joints
        configmaps::ConfigVector::iterator it;
        configmaps::ConfigMap::iterator joint_it;
        for (it = config["poses"].begin(); it!= config["poses"].end(); ++it) {
          if ((std::string)(*it)["name"] == (std::string)config["pose"]) {
            for (joint_it = (*it)["joints"][0].children.begin();
                 joint_it!= (*it)["joints"][0].children.end(); ++joint_it) {
              //fprintf(stderr, "setMotorValue: joint: %s, id: %lu, value: %f\n", ((std::string)joint_it->first).c_str(), motorIDMap[joint_it->first], (double)joint_it->second);
              control->motors->setMotorValue(getMotor(joint_it->first),
                                             joint_it->second);
            }
          }
        }
      }
    }

  } // end of namespace sim
} // end of namespace mars
