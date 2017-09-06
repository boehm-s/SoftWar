CC	=	gcc
NAME	=	SoftWar

SRC	=	init.c	\
		main.c

OBJ	=	$(SRC:%.c=%.o)

RM	=	rm -Rf

GCFLAGS  =	gcc -W -Wall -Werror -Wextra -ansi -pedantic

LDFLAGS =	-lzlog

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
		./SoftWar -v --size=8 --log=/tmp/soft_war.log --cycle=1000000 --rep-port=515 --pub-port=1921

.PHONY	:	all clean fclean re run
