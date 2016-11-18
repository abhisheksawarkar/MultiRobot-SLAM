# Install script for directory: /home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff

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
   "/usr/local/lib/libg2o_stuff.a")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/lib/libg2o_stuff.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg2o_opengl_helper.a")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/lib/libg2o_opengl_helper.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/g2o/stuff/timeutil.h;/usr/local/include/g2o/stuff/color_macros.h;/usr/local/include/g2o/stuff/opengl_wrapper.h;/usr/local/include/g2o/stuff/opengl_primitives.h;/usr/local/include/g2o/stuff/macros.h;/usr/local/include/g2o/stuff/string_tools.h;/usr/local/include/g2o/stuff/tictoc.h;/usr/local/include/g2o/stuff/sparse_helper.h;/usr/local/include/g2o/stuff/misc.h;/usr/local/include/g2o/stuff/sampler.h;/usr/local/include/g2o/stuff/scoped_pointer.h;/usr/local/include/g2o/stuff/command_args.h;/usr/local/include/g2o/stuff/property.h;/usr/local/include/g2o/stuff/filesys_tools.h;/usr/local/include/g2o/stuff/unscented.h;/usr/local/include/g2o/stuff/os_specific.h;/usr/local/include/g2o/stuff/g2o_stuff_api.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/include/g2o/stuff" TYPE FILE FILES
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/timeutil.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/color_macros.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/opengl_wrapper.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/opengl_primitives.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/macros.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/string_tools.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/tictoc.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/sparse_helper.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/misc.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/sampler.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/scoped_pointer.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/command_args.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/property.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/filesys_tools.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/unscented.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/os_specific.h"
    "/home/abhishek/iiit/project_final_cpp/cair_final/cair_online/g2o/stuff/g2o_stuff_api.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

