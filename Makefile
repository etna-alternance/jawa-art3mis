default: all

CC			= g++
CPPFLAGS	+= -Wall -Wextra -Werror -O3 --std=c++14
CPPFLAGS	+= -I ./includes -I ./mysf/includes

LDFLAGS		+= $(LIB)

##
## PROJECT
##

NAME 		= art3mis
RM			= rm -f

LIBSFML		= -L /usr/local/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
LIBMYSF		= -L ./mysf -lmysf
LIB			= $(LIBSFML) $(LIBMYSF)

SRC_DIR		= ./sources
SRC			= \
			$(SRC_DIR)/main.cpp \
			$(SRC_DIR)/Art3mis.cpp \
			$(SRC_DIR)/CodecRender.cpp \
			$(SRC_DIR)/SpriteNode.cpp \
			$(SRC_DIR)/TextBox.cpp

OBJ			= $(SRC:.cpp=.o)

##
## RULES
##

all: libmysf $(NAME)
	$(RM) ./libmysf.so
	ln -s mysf/libmysf.so .
	$(RM) ./libmysf.a
	ln -s mysf/libmysf.a .

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) ./libmysf.so
	$(RM) ./libmysf.a

fclean: clean
	$(RM) $(NAME)

libmysf:
	make -C mysf/

lclean:
	make clean -C mysf/

lfclean:
	make fclean -C mysf/

lre:
	make re -C mysf/

re: fclean all

.PHONY: default all $(NAME) clean fclean libmysf lclean lfclean lre re
