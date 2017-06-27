cmake_minimum_required(VERSION 2.6)
project(Notemania)

add_subdirectory(ThirdParty)

include_directories(
  ThirdParty/sfml-2.4.2/include/
  )

option(SFML_BUILD_EXAMPLES OFF)
option(SFML_BUILD_DOC OFF)
option(SFML_BUILD_SHADER_LIBS ON)
if (WIN32)
  option(SFML_USE_STATIC_STD_LIBS OFF) # Windows only
elseif (APPLE)
  if ((${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))
    set(SFML_BUILD_FRAMEWORKS ON)
    set(SFML_OSX_ARCHITECTURES "x86_64")
    set(SFML_INSTALL_XCODE_TEMPLATES OFF)
  endif()
endif()
option(BUILD_SHARED_LIBS OFF)

set(ALL_LIBS
  ${SFML_LIBRARY}
  sfml-system
  sfml-window
  sfml-graphics
  sfml-audio
  sfml-main
  )

file(GLOB NOTEMANIA_SOURCES ${PROJECT_NAME}/src/*.cpp)
file(GLOB NOTEMANIA_HEADERS ${PROJECT_NAME}/include/*.hpp
  ${PROJECT_NAME}/include/*.h)
file(GLOB NOTEMANIA_RESOURCES ${PROJECT_NAME}/resources/images/*.png
                                  ${PROJECT_NAME}/resources/images/*.jpg
                                  ${PROJECT_NAME}/resources/sounds/*.mp3
                                  ${PROJECT_NAME}/resources/sounds/*.wav
                                  ${PROJECT_NAME}/resources/*.txt)
file(GLOB NOTEMANIA_CONFIGS CMakeLists.txt)

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_definitions(-DCMAKE-C-FLAGS)

if (WIN32)
  set(ADDITIONAL_FLAGS WIN32)
else ()
  set(ADDITIONAL_FLAGS "")
endif()

add_executable(${PROJECT_NAME} ${ADDITIONAL_FLAGS}
  ${NOTEMANIA_SOURCES} ${NOTEMANIA_HEADERS}
  ${NOTEMANIA_RESOURCES} ${NOTEMANIA_CONFIGS}
  )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

target_link_libraries(${PROJECT_NAME}
  ${ALL_LIBS}
  )

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME})
