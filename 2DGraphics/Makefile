# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 18:25:54 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/02 18:50:27 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/build

SRC				= ${wildcard ${SRCS_DIR}/*.c}
OBJ 			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror
memcheck: CFLAGS 	+= -D MEMCHECK
DEPENDENCIES		= -I../Libft

NAME			= ${ROOT}/lib2D_Graphics.a
EXPORT_INCLUDE	= ${ROOT}/DD_Graphics.h


.PHONY: all clean fclean re norm memcheck


all: ${NAME} ${EXPORT_INCLUDE}

${NAME}: ${OBJ}
	ar rc $@ ${OBJ}

${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR} ${DEPENDENCIES}

${ROOT}/%.h: ${INCLUDES_DIR}/%.h
	cp $< $@


clean:
	rm -rf ${BUILD_DIR}


fclean: clean
	rm -rf ${NAME} ${EXPORT_INCLUDE}


re: fclean all


norm:
	norminette ${SRCS_DIR} ${INCLUDES_DIR}


memcheck: all


${BUILD_DIR}:
	mkdir -p $@
