cmake_minimum_required(VERSION 3.0)
project(gl_tutorials)
set(CMAKE_CXX_STANDARD 11)
cmake_policy(SET CMP0060 NEW)
cmake_policy(SET CMP0065 NEW)
cmake_policy(SET CMP0004 NEW)
MESSAGE("${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(gl_tutorial ${SOURCES})

target_link_libraries(gl_tutorial  ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

#[[add_custom_command(TARGET gl_tutorials POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/shaders
                    $<TARGET_FILE_DIR>/shaders)]]
