# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 19:15:34 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/02 17:54:12 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/build
MINI_LIB_X_DIR	= ${ROOT}/MiniLibX

SRC				= ${wildcard ${SRCS_DIR}/*.c}
OBJ 			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}
MINI_LIB_X_LIB	= ${MINI_LIB_X_DIR}/libmlx.a

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror
memcheck: CFLAGS 	+= -D MEMCHEK
DEPENDENCIES		= -I../Libft

NAME			= ${ROOT}/libwrapped_mlx.a
EXPORT_INCLUDE	= ${ROOT}/wrapped_mlx.h


.PHONY: all clean fclean re norm memcheck


all: ${NAME} ${EXPORT_INCLUDE}

${NAME}: ${MINI_LIB_X_LIB} ${OBJ}
	cp ${MINI_LIB_X_LIB} $@
	ar rc $@ ${OBJ}

${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${MINI_LIB_X_DIR} -I${INCLUDES_DIR} ${DEPENDENCIES}

${ROOT}/%.h: ${INCLUDES_DIR}/%.h
	cp $< $@


clean:
	rm -rf ${BUILD_DIR}


fclean: clean
	@echo Clean MiniLibX...
	@make -s -C ${MINI_LIB_X_DIR} clean
	rm -rf ${NAME} ${EXPORT_INCLUDE}


re: fclean all


norm:
	norminette ${SRCS_DIR} ${INCLUDES_DIR}


memcheck: all


${BUILD_DIR}:
	mkdir -p $@


${MINI_LIB_X_LIB}:
	@echo Build MiniLibX...
	@make -s -C ${MINI_LIB_X_DIR} all
