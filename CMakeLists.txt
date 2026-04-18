cmake_minimum_required(VERSION 3.16)
project(GravitySim VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type par défaut : Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Flags de compilation
set(CMAKE_CXX_FLAGS_DEBUG   "-g -Wall -Wextra -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# ----- Dépendances -----

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# GLEW
find_package(GLEW REQUIRED)

# GLM (header-only, on cherche juste le dossier)
find_package(glm QUIET)
if(NOT glm_FOUND)
  # Fallback : chercher manuellement dans /usr/include
  find_path(GLM_INCLUDE_DIR glm/glm.hpp)
  if(NOT GLM_INCLUDE_DIR)
    message(FATAL_ERROR "GLM introuvable. Installe : sudo apt install libglm-dev")
  endif()
endif()

# ----- Sources -----
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# ----- Includes -----
target_include_directories(${PROJECT_NAME} PRIVATE
  ${GLFW_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIR}
  src/
)

# ----- Link -----
target_link_libraries(${PROJECT_NAME} PRIVATE
  OpenGL::GL
  GLEW::GLEW
  ${GLFW_LIBRARIES}
)

message(STATUS "Build type : ${CMAKE_BUILD_TYPE}")
message(STATUS "Compilateur : ${CMAKE_CXX_COMPILER}")