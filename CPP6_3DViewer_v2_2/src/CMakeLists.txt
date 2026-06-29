cmake_minimum_required(VERSION 3.16)
project(3DViewer VERSION 2.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

# ---- Library (model + controller, no Qt) -----------------------------------
set(LIB_SOURCES
    model/vec3.cc
    model/obj_parser.cc
    model/affine_transform.cc
    model/light.cc
    model/camera.cc
    model/geometric_objects.cc
    model/kd_tree.cc
    model/ray_tracer.cc
    model/scene.cc
    controller/controller.cc
)

add_library(viewer_core STATIC ${LIB_SOURCES})
target_include_directories(viewer_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ---- Main executable -------------------------------------------------------
set(APP_SOURCES
    main.cc
    view/gl_widget.cc
    view/render_preview.cc
    view/main_window.cc
)

add_executable(3dviewer ${APP_SOURCES})
target_link_libraries(3dviewer
    PRIVATE viewer_core
            Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL
            OpenGL::GL OpenGL::GLU
)

# ---- Tests -----------------------------------------------------------------
find_package(GTest QUIET)
if(GTest_FOUND)
    enable_testing()
    add_executable(test_runner
        tests/test_parser.cc
        tests/test_affine.cc
        tests/test_scene.cc
    )
    target_link_libraries(test_runner
        PRIVATE viewer_core GTest::GTest GTest::Main pthread
    )
    add_test(NAME all_tests COMMAND test_runner)
endif()
