CC	=	gcc
NAME	=	SoftWar

SRC	=	init.c		\
		game.c		\
		json.c		\
		game_commands.c	\
		server.c	\
		main.c

OBJ	=	$(SRC:%.c=%.o)

RM	=	rm -Rf

GCFLAGS  =	gcc -W -Wall -Werror -Wextra -pedantic

LDFLAGS =	-lzlog -lczmq -lzmq -lcollectc

$(NAME)	:	$(OBJ)
		$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(LDFLAGS)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)
		$(RM) *~
		$(RM) #*#

fclean	:	clean
		$(RM) $(NAME)

%.o	:	%.c
		$(GCFLAGS) -c $< -o $@

re	:	fclean all

run	:
		./SoftWar -v --size=8 --log=/tmp/soft_war.log --cycle=1000000 --pub-port=4242 --rep-port=4243

.PHONY	:	all clean fclean re run
