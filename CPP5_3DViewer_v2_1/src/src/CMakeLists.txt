cmake_minimum_required(VERSION 3.16)
project(3DViewer VERSION 2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)
find_package(OpenGL REQUIRED)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    model/parser/obj_parser.cpp
    model/geometry/mesh.cpp
    model/geometry/transform.cpp
    model/lighting/light_source.cpp
    model/shading/shading_model.cpp
    model/scene.cpp
    view/main_window.cpp
    view/opengl/gl_widget.cpp
    view/widgets/transform_panel.cpp
    view/widgets/settings_panel.cpp
    controller/scene_controller.cpp
    utils/math_utils.cpp
)

set(HEADERS
    model/parser/obj_parser.h
    model/geometry/mesh.h
    model/geometry/transform.h
    model/lighting/light_source.h
    model/shading/shading_model.h
    model/scene.h
    view/main_window.h
    view/opengl/gl_widget.h
    view/widgets/transform_panel.h
    view/widgets/settings_panel.h
    controller/scene_controller.h
    utils/math_utils.h
)

qt_add_executable(3DViewer
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(3DViewer PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    OpenGL::GL
)

target_include_directories(3DViewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
