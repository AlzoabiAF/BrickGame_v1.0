# CC = gcc
# FLAGS = -std=c11 -Wall -Wextra -Werror
# TEST_FLAGS = -lcheck -lm -lsubunit -lpthread
# GCOV_FLAGS = -ftest-coverage -fprofile-arcs
# BUILD_DIR = build
# CLEAN = rm -rf build *.o *.gcno *.gcda test report test.info
# UNAME_S = $(shell uname -s)

# OBJS_TETRIS_LOGIC = ${shell find ./brick_game/tetris -name '*.c' -printf '$(BUILD_DIR)/%P\n' | sed 's/\.c$$/.o/'} 
# OBJS_GUI = ${shell find ./gui/cli -name '*.c' -printf '$(BUILD_DIR)/%P\n' | sed 's/\.c$$/.o/'}
# OBJS_TEST = ${shell find . -path './tests/*' -name '*.c' -printf '$(BUILD_DIR)/%P\n' | sed 's/\.c$$/.o/'} ${BUILD_DIR}/test.o

# ifeq ($(UNAME_S), Linux)
# 	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
# 	OPEN = xdg-open
# else
# 	CHECK_FLAGS = -lcheck
# 	OPEN = open
# endif


# all: clean s21_string.a test gcov_report


# install: ${OBJS_TETRIS_LOGIC} ${OBJS_GUI} 
# 	$(CC) ${FLAGS} ${OBJS_TETRIS_LOGIC} ${OBJS_GUI} 

# uninstall:


# dvi:

# dist:
	

# test:  


# clean:
# 	${CLEAN}
	

# clang-format:
# 	find . -name "*.c" -or -name "*.h" | xargs clang-format -i -style=Google

# valgrind:
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${BUILD_DIR}/test



# $(BUILD_DIR)/%.o: %.c
# 	@mkdir -p ${BUILD_DIR}
# 	$(CC) $(CFLAGS) -c $< -o ${BUILD_DIR}/$(notdir $@)


CC = gcc -g -Wall -Wextra -Werror

BACK = brick_game/tetris/
FRONT = gui/cli/
MAIN = ${BACK}tetris.c
TARGET = tetris

OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	OPEN = xdg-open
else
	CHECK_FLAGS = -lcheck
	OPEN = open
endif

BACK_SOURCES = $(filter-out $(MAIN), $(wildcard $(BACK)*.c))
BACK_OBJECTS = $(BACK_SOURCES:.c=.o)

FRONT_SOURCES = $(wildcard $(FRONT)*.c)
FRONT_OBJECTS = $(FRONT_SOURCES:.c=.o)

all: clean install

$(TARGET): backend.o gui.o main.o
	@$(CC) $^ -lncurses -o $@
# -fsanitize=address 

install: $(TARGET) 
	@rm -rf *.o
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃      'make run' to start the game       ┃"
	@echo "┗=========================================┛"

run: 
	@./tetris

uninstall: clean
	@rm -f $(TARGET)
	@echo "Program successfully uninstalled"

dvi: 
	@cd dvi && doxygen
	@$(OPEN) dvi/html/index.html

dist: 
	@cd ../ && mkdir -p dist
	@cp -r $(BACK) ../dist
	@cp -r $(FRONT) ../dist
	@cp -r dvi ../dist/  
	@tar -czvf ../tetris.tar.gz -C ../dist .
	@rm -rf ../dist tetris
	@echo "Distribution package created: /tetris.tar.gz"

test: backend.o
	@checkmk clean_mode=1 tests/*.check > tests/test.c 
	@$(CC) tests/test.c backend.o $(CHECK_FLAGS) -o test
	@./test

gcov_report: clean test 
	@$(CC) -coverage $(BACK_SOURCES) tests/test.c -o gcovreport $(CHECK_FLAGS)
	@./gcovreport
	@lcov -t "gcovreport" -o gcovreport.info -c -d .
	@genhtml -o report gcovreport.info
	@$(OPEN) report/./index.html

main.o: $(MAIN)
	@$(CC) -c $< -o $@


backend.o: $(BACK_OBJECTS)
	@ld -r $^ -o $@

gui.o: $(FRONT_OBJECTS)
	@ld -r $^ -o $@

%.o: %.c
	@$(CC) -g -c $< -o $@

valgrind_test: test
	valgrind --tool=memcheck --leak-check=full ./test

valgrind_tetris: all
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./tetris 2> valgrind.log
 

clean: clean_tetris clean_tests clean_dvi clean_dist
	@echo "Cleaned..."

clean_tetris:
	@rm -rf ${FRONT}*.o ${BACK}*.o *.o *.a

clean_tests:
	@rm -rf  *.dSYM *.gcda *.gcno gcov* report test tests/*.c

clean_dvi:
	@rm -rf dvi/html

clean_dist:
	@rm -rf ../tetris.tar.gz

rebuild: clean all

.PHONY: dvi