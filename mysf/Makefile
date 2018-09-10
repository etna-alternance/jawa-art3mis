default: all

CC			= g++
CPPFLAGS	+= -Wall -Wextra -pedantic -Werror -O3 -std=c++14 -fPIC
CPPFLAGS	+= -I ./includes
# CPPFLAGS	+= -I /usr/local/include

LIBSFML		= -L /usr/local/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

SRC_DIR		= sources
SRC			= \
			$(SRC_DIR)/Binding.cpp \
			$(SRC_DIR)/Engine.cpp \
			$(SRC_DIR)/Event.cpp \
			$(SRC_DIR)/GraphicLayer.cpp \
			$(SRC_DIR)/GraphicLayerSet.cpp \
			$(SRC_DIR)/GraphicRender.cpp \
			$(SRC_DIR)/Joysticks.cpp \
			$(SRC_DIR)/Key.cpp \
			$(SRC_DIR)/Mouse.cpp \
			$(SRC_DIR)/SceneNode.cpp \
			$(SRC_DIR)/AnimNode.cpp \
			$(SRC_DIR)/SoundPlayer.cpp

OBJ			= $(SRC:.cpp=.o)

NAME		= mysf
NAME_STC	= lib$(NAME).a
NAME_DYN	= lib$(NAME).so

RM			= rm -f

all: $(NAME_STC) $(NAME_DYN)

$(NAME_STC): $(OBJ)
	ar rcs $(NAME_STC) $(OBJ)

$(NAME_DYN): $(OBJ)
	$(CC) -shared $(OBJ) $(CPPFLAGS) $(LIBSFML) -o $(NAME_DYN)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME_STC) $(NAME_DYN)

re: fclean all

.PHONY		= all $(NAME_STC) $(NAME_DYN) clean fclean re
