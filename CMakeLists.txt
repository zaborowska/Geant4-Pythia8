#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(HepMCEx02)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

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
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find HepMC (required package)
#
find_package(HepMC REQUIRED)

#----------------------------------------------------------------------------
# Find Pythia6 (required package)
#
find_package(Pythia6 QUIET)
if(PYTHIA6_FOUND)
  message(STATUS "G4 Examples: Pythia6 found. --> HepMCEx02 example with Pythia6 enabled.") 
  add_definitions(-DG4LIB_USE_PYTHIA) 
else()
  set(PYTHIA6_LIBRARIES "")  
endif()

#----------------------------------------------------------------------------
# Find Pythia8 (required package)
#
find_package(Pythia8 REQUIRED)
if(PYTHIA8_FOUND)
  message(STATUS "G4 Examples: Pythia8 found. --> HepMCEx02 example with Pythia8 enabled.") 
  add_definitions(-DG4LIB_USE_PYTHIA8) 
else()
  set(PYTHIA8_LIBRARY "")
  set(PYTHIA8_HEPMC_LIBRARY "")
  set(PYTHIA8_HAPDF_LIBRARY "")
endif()

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
                    ${HEPMC_INCLUDE_DIR}
                    ${PYTHIA8_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(HepMCEx02 HepMCEx02.cc ${sources} ${headers})
target_link_libraries(HepMCEx02 ${Geant4_LIBRARIES}
                      ${HEPMC_LIBRARIES} ${HEPMC_FIO_LIBRARIES}
                      ${PYTHIA6_LIBRARIES} ${PYTHIA8_LIBRARY}
                       ${PYTHIA8_HEPMC_LIBRARY} ${PYTHIA8_HAPDF_LIBRARY} gcc)

# if pythia is compiled with g77, link with -lg2c instead.
#target_link_libraries(HepMCEx02 ${Geant4_LIBRARIES}
#                      ${HEPMC_LIBRARIES} ${HEPMC_FIO_LIBRARIES}
#                      ${PYTHIA6_LIBRARIES} g2c)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build HepMCEx02. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(HepMCEx02_SCRIPTS
    hepmc_ascii_Pythia6.in hepmc_ascii_Pythia8.in
    hepmc_ascii.out hepmc_pygen.in hepmc_pygen.out vis.mac hepmc_pythia8.in
    data_Pythia8ToAscii/example_MyPythia8.dat
    data_Pythia6ToAscii/example_MyPythia.dat
  )

foreach(_script ${HepMCEx02_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS HepMCEx02 DESTINATION bin)

