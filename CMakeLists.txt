cmake_minimum_required(VERSION 2.6)
project(Notemania)

add_subdirectory(ThirdParty)

include_directories(
  ThirdParty/sfml-2.4.2/include/
  )

option(SFML_BUILD_EXAMPLES OFF)
option(SFML_BUILD_DOC OFF)
option(SFML_BUILD_SHADER_LIBS OFF)
option(SFML_USE_STATIC_STD_LIBS ON) # Windows only
option(BUILD_SHARED_LIBS OFF)

add_definitions(-DSFML_STATIC)

find_package(OpenGL REQUIRED)

set(ALL_LIBS
  ${SFML_LIBRARY}
  sfml-system
  sfml-window
  sfml-graphics
  sfml-audio
  sfml-main
  )

file(GLOB NOTEMANIA_SOURCES Notemania/src/*.cpp)
file(GLOB NOTEMANIA_HEADERS Notemania/include/*.hpp
  Notemania/include/*.h)
file(GLOB NOTEMANIA_RESOURCES Notemania/resources/images/*.png
                                  Notemania/resources/images/*.jpg
                                  Notemania/resources/sounds/*.mp3
                                  Notemania/resources/sounds/*.wav
                                  Notemania/resources/*.txt)
file(GLOB NOTEMANIA_CONFIGS CMakeLists.txt)

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME}
  ${NOTEMANIA_SOURCES} ${NOTEMANIA_HEADERS}
  ${NOTEMANIA_RESOURCES} ${NOTEMANIA_CONFIGS}
  )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

target_link_libraries(${PROJECT_NAME}
  ${ALL_LIBS}
  )

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME})
