QT += core gui widgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_CXXFLAGS += -std=c++20

TARGET   = 3dviewer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cc \
    model/vec3.cc \
    model/obj_parser.cc \
    model/affine_transform.cc \
    model/light.cc \
    model/camera.cc \
    model/geometric_objects.cc \
    model/kd_tree.cc \
    model/ray_tracer.cc \
    model/scene.cc \
    controller/controller.cc \
    view/gl_widget.cc \
    view/render_preview.cc \
    view/main_window.cc

HEADERS += \
    model/model_data.h \
    model/obj_parser.h \
    model/affine_transform.h \
    model/light.h \
    model/camera.h \
    model/geometric_objects.h \
    model/kd_tree.h \
    model/ray_tracer.h \
    model/scene.h \
    controller/controller.h \
    view/gl_widget.h \
    view/render_preview.h \
    view/main_window.h \
    utils/stb_image_write.h

unix: LIBS += -lGL -lGLU

INCLUDEPATH += .
