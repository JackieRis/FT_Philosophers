# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:26:21 by tnguyen-          #+#    #+#              #
#    Updated: 2022/03/30 13:13:31 by tnguyen-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= main.c utils.c thread.c mutex.c fork.c

OBJ	= ${SRCS:.c=.o}

CC = gcc

FLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread -fno-builtin -I.

all: ${NAME}

%.o:%.c philo.h
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:    ${OBJ}
	$(CC) ${FLAGS} $(OBJ) -o $(NAME)

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
