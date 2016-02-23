project(mars_interfaces)
set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "This library is the base library for the MARS project and includes the general defines, structs and classes.")
cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=c++0x")
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

include(FindPkgConfig)

find_package(lib_manager)
lib_defaults()
define_module_info()

#This adds base-lib to the package-config as dep.
set(LIB_DEPS "base-lib")

pkg_check_modules(PKGCONFIG REQUIRED
        envire_core
        configmaps
        data_broker
        mars_utils
)
include_directories(${PKGCONFIG_INCLUDE_DIRS})
link_directories(${PKGCONFIG_LIBRARY_DIRS})
add_definitions(${PKGCONFIG_CLFAGS_OTHER})  #flags excluding the ones with -I

include_directories(src)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIRS})

set(HEADERS
    src/Logging.hpp
    src/cameraStruct.h
    src/contact_params.h
    src/ControllerData.h
    src/core_objects_exchange.h
    src/GraphicData.h
    src/JointData.h
    src/LightData.h
    src/MARSDefs.h
    src/MaterialData.h
    src/MotorData.h
    src/nodeState.h
    src/NodeData.h
    src/sensor_bases.h
    src/sim_common.h
    src/snmesh.h
    src/terrainStruct.h
    src/utils.h

    src/exceptions/SceneParseException.h
    
    src/InteractionStates/Analog.h
    src/InteractionStates/Arm.h
    src/InteractionStates/BaseType.h
    src/InteractionStates/Finger.h
    src/InteractionStates/ForceTorque.h    
    src/InteractionStates/FullBody.h
    src/InteractionStates/Hand.h
    src/InteractionStates/Head.h
    src/InteractionStates/Leg.h
    src/InteractionStates/Pose.h
    src/InteractionStates/Quaternion.h
    src/InteractionStates/Vec3.h
    src/InteractionStates/Velocity6D.h    
    
    src/InteractionStates/BaseState.h
    src/InteractionStates/SpaceMouse.h
    src/InteractionStates/BaseStateEventDispatcher.h
)

set(SOURCES 
    src/sim/ControlCenter.cpp
    src/sim/LoadCenter.cpp
    src/MaterialData.cpp
    src/NodeData.cpp
    src/JointData.cpp
    src/MotorData.cpp
    src/LightData.cpp
    src/GraphicData.cpp
    src/ControllerData.cpp
    src/utils.cpp
    
    src/InteractionStates/Analog.cpp
    src/InteractionStates/Arm.cpp
    src/InteractionStates/BaseType.cpp
    src/InteractionStates/Finger.cpp
    src/InteractionStates/ForceTorque.cpp    
    src/InteractionStates/FullBody.cpp
    src/InteractionStates/Hand.cpp
    src/InteractionStates/Head.cpp
    src/InteractionStates/Leg.cpp
    src/InteractionStates/Pose.cpp
    src/InteractionStates/Quaternion.cpp
    src/InteractionStates/Vec3.cpp
    src/InteractionStates/Velocity6D.cpp
    
    src/InteractionStates/BaseState.cpp
    src/InteractionStates/SpaceMouse.cpp
    src/InteractionStates/BaseStateEventDispatcher.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(
        ${PROJECT_NAME}
        ${PKGCONFIG_LIBRARIES}
)


if(WIN32)
  set(LIB_INSTALL_DIR bin) # .dll are in PATH, like executables
else(WIN32)
  set(LIB_INSTALL_DIR lib)
endif(WIN32)

set(_INSTALL_DESTINATIONS
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION ${LIB_INSTALL_DIR}
	ARCHIVE DESTINATION lib
)

# Install the library
install(TARGETS ${PROJECT_NAME} ${_INSTALL_DESTINATIONS})

# Install headers into mars include directory
install(FILES ${HEADERS} DESTINATION include/mars/interfaces)

FILE(GLOB files "src/graphics/*.h")
install(FILES ${files} DESTINATION include/mars/interfaces/graphics)
FILE(GLOB files "src/sim/*.h")
install(FILES ${files} DESTINATION include/mars/interfaces/sim)
FILE(GLOB files "src/gui/*.h")
install(FILES ${files} DESTINATION include/mars/interfaces/gui)
FILE(GLOB files "src/InteractionStates/*.h")
install(FILES ${files} DESTINATION include/mars/interfaces/InteractionStates)

# Prepare and install necessary files to support finding of the library 
# using pkg-config
configure_file(${PROJECT_NAME}.pc.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)
