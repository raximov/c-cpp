cmake_minimum_required(VERSION 3.16)
project(3DViewer_Tests)
set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(test_runner
  test_parser.cpp
  test_transform.cpp
  test_mesh.cpp
  ../model/parser/obj_parser.cpp
  ../model/geometry/mesh.cpp
  ../model/geometry/transform.cpp
  ../utils/math_utils.cpp
  ../model/lighting/light_source.cpp
  ../model/shading/shading_model.cpp
  ../model/scene.cpp
)

target_link_libraries(test_runner PRIVATE
  ${GTEST_BOTH_LIBRARIES}
  pthread
)
