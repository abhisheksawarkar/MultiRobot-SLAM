# Install script for directory: /home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg2o_types_slam2d.a")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/lib/libg2o_types_slam2d.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/g2o/types/slam2d/types_slam2d.h;/usr/local/include/g2o/types/slam2d/edge_se2_pointxy_calib.h;/usr/local/include/g2o/types/slam2d/edge_se2_prior.h;/usr/local/include/g2o/types/slam2d/se2.h;/usr/local/include/g2o/types/slam2d/g2o_types_slam2d_api.h;/usr/local/include/g2o/types/slam2d/edge_se2_lotsofxy.h;/usr/local/include/g2o/types/slam2d/edge_se2_xyprior.h;/usr/local/include/g2o/types/slam2d/parameter_se2_offset.h;/usr/local/include/g2o/types/slam2d/edge_se2_pointxy.h;/usr/local/include/g2o/types/slam2d/edge_se2_offset.h;/usr/local/include/g2o/types/slam2d/edge_pointxy.h;/usr/local/include/g2o/types/slam2d/vertex_se2.h;/usr/local/include/g2o/types/slam2d/edge_se2.h;/usr/local/include/g2o/types/slam2d/edge_se2_pointxy_bearing.h;/usr/local/include/g2o/types/slam2d/edge_se2_twopointsxy.h;/usr/local/include/g2o/types/slam2d/vertex_point_xy.h;/usr/local/include/g2o/types/slam2d/edge_se2_pointxy_offset.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/include/g2o/types/slam2d" TYPE FILE FILES
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/types_slam2d.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_pointxy_calib.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_prior.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/se2.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/g2o_types_slam2d_api.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_lotsofxy.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_xyprior.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/parameter_se2_offset.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_pointxy.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_offset.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_pointxy.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/vertex_se2.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_pointxy_bearing.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_twopointsxy.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/vertex_point_xy.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/types/slam2d/edge_se2_pointxy_offset.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

