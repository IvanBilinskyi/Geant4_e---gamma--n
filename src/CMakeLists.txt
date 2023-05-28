### Geant4 Section ###
if(PROJECT_GEANT4_USE_GUI)
  find_package(Geant4 11 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 11 REQUIRED)
endif()

# finding Geant4 script files and updating them in the build directory
file(GLOB Geant4ScriptFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/../scripts/*.mac")
foreach (f ${Geant4ScriptFiles})
  message(status "From ${f}")
  get_filename_component(outputFileName ${f} NAME)
  message(status "To ${CMAKE_CURRENT_BINARY_DIR}/${outputFileName}")
  configure_file(${f} ${CMAKE_CURRENT_BINARY_DIR}/${outputFileName} COPYONLY)
endforeach ()

# configure source files
set(DETECTOR_SOURCE_FILES
        detector/DetectorConstruction.cc
        detector/DetectorConstruction.hh
        detector/DetectorMessenger.cc
        detector/DetectorMessenger.hh)

set(PHYSICS_SOURCE_FILES
        physics/PhysicsList.cc
        physics/PhysicsList.hh
        physics/ElectronPhysics.cpp
        physics/ElectronPhysics.hh
        physics/GammaNuclearPhysics.cc
        physics/GammaNuclearPhysics.hh
        physics/GammaNuclearPhysicsLEND.cc
        physics/GammaNuclearPhysicsLEND.hh)

set(RUN_SOURCE_FILES
        run/Run.cc
        run/Run.hh
        run/RunMessenger.cc
        run/RunMessenger.hh)

set(ACTION_SOURCE_FILES
        actions/ActionInitialization.cc
        actions/ActionInitialization.hh
        actions/PrimaryGeneratorAction.cc
        actions/PrimaryGeneratorAction.hh
        actions/RunAction.cc
        actions/RunAction.hh
        actions/SteppingAction.cc
        actions/SteppingAction.hh)

set(ANALYSIS_SOURCE_FILES
        analysis/HistoManager.cc
        analysis/HistoManager.hh
        analysis/ParticleInfo.cpp
        analysis/ParticleInfo.hh)

# make the executable
add_executable(simulation
        main.cpp
        Geant4Application.cpp
        Geant4Application.h
        ApplicationMessenger.cpp
        ApplicationMessenger.h
        ${DETECTOR_SOURCE_FILES}
        ${PHYSICS_SOURCE_FILES}
        ${RUN_SOURCE_FILES}
        ${ACTION_SOURCE_FILES}
        ${ANALYSIS_SOURCE_FILES})
target_include_directories(simulation PRIVATE
        detector
        physics
        run
        actions
        analysis
        ${PYTHIA8_INCLUDE_DIRS})
target_link_libraries(simulation PUBLIC
        common
        ${Geant4_LIBRARIES})
