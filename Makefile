CXX = clang++
INCLUDE = -I"./googletest/include" -I"./"
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98 $(INCLUDE) -MMD -MP

SRC_FILES = main.cpp 
SRC_DIR = src/
OBJ_DIR = objects/
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
DEPENDS = $(OBJS:.o=.d)

VPATH = $(SRC_DIR)

LIBPATH = "./googletest/1_5_0"
LIBS = -lgtest -lpthread

NAME = a.out

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) -L $(LIBPATH) $(OBJS) $(LIBS)

$(OBJ_DIR)%.o: %.cpp
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
