cmake_minimum_required(VERSION 3.15...3.27)
project(pysonycrsdk) # Replace 'my_project' with the name of your project

if(NOT SKBUILD)
    message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build'. Running
  it directly will almost certainly not produce the desired result. If
  you are a user trying to install this package, please use the command
  below, which will install all necessary build dependencies, compile
  the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to re-run the above
  after editing C++ files.")
endif()

if(CMAKE_VERSION VERSION_LESS 3.18)
    set(DEV_MODULE Development)
else()
    set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.9 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Detect the installed nanobind package and import it into CMake
execute_process(
    COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)

find_package(nanobind CONFIG REQUIRED)

# Link CRSDK library
set(cr_ldir ${CMAKE_CURRENT_SOURCE_DIR}/Sony_Camera_Remote/linux_${CMAKE_HOST_SYSTEM_PROCESSOR}/crsdk)
find_library(camera_remote Cr_Core HINTS ${cr_ldir})
add_library(sonycrsdk_lib SHARED IMPORTED)
set_target_properties(sonycrsdk_lib PROPERTIES
    IMPORTED_LOCATION ${camera_remote}
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/Sony_Camera_Remote/include/CRSDK/
)


nanobind_add_module(
    sonycrsdk_ext

    STABLE_ABI

    src/sonycrsdk_ext.cpp
    src/camera_info.cpp
)

target_include_directories(sonycrsdk_ext
    PUBLIC
    sonycrsdk_lib
)

target_link_libraries(sonycrsdk_ext
    PRIVATE
    sonycrsdk_lib
)

set_property(TARGET sonycrsdk_ext APPEND PROPERTY BUILD_RPATH "$<TARGET_FILE_DIR:sonycrsdk_lib>")

install(TARGETS sonycrsdk_ext LIBRARY DESTINATION sonycrsdk)
