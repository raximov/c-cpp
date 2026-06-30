CXX := g++
CXXSTD := -std=c++20
CXXFLAGS := $(CXXSTD) -Wall -Wextra -O2
LDFLAGS :=

GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0 2>/dev/null)
GTK_LIBS := $(shell pkg-config --libs gtk+-3.0 2>/dev/null)
GTEST_CFLAGS := $(shell pkg-config --cflags gtest 2>/dev/null)
GTEST_LIBS := $(shell pkg-config --libs gtest 2>/dev/null || echo "-lgtest -lgtest_main -pthread")

SRC_DIR := .
BUILD_DIR := build
INSTALL_DIR ?= $(CURDIR)/install

MODEL_SRCS := $(SRC_DIR)/model/matrix_perceptron.cc \
              $(SRC_DIR)/model/graph_perceptron.cc \
              $(SRC_DIR)/model/data_loader.cc
CONTROLLER_SRCS := $(SRC_DIR)/controller/controller.cc
VIEW_SRCS := $(SRC_DIR)/view/main_window.cc
APP_SRCS := $(MODEL_SRCS) $(CONTROLLER_SRCS) $(VIEW_SRCS) $(SRC_DIR)/main.cc
TEST_SRCS := $(MODEL_SRCS) $(CONTROLLER_SRCS) $(SRC_DIR)/tests/tests_main.cc

APP_OBJS := $(APP_SRCS:%.cc=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:%.cc=$(BUILD_DIR)/test_%.o)

APP_BIN := MultilayerPerceptron
TEST_BIN := mlp_tests

.PHONY: all install uninstall clean dvi dist tests run

all: $(APP_BIN)

$(APP_BIN): $(APP_OBJS)
	$(CXX) $(CXXFLAGS) $(GTK_CFLAGS) -o $@ $(APP_OBJS) $(GTK_LIBS) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(GTK_CFLAGS) -c $< -o $@

tests: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(GTEST_CFLAGS) -o $@ $(TEST_OBJS) $(GTEST_LIBS)

$(BUILD_DIR)/test_%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(GTEST_CFLAGS) -c $< -o $@

run: all
	./$(APP_BIN)

install: all
	mkdir -p $(INSTALL_DIR)
	cp $(APP_BIN) $(INSTALL_DIR)/

uninstall:
	rm -f $(INSTALL_DIR)/$(APP_BIN)

clean:
	rm -rf $(BUILD_DIR) $(APP_BIN) $(TEST_BIN) *.dvi *.tar.gz

dvi:
	@which doxygen >/dev/null 2>&1 && doxygen Doxyfile || echo "doxygen not found: skipping documentation generation"

dist: clean
	tar --exclude='./install' --exclude='./.git' -czf MultilayerPerceptron.tar.gz -C .. $(notdir $(CURDIR))
