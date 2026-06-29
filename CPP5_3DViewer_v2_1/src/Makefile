CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic
INSTALL_DIR = $(HOME)/3DViewer_v2.1_app
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = $(SRC_DIR)/tests

.PHONY: all install uninstall clean dvi dist tests

all: $(BUILD_DIR)/3DViewer

$(BUILD_DIR)/3DViewer: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../$(SRC_DIR) -DCMAKE_BUILD_TYPE=Release && make -j$(nproc)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

install: $(BUILD_DIR)/3DViewer
	mkdir -p $(INSTALL_DIR)
	cp $(BUILD_DIR)/3DViewer $(INSTALL_DIR)/
	@echo "Installed to $(INSTALL_DIR)"

uninstall:
	rm -rf $(INSTALL_DIR)
	@echo "Uninstalled"

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TEST_DIR)/test_runner
	@echo "Cleaned"

dvi:
	@echo "Opening documentation..."
	@if command -v doxygen &> /dev/null; then \
		doxygen Doxyfile; \
		xdg-open docs/html/index.html 2>/dev/null || open docs/html/index.html 2>/dev/null; \
	else \
		echo "Doxygen not found. Please install doxygen."; \
	fi

dist:
	tar -czf 3DViewer_v2.1.tar.gz \
		--exclude='./build' \
		--exclude='./.git' \
		.
	@echo "Distribution archive created: 3DViewer_v2.1.tar.gz"

tests:
	cd $(TEST_DIR) && cmake . -DCMAKE_BUILD_TYPE=Debug && make -j$(nproc) && ./test_runner
