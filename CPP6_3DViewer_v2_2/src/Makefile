CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -O2 -fPIC
GTEST_FLAGS = -lgtest -lgtest_main -pthread
INSTALL_DIR = $(HOME)/3DViewer

SRC_MODEL = model/vec3.cc model/obj_parser.cc model/scene.cc \
            model/affine_transform.cc model/ray_tracer.cc model/light.cc \
            model/camera.cc model/geometric_objects.cc model/kd_tree.cc
SRC_CTRL  = controller/controller.cc
SRC_VIEW  = view/main_window.cc view/gl_widget.cc view/render_preview.cc
SRC_MAIN  = main.cc

OBJS_MODEL = $(SRC_MODEL:.cc=.o)
OBJS_CTRL  = $(SRC_CTRL:.cc=.o)
OBJS_VIEW  = $(SRC_VIEW:.cc=.o)

MOC = moc
MOC_HEADERS = view/main_window.h view/gl_widget.h view/render_preview.h
MOC_SOURCES = $(MOC_HEADERS:%.h=%_moc.cc)
OBJS_MOC    = $(MOC_SOURCES:.cc=.o)

.PHONY: all install uninstall clean dvi dist tests

all: 3dviewer

3dviewer: $(OBJS_MODEL) $(OBJS_CTRL) $(OBJS_VIEW) $(OBJS_MOC) main.o
	$(CC) $(CFLAGS) $^ -o $@ `pkg-config --libs Qt5Widgets Qt5OpenGL` -lGL -lGLU

%_moc.cc: %.h
	$(MOC) `pkg-config --cflags Qt5Widgets Qt5OpenGL` $< -o $@

%.o: %.cc
	$(CC) $(CFLAGS) `pkg-config --cflags Qt5Widgets Qt5OpenGL` -c $< -o $@

install: all
	mkdir -p $(INSTALL_DIR)
	cp 3dviewer $(INSTALL_DIR)/

uninstall:
	rm -rf $(INSTALL_DIR)

clean:
	find . -name "*.o" -delete
	rm -f 3dviewer
	rm -f tests/test_runner
	rm -rf dist/

dvi:
	@echo "3DViewer v2.2 Documentation"
	@echo "  Build:   make all"
	@echo "  Install: make install"
	@echo "  Test:    make tests"
	@echo "  Dist:    make dist"

dist:
	mkdir -p dist
	tar czf dist/3dviewer_v2.2.tar.gz \
		--exclude=dist --exclude='*.o' --exclude=3dviewer \
		.
	@echo "Archive created: dist/3dviewer_v2.2.tar.gz"

tests:
	$(CC) $(CFLAGS) \
		model/vec3.cc model/obj_parser.cc model/scene.cc \
		model/affine_transform.cc model/geometric_objects.cc \
		model/kd_tree.cc model/light.cc model/camera.cc \
		model/ray_tracer.cc controller/controller.cc \
		tests/test_parser.cc tests/test_affine.cc \
		tests/test_scene.cc tests/test_raytracer.cc \
		$(GTEST_FLAGS) -o tests/test_runner
	./tests/test_runner
