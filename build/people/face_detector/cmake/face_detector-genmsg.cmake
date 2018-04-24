# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "face_detector: 7 messages, 0 services")

set(MSG_I_FLAGS "-Iface_detector:/home/trobot/robot_ws/devel/share/face_detector/msg;-Iactionlib_msgs:/opt/ros/indigo/share/actionlib_msgs/cmake/../msg;-Ipeople_msgs:/home/trobot/robot_ws/src/people/people_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(face_detector_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg" NAME_WE)
add_custom_target(_face_detector_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "face_detector" "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg" ""
)

get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorAction.msg" NAME_WE)
add_custom_target(_face_detector_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "face_detector" "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorAction.msg" "geometry_msgs/Point:face_detector/FaceDetectorFeedback:face_detector/FaceDetectorGoal:actionlib_msgs/GoalID:face_detector/FaceDetectorActionGoal:face_detector/FaceDetectorActionFeedback:face_detector/FaceDetectorActionResult:std_msgs/Header:people_msgs/PositionMeasurement:actionlib_msgs/GoalStatus:face_detector/FaceDetectorResult"
)

get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg" NAME_WE)
add_custom_target(_face_detector_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "face_detector" "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg" "geometry_msgs/Point:actionlib_msgs/GoalStatus:actionlib_msgs/GoalID:std_msgs/Header:people_msgs/PositionMeasurement:face_detector/FaceDetectorResult"
)

get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg" NAME_WE)
add_custom_target(_face_detector_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "face_detector" "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg" "actionlib_msgs/GoalStatus:actionlib_msgs/GoalID:std_msgs/Header:face_detector/FaceDetectorFeedback"
)

get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg" NAME_WE)
add_custom_target(_face_detector_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "face_detector" "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg" ""
)

get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg" NAME_WE)
add_custom_target(_face_detector_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "face_detector" "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg" "face_detector/FaceDetectorGoal:actionlib_msgs/GoalID:std_msgs/Header"
)

get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg" NAME_WE)
add_custom_target(_face_detector_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "face_detector" "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg" "std_msgs/Header:people_msgs/PositionMeasurement:geometry_msgs/Point"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorAction.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
)
_generate_msg_cpp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
)
_generate_msg_cpp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
)
_generate_msg_cpp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
)
_generate_msg_cpp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
)
_generate_msg_cpp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
)
_generate_msg_cpp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
)

### Generating Services

### Generating Module File
_generate_module_cpp(face_detector
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(face_detector_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(face_detector_generate_messages face_detector_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_cpp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorAction.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_cpp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_cpp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_cpp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_cpp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_cpp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_cpp _face_detector_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(face_detector_gencpp)
add_dependencies(face_detector_gencpp face_detector_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS face_detector_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorAction.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
)
_generate_msg_lisp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
)
_generate_msg_lisp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
)
_generate_msg_lisp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
)
_generate_msg_lisp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
)
_generate_msg_lisp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
)
_generate_msg_lisp(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
)

### Generating Services

### Generating Module File
_generate_module_lisp(face_detector
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(face_detector_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(face_detector_generate_messages face_detector_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_lisp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorAction.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_lisp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_lisp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_lisp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_lisp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_lisp _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_lisp _face_detector_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(face_detector_genlisp)
add_dependencies(face_detector_genlisp face_detector_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS face_detector_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorAction.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
)
_generate_msg_py(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
)
_generate_msg_py(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
)
_generate_msg_py(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
)
_generate_msg_py(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
)
_generate_msg_py(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg;/opt/ros/indigo/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
)
_generate_msg_py(face_detector
  "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/trobot/robot_ws/src/people/people_msgs/msg/PositionMeasurement.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
)

### Generating Services

### Generating Module File
_generate_module_py(face_detector
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(face_detector_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(face_detector_generate_messages face_detector_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorGoal.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_py _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorAction.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_py _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionResult.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_py _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionFeedback.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_py _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorFeedback.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_py _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorActionGoal.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_py _face_detector_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/trobot/robot_ws/devel/share/face_detector/msg/FaceDetectorResult.msg" NAME_WE)
add_dependencies(face_detector_generate_messages_py _face_detector_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(face_detector_genpy)
add_dependencies(face_detector_genpy face_detector_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS face_detector_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/face_detector
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(face_detector_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()
if(TARGET people_msgs_generate_messages_cpp)
  add_dependencies(face_detector_generate_messages_cpp people_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/face_detector
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(face_detector_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()
if(TARGET people_msgs_generate_messages_lisp)
  add_dependencies(face_detector_generate_messages_lisp people_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/face_detector
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(face_detector_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
if(TARGET people_msgs_generate_messages_py)
  add_dependencies(face_detector_generate_messages_py people_msgs_generate_messages_py)
endif()
