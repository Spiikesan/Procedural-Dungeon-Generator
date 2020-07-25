CXX		= g++

RM		= rm -rf

NAME		= genmap

BIN_NAME	= $(addprefix bin/, $(NAME))

CXXFLAGS	+= -W -Wall -Werror -Wextra -Iinclude -std=c++11 -O3

LDFLAGS		= -lglut -lGL -lGLU -lGLEW

SRCS_DIR	= src

OBJS_DIR	= obj

SRCS		= main.cpp \
		  Point.cpp \
		  Box.cpp \
		  Render.cpp \
		  Edge.cpp \
		  GObject.cpp \
		  Canvas.cpp \
		  Color.cpp \
		  Square.cpp \
		  Random.cpp \
		  Generate.cpp \
		  Triangle.cpp \
		  Util.cpp \
		  Circle.cpp \
		  Filter.cpp \
		  Transform.cpp \
		  Shader.cpp \
		  FastRandom.cpp

SRCS_BIN	= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS_BIN	= $(addsuffix .o, $(basename $(subst $(SRCS_DIR), \
					       $(OBJS_DIR), $(SRCS_BIN))))

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.cpp
		  $(shell mkdir -p $(OBJS_DIR))
		  $(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_NAME)	: $(OBJS_BIN)
		  $(shell mkdir -p bin)
		  $(CXX) $(CXXFLAGS) $(OBJS_BIN) $(LDFLAGS) -o $(BIN_NAME)
		  ln -fs $(BIN_NAME) $(NAME)

all		: $(BIN_NAME)

clean		:
		  $(RM) $(OBJS_BIN)

fclean		: clean
		  $(RM) $(BIN_NAME)
		  $(RM) $(NAME)

re		: fclean all

.PHONY		: re clean fclean all
