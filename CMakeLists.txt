cmake_minimum_required(VERSION 2.8)

project(MandelBrot)

set(SOURCE_DIR "src")

set(CMAKE_MODULE_PATH "/usr/local/share/SFML/cmake/Modules/;${CMAKE_MODULE_PATH}")

set(EXECUTABLE_NAME "MandelBrot")

add_executable(${EXECUTABLE_NAME} 
               	${SOURCE_DIR}/main.cpp
                ${SOURCE_DIR}/Logger.cpp)

find_package(SFML 2 REQUIRED graphics window system)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARY})
endif()
