# basic-gl-shaders - Simple C++ wrappers for OpenGL shaders
# Copyright (C) 2017 - Eduardo Costa
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
cmake_minimum_required(VERSION 3.9)
project(m4c0-bgl-shaders VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXPORT_NAME "${PROJECT_NAME}-config")

find_package(opengl-headers REQUIRED)

add_library(${PROJECT_NAME} STATIC main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${PROJECT_NAME}.hpp")
target_link_libraries(${PROJECT_NAME} PUBLIC opengl-headers)
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${EXPORT_NAME}
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
    PUBLIC_HEADER DESTINATION include)

install(EXPORT ${EXPORT_NAME} DESTINATION "lib/cmake/${PROJECT_NAME}")

find_package(m4c0-bgl-loop)
if(m4c0-bgl-loop_FOUND)
    add_executable(example example.cpp)
    target_link_libraries(example PUBLIC ${PROJECT_NAME})
    target_link_libraries(example PUBLIC m4c0-bgl-loop)
else()
    message("m4c0-bgl-loop not found - example was skipped")
endif()


