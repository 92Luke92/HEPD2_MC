#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(HEPD2_MC)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# - Prepend local CMake Modules to the search path

set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake/Modules
    ${CMAKE_MODULE_PATH})

  set(CMAKE_CXX_FLAGS_INIT "-Wno-unused-variable")
  set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wno-unused-variable")
  set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2 -Wno-unused-variable")
  set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT "-Os -DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")



#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


#------ Include ROOT

include(FindROOT)
if(ROOT_FOUND)
        MESSAGE( STATUS "HEPDSW will be compiled with ROOT.")
	set(VGM_INCLUDE "${PROJECT_SOURCE_DIR}/../VGM/include")
        include_directories(${ROOT_INCLUDE_DIR} ${VGM_INCLUDE} )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_ANALYSIS_ROOT -Wno-unused-variable")
        set(EXTRA_LIBRARIES "${EXTRA_LIBRARIES} ${ROOT_LIBRARIES} -lGeom")
        set (HEPDSW_BUILTWITH_ROOT "yes")
else()
        MESSAGE(FATAL_ERROR "ROOT installation not found!Installation interrupted!")
endif()

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# HEPDSW library
option(STATIC_BUILD "Build HEPDSW static library" ON)
STRING(TOUPPER ${STATIC_BUILD} staticbuild)
STRING(COMPARE EQUAL ${staticbuild} "ON" test_res)
set(ROOT_LIBRARIES "${ROOT_LIBRARIES} -lGeom  -L${PROJECT_SOURCE_DIR}/../VGM/lib/ -lClhepVGM -lBaseVGM -lGeant4GM -lRootGM -lXmlVGM")
if (test_res)
    add_library(hepdsw_lib STATIC ${sources} ${headers})

else()
    add_library(hepdsw_lib SHARED ${sources} ${headers})

endif()
set_target_properties(hepdsw_lib PROPERTIES OUTPUT_NAME "hepdsw")
target_link_libraries(hepdsw_lib  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#dd the dictionary to the list of source files
set(sources ${sources} ${DataFormats_DICTIONARY})

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(HEPD2_MC HEPD2_MC.cc ${sources} ${headers})
target_link_libraries(HEPD2_MC ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build HEPD2_MC. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(SCRIPTS
  icons.mac
  gui.mac
  run.png
  init_vis.mac
  run1.mac
  run2.mac
  vis.mac
  HEPD2MC.mac
  )

foreach(_script ${SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS HEPD2_MC DESTINATION bin)
