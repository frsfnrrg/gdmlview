cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(gdmlview)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(gdmlview gdmlview.cc ${sources} ${headers})
target_link_libraries(gdmlview ${Geant4_LIBRARIES} )

set(SCRIPTS
    vis.mac
  )

foreach(_script ${SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

install(TARGETS gdmlview DESTINATION bin)

