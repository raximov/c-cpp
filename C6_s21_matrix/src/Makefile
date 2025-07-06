# Компилятор и флаги
CC = gcc
CFLAGS = -std=c11 
#-Wall -Wextra -Werror -pedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

ADDITIONAL_LIBS = -lcheck -lsubunit -lm -lpthread
# Additionals flags for GCOV
LIBS_GCOV = $(ADDITIONAL_LIBS) -lgcov 

# Определение путей для Check через pkg-config
CHECK_CFLAGS = $(shell pkg-config --cflags check 2>/dev/null || echo "-I/media/sf_s21_string+/check-0.15.2/include")
CHECK_LDFLAGS = $(shell pkg-config --libs check 2>/dev/null || echo "-L/media/sf_s21_string+/check-0.15.2/lib -lcheck -lsubunit -lm -lpthread -lgcov")

# ========================================= CONFIGS ===============================================

# Paths
OBJ_DIR = obj
MODULES_DIR = utils
TEST_DIR = tests
TESTS_OBJ_DIR = obj/tests
REPORT_DIR = report
GCOV_OBJ_DIR = obj/gcov

# Library name
LIBRARY = s21_matrix.a
# Library name for gcov
LIBRARY_GCOV = s21_matrix_gcov.a

ALL_FILES = $(shell find . -name "*.c" -o -name "*.h")

LIBRARY_SRC_DIRS = $(shell find ${MODULES_DIR} -type d)
LIBRARY_SRC_C = $(notdir $(shell find $(LIBRARY_SRC_DIRS) -maxdepth 1 -name "*.c"))
_LIBRARY_SRC_H = $(shell find $(LIBRARY_SRC_DIRS) -maxdepth 1 -name "*.h")
_LIBRARY_MAIN_H = $(shell find . -maxdepth 1 -name "*.h")
LIBRARY_ALL_H = $(_LIBRARY_SRC_H) $(_LIBRARY_MAIN_H)
LIBRARY_OBJS = $(LIBRARY_SRC_C:%.c=%.o)

TESTS_DIRS = $(shell find $(TEST_DIR) -type d)
TESTS_C = $(notdir $(shell find $(TESTS_DIRS) -maxdepth 1 -name "*.c"))
TESTS_H = $(shell find $(TESTS_DIRS) -maxdepth 1 -name "*.h")
TESTS_OBJS = $(addprefix $(TESTS_OBJ_DIR)/, $(notdir $(TESTS_C:%.c=%.o)))

MODULES_GCOV = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(LIBRARY_SRC_C:.c=.o)))

# Имя исполняемого файла
TEST_EXE = tests_runner
# Название исполняемого файла для отчета по покрытию и цель для его сборки
GCOV_EXE = gcov_report

# Пути поиска исходников
vpath %.c $(LIBRARY_SRC_DIRS) : $(TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# ========================================= TARGETS ===============================================

all: test

test: $(OBJ_DIR) $(TESTS_OBJ_DIR) $(LIBRARY) $(TESTS_OBJS)
	@$(CC) $(TESTS_OBJS) $(LIBRARY) $(ADDITIONAL_LIBS) -o $(TEST_EXE) $(ADDITIONAL_LIBS)
	@./$(TEST_EXE)

$(GCOV_EXE): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(REPORT_DIR) $(LIBRARY_GCOV) $(TESTS_OBJS) $(LIBRARY_ALL_H) $(TESTS_H)
	@echo "Создание виртуального окружения Python..."
	@python3 -m venv /tmp/venv

	@echo "Установка gcovr в виртуалку..."
	@/tmp/venv/bin/pip install --upgrade pip > /dev/null
	@/tmp/venv/bin/pip install gcovr > /dev/null

	@echo "Сборка тестового бинарника с флагами gcov..."
	@$(CC) $(TESTS_OBJS) $(LIBRARY_GCOV) $(GCOV_FLAGS) $(LIBS_GCOV) -o $(GCOV_EXE) $(CHECK_LDFLAGS)

	@echo "Запуск тестов..."
	@./$(GCOV_EXE) > /dev/null

	@echo "Генерация HTML-отчета покрытия..."
	@/tmp/venv/bin/gcovr -r . \
		--html --html-details \
		--exclude 'test/*' \
		-o ./$(REPORT_DIR)/index.html

	@echo "Удаление временного виртуального окружения..."
	@rm -rf /tmp/venv


# Сборка библиотеки
$(LIBRARY): $(OBJ_DIR) $(TESTS_OBJ_DIR) $(LIBRARY_OBJS) $(LIBRARY_ALL_H)
	@echo $(LIBRARY_SRC_DIRS)
	@ar rc $@ $(LIBRARY) $(addprefix $(OBJ_DIR)/, $(LIBRARY_OBJS))

$(LIBRARY_GCOV): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(MODULES_GCOV) $(LIBRARY_ALL_H)
	@ar rc $(LIBRARY_GCOV) $(MODULES_GCOV)
	@ranlib $(LIBRARY_GCOV)

# Создание папок для объектных файлов
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(TESTS_OBJ_DIR):
	@mkdir -p $(TESTS_OBJ_DIR)
$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)
$(GCOV_OBJ_DIR):
	@mkdir -p $(GCOV_OBJ_DIR)

$(GCOV_OBJ_DIR)/%.o : %.c $(LIBRARY_ALL_H) $(TESTS_H)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -c -o $@ $<
	
$(TESTS_OBJ_DIR)/%.o : %.c $(TESTS_H) $(LIBRARY_ALL_H) 
	$(CC) $(ADDITIONAL_LIBS) $(CFLAGS) -c -o $@ $<

# Компиляция .c -> .o в obj/
%.o: %.c $(LIBRARY_ALL_H) $()
	$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<

# ========================================= STANDART TARGETS ===============================================

valgrind:
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./$(TEST_EXE)

clean:
	rm -f *.a *.o
	rm -rf $(OBJ_DIR)
	rm -f *.c.gcov *.gcno *.gcov *.gcda output.info
	rm -rf $(REPORT_DIR)
	rm -f ./$(GCOV_EXE) ./$(TEST_EXE)

check-format: 
	clang-format -n $(ALL_FILES)
	
clang-format: 
	clang-format -i $(ALL_FILES)

rebuild: clean all

.PHONY: all rebuild clean valgrind