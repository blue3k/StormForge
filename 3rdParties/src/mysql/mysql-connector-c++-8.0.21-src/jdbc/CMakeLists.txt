# Copyright (c) 2008, 2019, Oracle and/or its affiliates. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 2.0, as
# published by the Free Software Foundation.
#
# This program is also distributed with certain software (including
# but not limited to OpenSSL) that is licensed under separate terms,
# as designated in a particular file or component or in included license
# documentation.  The authors of MySQL hereby grant you an
# additional permission to link the program and your derivative works
# with the separately licensed software that they have included with
# MySQL.
#
# Without limiting anything contained in the foregoing, this file,
# which is part of MySQL Connector/C++, is also subject to the
# Universal FOSS Exception, version 1.0, a copy of which can be found at
# http://oss.oracle.com/licenses/universal-foss-exception.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License, version 2.0, for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA


PROJECT(MYSQLCPPCONN)
cmake_minimum_required(VERSION 3.1)

if(POLICY CMP0003)
  cmake_policy(SET CMP0003 NEW)
endif()

if(POLICY CMP0007)
  cmake_policy(SET CMP0007 NEW)
endif()

if(POLICY CMP0015)
  cmake_policy(SET CMP0015 NEW)
endif()

if(POLICY CMP0028)
  cmake_policy(SET CMP0028 NEW)
endif()

#-----------------

include(cmake/setup.cmake)

# Prefer cmake code from parent project, if present
include(../cmake/setup.cmake OPTIONAL)

include(platform)
include(config_options)


#
# Detect if we are configured as stand-alone project, or sub-project.
#

IF (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  MESSAGE("Stand-alone configuration")
  MESSAGE("Building on system: ${CMAKE_SYSTEM}")
  SET(jdbc_stand_alone 1)
ELSE()
  SET(jdbc_stand_alone 0)
  INCLUDE(SubProject.cmake OPTIONAL)
ENDIF()

#-----------------

if(jdbc_stand_alone)

  add_config_option(BUILD_STATIC BOOL DEFAULT OFF
    "Build static connector library instead of dynamic one"
  )

  add_config_option(BUNDLE_DEPENDENCIES BOOL ADVANCED DEFAULT OFF
    "copy dependencies to install location"
  )

endif(jdbc_stand_alone)



add_config_option(MYSQLCLIENT_STATIC_LINKING BOOL ADVANCED DEFAULT ON "enable libmysqlclient static linking")
add_config_option(MYSQLCLIENT_STATIC_BINDING BOOL ADVANCED DEFAULT ON "enable libmysqlclient static binding")



if(BUILD_STATIC)
  set(BUILD_SHARED_LIBS OFF)
else()
  set(BUILD_SHARED_LIBS ON)
endif()

set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS} CACHE INTERNAL "")


#-----------------
#  Version info
#

if(jdbc_stand_alone)

  message(WARNING "Using fake version info for legacy Connector/C++")

  set(CONCPP_VERSION_MAJOR 8)
  set(CONCPP_VERSION_MINOR 0)
  set(CONCPP_VERSION_MICRO 0)
  set(CONCPP_VERSION_LEVEL "")
  set(JDBC_ABI_VERSION_MAJOR 7)

endif(jdbc_stand_alone)

configure_file(
  "VersionInfo.cmake.in"
  "${PROJECT_BINARY_DIR}/VersionInfo.cmake"
  @ONLY
)

INCLUDE("${PROJECT_BINARY_DIR}/VersionInfo.cmake")

#message("Con/C++ version: ${CONNECTOR_VERSION}")
message("Legacy library soversion: ${MYSQLCPPCONN_SOVERSION}")

include(./install_layout.cmake)

#-----------------
#  Dependencies
#

include(dependency)

if(MYSQLCLIENT_STATIC_LINKING)
  # Arrange for MySQL::client to refer to the static library
  set(MYSQL_LIB_STATIC ON)
else()
  # Arrange for MySQL::client to refer to the dynamic library
  set(MYSQL_LIB_STATIC OFF)
endif()


find_dependency(MySQL)
find_dependency(Boost)


#-----------------
# Global build flags


if(NOT DEFINED CMAKE_CXX_FLAGS)
  enable_pic()
  set_visibility(hidden)
endif()

enable_cxx11()


#-----------------
# Warnings
#

if(MSVC)

  add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)

elseif(SUNPRO)

  add_compile_options(
    -errtags=yes  # show tags that can be used to disable warnings
  )

endif()

#
#  TODO: We should fix the warnings below and then also increase warning
#  level and fix remaining warnings. However, before this is done, we do
#  not show the warnings to not break our release builds which are done
#  in maintainer mode.
#

set(SHOW_JDBC_WARNINGS OFF CACHE BOOL "Show compile warnings for legacy code")
mark_as_advanced(SHOW_JDBC_WARNINGS)

if(NOT SHOW_JDBC_WARNINGS)
  if(MSVC)

    add_compile_options(
      /wd4101  # unreferenced local variable
      /wd4267  # conversion ... possible loss of data
      /wd4800  # forcing value to bool
      /wd4594  # class ... can never be instantiated - indirect virtual base class is inaccesible

      /wd4100  # unreferenced formal parameter
      /wd4458  # declaration hides class member
      /wd4244  # conversion ... possible loss of data
      /wd4245  # conversion ... signed/unsigned missmatch
      /wd4706  # assignment within conditional expression
    )

  elseif(SUNPRO)

    add_compile_options(
      -erroff=wvarhidemem
    )

  else()

    add_compile_options(
      -Wno-unused-parameter
      -Wno-deprecated-declarations
    )

  endif()

endif()

############################################################################
#
#  Main components and connector library target.
#

ADD_SUBDIRECTORY(cppconn)
ADD_SUBDIRECTORY(driver)

#
# Connector library target
#

include(libutils)


# TODO: INFO file

set(INFO "${PROJECT_BINARY_DIR}/INFO_BIN")
file(WRITE "${INFO}" "Connector/C++ build information.\n\n")
set(INFO_PREFIX "jdbc-")

merge_libraries(connector-jdbc jdbc)
target_link_libraries(connector-jdbc PUBLIC Boost::boost)

#
# Embed rpath information in the connector library.
#

set_property(TARGET connector-jdbc PROPERTY BUILD_WITH_INSTALL_RPATH ON)

# The $ORIGIN/@loader_path entry tells to look for dependent libraries in the
# location where our connector library is stored.

if(APPLE)
  set_property(TARGET connector-jdbc APPEND PROPERTY INSTALL_RPATH "@loader_path")
elseif(NOT WIN32)
  set_property(TARGET connector-jdbc APPEND PROPERTY INSTALL_RPATH "$ORIGIN")
endif()


#
# Install specifications
# ----------------------
#
# Note: Locations and names are configured in install_layout.cmake
#

set_property(TARGET connector-jdbc PROPERTY OUTPUT_NAME ${LIB_NAME})
message("Connector legacy library name: ${LIB_NAME}")

if(NOT BUILD_STATIC)
  set_property(TARGET connector-jdbc PROPERTY ARCHIVE_OUTPUT_NAME ${LIB_NAME_BASE})
endif()


set_target_properties(connector-jdbc
  PROPERTIES
  SOVERSION "${MYSQLCPPCONN_SOVERSION}"
  VERSION   "${MYSQLCPPCONN_SOVERSION}.${CONNECTOR_NUMERIC_VERSION}"
)


install(TARGETS connector-jdbc
  CONFIGURATIONS Release RelWithDebInfo
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR_STATIC}" COMPONENT JDBCDev
  RUNTIME DESTINATION "${INSTALL_LIB_DIR}" COMPONENT JDBCDll
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT JDBCDll
)

install(TARGETS connector-jdbc
  CONFIGURATIONS Debug
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR_STATIC}/debug" COMPONENT JDBCDev
  RUNTIME DESTINATION "${INSTALL_LIB_DIR}/debug" COMPONENT JDBCDll
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}/debug" COMPONENT JDBCDll
)


if(MSVC AND NOT BUILD_STATIC)

  install(FILES $<TARGET_PDB_FILE:connector-jdbc>
    CONFIGURATIONS RelWithDebInfo
    DESTINATION "${INSTALL_LIB_DIR}"
    COMPONENT Debuginfo
  )

  install(FILES $<TARGET_PDB_FILE:connector-jdbc>
    CONFIGURATIONS Debug
    DESTINATION "${INSTALL_LIB_DIR}/debug"
    COMPONENT Debuginfo
  )

endif()

# Install some MySQL specific headers
SET(MYSQLCPPCONN_SPECIFIC_INSTALL_HEADERS
  driver/mysql_connection.h
  driver/mysql_driver.h
  driver/mysql_error.h)

INSTALL(FILES ${MYSQLCPPCONN_SPECIFIC_INSTALL_HEADERS}
  DESTINATION "${INSTALL_INCLUDE_DIR}"
  COMPONENT JDBCDev
)

# Note: Copy to build location so that test code can use headers without
# installing them first.

file(COPY ${MYSQLCPPCONN_SPECIFIC_INSTALL_HEADERS}
  DESTINATION "${PROJECT_BINARY_DIR}/include/jdbc"
)

#  export(TARGETS mysqlcppconn
#    APPEND FILE "${PROJECT_BINARY_DIR}/exports.cmake"
#  )

#
#  Add command to show rpath information
#

if(0)

if(APPLE)
  set(list_rpath_cmd otool -l $<TARGET_FILE:connector-jdbc> "|" grep RPATH -A2 "||" true)
elseif(NOT WIN32)
  set(list_rpath_cmd objdump -x $<TARGET_FILE:connector-jdbc> "|" grep RPATH -A2 "||" true)
endif()

add_custom_command(TARGET connector-jdbc POST_BUILD
  COMMAND ${list_rpath_cmd}
  COMMENT "RPATH setting for: $<TARGET_FILE_NAME:connector-jdbc>"
)

endif()


# -----------------------
# Look at libraries required by client lib that are bundled with MySQL.
# We bundle them with the connector as well.
#

if(BUNDLE_DEPENDENCIES)

message("looking for bundled client lib deps: ${MYSQL_EXTERNAL_DEPENDENCIES}")

if(MYSQL_EXTERNAL_DEPENDENCIES)

  foreach(lib ${MYSQL_EXTERNAL_DEPENDENCIES})

    #message("-- looking for: ${MYSQL_LIB_DIR}/*${lib}*${CMAKE_SHARED_LIBRARY_SUFFIX}*")
    file(GLOB _bundled1 "${MYSQL_LIB_DIR}/private/*${CMAKE_SHARED_LIBRARY_PREFIX}${lib}${CMAKE_SHARED_LIBRARY_SUFFIX}*")
    file(GLOB _bundled2 "${MYSQL_LIB_DIR}/*${CMAKE_SHARED_LIBRARY_PREFIX}${lib}${CMAKE_SHARED_LIBRARY_SUFFIX}*")

    if(_bundled1 OR _bundled2)

      message("found bundled libs: ${_bundled1} ${_bundled2}")

      install(FILES ${_bundled1} ${_bundled2}
        DESTINATION "${INSTALL_LIB_DIR}"
        COMPONENT JDBCDll
      )

    endif()

  endforeach()

else()

  #
  # If detection of external MySQL library dependencies did not work for
  # some reason, copy known dependencies if they are bundled with
  # MySQL. This list would need to be updated if new required dependencies
  # appear.
  #

  file(GLOB _bundled "${MYSQL_DIR}/lib/*${CMAKE_SHARED_LIBRARY_SUFFIX}*")

  foreach(lib ${_bundled})
    if(lib MATCHES "eay|ssl|crypto")

      message("found bundled libs: ${lib}")

      install(FILES "${lib}"
        DESTINATION "${INSTALL_LIB_DIR}"
        COMPONENT JDBCDll
      )

    endif()
  endforeach()

endif()

endif(BUNDLE_DEPENDENCIES)

add_config_option(WITH_JDBC_TESTS BOOL DEFAULT OFF
  "Build JDBC Unit tests"
)


if(jdbc_stand_alone)
  show_config_options()
endif()
