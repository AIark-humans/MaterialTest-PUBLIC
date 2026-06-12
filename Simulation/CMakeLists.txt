cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(materialTest)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

file(GLOB macros "*.mac")
file(COPY ${macros} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(matTest matTest.cc ${sources} ${headers})
target_link_libraries(matTest ${Geant4_LIBRARIES})

add_custom_target(materialTest DEPENDS matTest)
