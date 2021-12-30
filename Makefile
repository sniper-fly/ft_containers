CXX = clang++
INCLUDE = -I"./googletest/include" -I"./include"
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98 $(INCLUDE) -MMD -MP
EXTRA_FLAGS = -Wno-unused-variable -Wno-unused-parameter
CXXFLAGS += $(EXTRA_FLAGS)
LIBS = -lgtest -lpthread

ifeq ($(shell uname),Linux)
LIBPATH = "./googletest/1_5_0_debug"
else
LIBPATH = "./googletest/1_5_0mac"
endif

ifdef fsanitize
CXXFLAGS += -fsanitize=address
LIBPATH = "./googletest/1_5_0_fsanitize_address"
endif

ifdef debug
SRCS = $(shell find ./src/debug -type f -name '*.cpp')
else
SRCS = src/main.cpp
SRCS += $(shell find ./src/test -type f -name '*.cpp')
endif

OBJ_DIR = objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))
DEPENDS = $(OBJS:.o=.d)

COVFILES = $(OBJS:.o=.gcda) $(OBJS:.o=.gcno) cov_test.info coverageFiltered.info

NAME = a.out

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) -L $(LIBPATH) $(OBJS) $(LIBS)

$(OBJ_DIR)%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDS)

clean:
	rm -rf $(OBJS) $(DEPENDS) $(COVFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: all
	$(NAME)

debug:
	make all debug=1

.PHONY: all clean fclean re update_src test coverage

ifdef cov
CXX = g++
CXXFLAGS += -ftest-coverage -fprofile-arcs -lgcov
endif

coverage:
	make re cov=1
	./$(NAME)
	lcov -c -b . -d . -o cov_test.info
	lcov -r cov_test.info "*/googletest/*" "*/c++/*" -o coverageFiltered.info
	genhtml coverageFiltered.info -o cov_test
