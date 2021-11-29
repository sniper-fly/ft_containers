CXX = clang++
INCLUDE = -I"./googletest/include" -I"./include"
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98 $(INCLUDE) -MMD -MP

SRCS = ./src/main.cpp ./src/aaa/hoge.cpp 
OBJ_DIR = objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))
DEPENDS = $(OBJS:.o=.d)

ifeq ($(shell uname),Linux)
LIBPATH = "./googletest/1_5_0"
else
LIBPATH = "./googletest/1_5_0mac"
endif
LIBS = -lgtest -lpthread

NAME = a.out

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) -L $(LIBPATH) $(OBJS) $(LIBS)

$(OBJ_DIR)%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDS)

clean:
	rm -rf $(OBJS) $(DEPENDS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: all
	$(NAME)

update_src:
	./script/src_updater.sh

.PHONY: all clean fclean re update_src test
