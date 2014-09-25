#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(main42)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find HepMC (required package)
#
find_package(HepMC QUIET)
if(NOT HEPMC_FOUND)
  message(STATUS "G4 Examples: HepMC package not found. --> example_MyPythia example disabled")  
  return()
endif()

#----------------------------------------------------------------------------
# Find Pythia8 (required package)
#
#find_package(Pythia8 QUIET)
#==============================================================================
# Locate Pythia8 library
# in a directory defined via PYTHIA8 environment variable
#
# Defines:
#  PYTHIA8_FOUND
#  PYTHIA8_LIBRARIES

find_path(PYTHIA8_INCLUDE_DIR Pythia8/Pythia.h Pythia8/Pythia8ToHepMC.h
          HINTS $ENV{PYTHIA8LOCATION}/include ${PYTHIA8LOCATION}/include
          $ENV{PYTHIA8}/include ${PYTHIA8}/include)

# message(STATUS PYTHIA8_INCLUDE_DIR ${PYTHIA8_INCLUDE_DIR} )

find_library(PYTHIA8_LIBRARY NAMES pythia8
			     HINTS $ENV{PYTHIA8LOCATION}/lib ${PYTHIA8LOCATION}/lib
			     HINTS $ENV{PYTHIA8}/lib ${PYTHIA8}/lib)

# message(STATUS PYTHIA8_LIBRARY ${PYTHIA8_LIBRARY} )

find_library(PYTHIA8_HEPMC_LIBRARY NAMES pythia8tohepmc
			     HINTS $ENV{PYTHIA8LOCATION}/lib ${PYTHIA8LOCATION}/lib
			     HINTS $ENV{PYTHIA8}/lib ${PYTHIA8}/lib)

# message(STATUS PYTHIA8_HEPMC_LIBRARY ${PYTHIA8_HEPMC_LIBRARY} )

find_library(PYTHIA8_HAPDF_LIBRARY NAMES lhapdfdummy
			     HINTS $ENV{PYTHIA8LOCATION}/lib ${PYTHIA8LOCATION}/lib
			     HINTS $ENV{PYTHIA8}/lib ${PYTHIA8}/lib)

# message(STATUS PYTHIA8_HAPDF_LIBRARY ${PYTHIA8_HAPDF_LIBRARY} )

# handle the QUIETLY and REQUIRED arguments and set PYTHIA8_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pythia8 DEFAULT_MSG PYTHIA8_LIBRARY)
mark_as_advanced(PYTHIA8_FOUND PYTHIA8_LIBRARY PYTHIA8_HEPMC_LIBRARY PYTHIA8_HAPDF_LIBRARY)
#==============================================================================

if(PYTHIA8_FOUND)
  message(STATUS "G4 Examples: Pythia8 found. --> main42 with Pythia8 enabled.")
  add_definitions(-DG4LIB_USE_PYTHIA)
else()
  set(PYTHIA8_LIBRARY "")
  set(PYTHIA8_HEPMC_LIBRARY "")
  set(PYTHIA8_HAPDF_LIBRARY "")
endif()

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
include_directories(${HEPMC_INCLUDE_DIR})
include_directories(${PYTHIA8_INCLUDE_DIR})
add_executable(main42 main42.cc)
target_link_libraries(main42
                      ${HEPMC_LIBRARIES} ${PYTHIA8_LIBRARY}
                      ${PYTHIA8_HEPMC_LIBRARY} ${PYTHIA8_HAPDF_LIBRARY} gcc)


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS main42 DESTINATION bin)

