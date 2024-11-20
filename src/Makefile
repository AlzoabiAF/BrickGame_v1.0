CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror
TEST_FLAGS = -lcheck -lm -lsubunit -lpthread
GCOV_FLAGS = -ftest-coverage -fprofile-arcs
BUILD_DIR = build
CLEAN = rm -rf build *.o *.gcno *.gcda test report test.info

OBJS_FUNC = ${shell find . -path './*Function*' -name '*.c' -printf '$(BUILD_DIR)/%P\n' | sed 's/\.c$$/.o/'} 
OBJS_TEST = ${shell find . -path './tests/*' -name '*.c' -printf '$(BUILD_DIR)/%P\n' | sed 's/\.c$$/.o/'} ${BUILD_DIR}/test.o

ifeq ($(shell uname -s),Linux)
    OPEN_CMD = xdg-open
endif

ifeq ($(shell uname -s),Darwin)
    OPEN_CMD = open
endif


all: clean s21_string.a test gcov_report


install:


uninstall:


dvi:

dist:
	

test:  


clean:
	${CLEAN}
	

clang-format:
	find . -name "*.c" -or -name "*.h" | xargs clang-format -i -style=Google

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${BUILD_DIR}/test



${BUILD_DIR}/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@ 