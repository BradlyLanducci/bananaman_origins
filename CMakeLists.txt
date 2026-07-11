cmake_minimum_required(VERSION 3.21)

project(bananaman_origins)

include(FetchContent)

FetchContent_Declare(AnguishEngine
  GIT_REPOSITORY https://github.com/BradlyLanducci/anguish_engine.git
  GIT_TAG main
  SOURCE_DIR ${CMAKE_BINARY_DIR}/anguish_engine
  BINARY_DIR ${CMAKE_BINARY_DIR}/anguish_engine_build
)
FetchContent_MakeAvailable(AnguishEngine)

add_compile_options("-Werror")

add_subdirectory(${CMAKE_SOURCE_DIR}/source)
