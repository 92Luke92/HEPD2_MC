#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.1...3.15)
project(HEPD2_MC
        VERSION 0.2
        DESCRIPTION "HEPD2 Geant 4 Monte Carlo simulation"
        LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

# Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

# Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)
  
endif()
    
#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

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





#----------------------------------------------------------------------------
# HEPDSW library
option(STATIC_BUILD "Build HEPDSW static library" ON)
STRING(TOUPPER ${STATIC_BUILD} staticbuild)
STRING(COMPARE EQUAL ${staticbuild} "ON" test_res)
if (test_res)
    add_library(hepdsw_lib STATIC ${sources} ${headers})

else()
    add_library(hepdsw_lib SHARED ${sources} ${headers})

endif()
set_target_properties(hepdsw_lib PROPERTIES OUTPUT_NAME "hepdsw")
target_link_libraries(hepdsw_lib  ${Geant4_LIBRARIES} )

#dd the dictionary to the list of source files
set(sources ${sources} ${DataFormats_DICTIONARY})

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(HEPD2_MC HEPD2_MC.cc ${sources} ${headers})
target_link_libraries(HEPD2_MC ${Geant4_LIBRARIES} )

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
