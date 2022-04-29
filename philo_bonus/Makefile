NAME	=	philo_bonus

SRCS	=	philo.c	utils.c	message.c simulation.c init.c

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

HEADER	=	philo.h

%.o: %.c
	${CC}	${CFLAGS} -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}


all:	${NAME}

clean:
		@${RM} ${OBJS}

fclean:
		@${RM} ${OBJS} ${NAME}

re:		fclean all

.PHONE:	fclean clean re all