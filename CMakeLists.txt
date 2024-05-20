cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(graphics-cookbook CXX C)

execute_process(
  COMMAND ./vcpkg/bootstrap-vcpkg.sh
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  RESULT_VARIABLE bootstrap_result
)

if(NOT (${bootstrap_result} EQUAL 0))
  message(FATAL_ERROR "Canot run bootstrap vcpkg")
endif()

add_subdirectory(dependencies)
add_subdirectory(shared)

add_subdirectory(TestProject)



