cmake_minimum_required(VERSION 2.6)
project(Notemania)

add_subdirectory(ThirdParty)

include_directories(
  ThirdParty/sfml-2.4.2/include/
  ${PROJECT_NAME}/include/
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
  sfml-network
  sfml-main
  )

file(GLOB NOTEMANIA_SOURCES ${PROJECT_NAME}/src/*.cpp)
file(GLOB NOTEMANIA_HEADERS
  ${PROJECT_NAME}/include/*.hpp
  ${PROJECT_NAME}/include/*.h
  )
file(GLOB NOTEMANIA_IMAGES ${PROJECT_NAME}/data/images/*.jpg
  ${PROJECT_NAME}/data/images/*.png
  )
file(GLOB NOTEMANIA_MUSIC ${PROJECT_NAME}/data/music/*.ogg)
file(GLOB NOTEMANIA_FONTS ${PROJECT_NAME}/data/fonts/*.png
  ${PROJECT_NAME}/data/fonts/*.txt
  ${PROJECT_NAME}/data/fonts/*.ttf
  )
file(GLOB NOTEMANIA_SHADERS ${PROJECT_NAME}/data/shaders/*.vert
  ${PROJECT_NAME}/data/shaders/*.frag
  )
file(GLOB NOTEMANIA_SFX ${PROJECT_NAME}/data/sfx/*.wav
  ${PROJECT_NAME}/data/images/*.png
  )
file(GLOB NOTEMANIA_CONFIGS CMakeLists.txt )

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_definitions(-DCMAKE-C-FLAGS)

if (WIN32)
  set(ADDITIONAL_FLAGS WIN32)
else ()
  set(ADDITIONAL_FLAGS "")
endif()

add_executable(${PROJECT_NAME} ${ADDITIONAL_FLAGS}
  ${NOTEMANIA_SOURCES} ${NOTEMANIA_HEADERS}
  ${NOTEMANIA_IMAGES} ${NOTEMANIA_MUSIC}
  ${NOTEMANIA_FONTS} ${NOTEMANIA_SHADERS}
  ${NOTEMANIA_SFX}  ${NOTEMANIA_CONFIGS}
  )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

target_link_libraries(${PROJECT_NAME}
  ${ALL_LIBS}
  )

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME})
